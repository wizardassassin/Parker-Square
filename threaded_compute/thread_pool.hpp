// Custom thread pool from reading
// https://stackoverflow.com/questions/15752659/thread-pooling-in-c11
#pragma once

#include <chrono>
#include <cmath>
#include <condition_variable>
#include <functional>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

#include "timer_util.hpp"

namespace ThreadPool {
// I hope there's no race conditions or unexpected behavior
class ThreadPool {
   private:
    bool stopThreads;
    bool isActive;
    long long threadCount;
    long long jobCount;
    long long activeThreads;
    std::condition_variable mainWait;
    std::mutex threadLock;
    std::condition_variable threadWait;
    std::vector<std::thread> threads;
    std::queue<std::function<void(long long)>> jobs;

    void threadLoop(long long threadId) {
        while (true) {
            std::unique_lock<std::mutex> lock(this->threadLock);
            this->activeThreads--;
            this->mainWait.notify_all();
            this->threadWait.wait(lock, [this] {
                return !this->jobs.empty() || this->stopThreads;
            });
            if (this->stopThreads) return;
            auto job = this->jobs.front();
            this->jobs.pop();
            this->activeThreads++;
            lock.unlock();
            job(threadId);
        }
    }

   public:
    ThreadPool(long long threadCount)
        : threadCount{threadCount},
          activeThreads{0},
          jobCount{0},
          stopThreads{false},
          isActive{false},
          threads(threadCount) {
    }
    ThreadPool() : ThreadPool((long long)std::thread::hardware_concurrency()) {
    }
    void start() {
        if (this->isActive) return;
        this->activeThreads = this->threadCount;
        for (long long i = 0; i < this->threadCount; i++)
            this->threads[i] = std::thread([this, i] { this->threadLoop(i); });
        this->isActive = true;
    }
    void stop() {
        if (!this->isActive) return;
        std::unique_lock<std::mutex> lock(this->threadLock);
        this->stopThreads = true;
        this->threadWait.notify_all();
        lock.unlock();
        for (std::thread& currThread : this->threads) currThread.join();
        this->stopThreads = false;
        this->threads.clear();
        this->threads.resize(this->threadCount);
        std::queue<std::function<void(long long)>> emptyQueue;
        this->jobs = emptyQueue;
        this->jobCount = 0;
        this->isActive = false;
        this->mainWait.notify_all();
    }
    void wait(std::ostream& stream, bool isInteractive = true) {
        std::unique_lock<std::mutex> lock(this->threadLock);
        std::cout << this->threadCount << " Threads:\n";
        auto start = std::chrono::steady_clock::now();
        long long nextPrint = 0;
        this->mainWait.wait(lock, [this, &stream, &start, isInteractive,
                                   &nextPrint] {
            auto stop = std::chrono::steady_clock::now();
            long long activeThreads = this->activeThreads;
            long long jobCount = this->jobCount;
            long long remainingJobs = std::min(
                jobCount, (long long)this->jobs.size() + activeThreads);
            long long completedJobs =
                std::max(0LL, this->jobCount - remainingJobs - activeThreads);
            long long percentComplete =
                (long long)(completedJobs / (long double)jobCount * 100);
            if (!isInteractive && percentComplete < nextPrint) {
                return this->jobs.empty() && this->activeThreads == 0;
            }
            nextPrint++;
            if (isInteractive) stream << "\33[2K\r";
            stream << completedJobs << " / " << jobCount << " - ";
            Timer::printTime(stream, start, stop);
            stream << " < ";
            if (completedJobs != 0) {
                auto duration =
                    std::chrono::duration_cast<std::chrono::nanoseconds>(stop -
                                                                         start);
                long double timePerJob =
                    duration.count() / (long double)(completedJobs);
                auto nanoTime = remainingJobs * timePerJob;
                Timer::printTime(
                    stream, stop,
                    stop + std::chrono::nanoseconds((long long)nanoTime));
            } else {
                stream << "unknown";
            }
            if (isInteractive)
                stream << std::flush;
            else
                stream << std::endl;
            return this->jobs.empty() && this->activeThreads == 0;
        });
        if (isInteractive) stream << std::endl;
        this->jobCount = 0;
    }
    void wait() {
        std::unique_lock<std::mutex> lock(this->threadLock);
        this->mainWait.wait(lock, [this] {
            return this->jobs.empty() && this->activeThreads == 0;
        });
    }
    bool isBusy() {
        std::unique_lock<std::mutex> lock(this->threadLock);
        return this->jobs.empty();
    }
    void addJob(const std::function<void(long long)>& job) {
        std::unique_lock<std::mutex> lock(this->threadLock);
        this->jobCount++;
        this->jobs.push(job);
        this->threadWait.notify_one();
    }
    long long getThreadCount() {
        return this->threadCount;
    }
    bool getActiveStatus() {
        return this->isActive;
    }
};
}  // namespace ThreadPool
