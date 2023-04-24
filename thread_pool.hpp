// Custom thread pool from reading
// https://stackoverflow.com/questions/15752659/thread-pooling-in-c11
#include <chrono>
#include <condition_variable>
#include <functional>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

namespace timer {
void printTime(std::ostream& stream,
               const std::chrono::steady_clock::time_point& startTime,
               const std::chrono::steady_clock::time_point& stopTime);
}  // namespace timer

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
    std::queue<std::function<void()>> jobs;

    void threadLoop() {
        while (true) {
            std::unique_lock<std::mutex> lock(this->threadLock);
            this->activeThreads--;
            this->mainWait.notify_all();
            this->threadWait.wait(lock, [this] {
                return !this->jobs.empty() || this->stopThreads;
            });
            if (this->stopThreads) {
                return;
            }
            auto job = this->jobs.front();
            this->jobs.pop();
            this->activeThreads++;
            lock.unlock();
            job();
        }
    }

   public:
    ThreadPool(long long threadCount) {
        this->threadCount = threadCount;
        this->activeThreads = 0;
        this->jobCount = 0;
        this->stopThreads = false;
        this->isActive = false;
        this->threads.resize(threadCount);
    }
    ThreadPool() {
        ThreadPool((long long)std::thread::hardware_concurrency());
    }
    void start() {
        if (this->isActive) {
            return;
        }
        this->activeThreads = this->threadCount;
        for (long long i = 0; i < this->threadCount; i++) {
            this->threads[i] = std::thread([this] { this->threadLoop(); });
        }
        this->isActive = true;
    }
    void stop() {
        if (!this->isActive) {
            return;
        }
        std::unique_lock<std::mutex> lock(this->threadLock);
        this->stopThreads = true;
        lock.unlock();
        this->threadWait.notify_all();
        for (std::thread& currThread : this->threads) {
            currThread.join();
        }
        this->threads.clear();
        std::queue<std::function<void()>> emptyQueue;
        this->jobs = emptyQueue;
        this->isActive = false;
    }
    void wait(std::ostream& stream) {
        std::unique_lock<std::mutex> lock(this->threadLock);
        auto start = std::chrono::steady_clock::now();
        auto initStart = start;
        this->mainWait.wait(lock, [this, &stream, &start, &initStart] {
            auto stop = std::chrono::steady_clock::now();
            stream << "\nqueuedJobs: " << this->jobs.size()
                   << " \nactiveThreads: " << this->activeThreads;
            stream << "\nElapsedTime: ";
            timer::printTime(stream, initStart, stop);
            stream << "lastCompetion: ";
            timer::printTime(stream, start, stop);
            start = stop;
            return this->jobs.empty() && this->activeThreads == 0;
        });
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
    void addJob(const std::function<void()>& job) {
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
