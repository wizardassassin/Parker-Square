#include <fstream>
#include <iostream>
#include <thread>
#include <vector>

#include "compute_increment.hpp"
#include "thread_pool.hpp"

int main(int argc, char const* argv[]) {
    if (argc < 3) return 1;

    const long long min_val = std::stoll(argv[1]);
    const long long max_val = std::stoll(argv[2]);
    const long long thread_count =
        (argc >= 4) ? std::stoll(argv[3]) : std::thread::hardware_concurrency();
    const std::string prefix = (argc >= 5) ? argv[4] : "thread";

    ThreadPool::ThreadPool pool(thread_count);
    std::vector<std::ofstream> file_store(thread_count);
    for (long long i = 0; i < thread_count; i++)
        file_store[i].open(prefix + "_" + std::to_string(i) + "_" +
                           std::to_string(thread_count) + ".txt");

    std::vector<std::vector<std::vector<int64_t>>> vect_store(thread_count);

    for (size_t i = min_val; i < max_val; i++) {
        pool.addJob([i, &file_store, &vect_store, max_val](long long threadId) {
            auto& file = file_store[threadId];
            auto& vect = vect_store[threadId];
            vect.resize(2 * max_val + 1);
            ComputeIncrement::main_compute(file, vect, i);
            for (size_t j = 0; j < 2 * i + 1; j++) {
                vect[j].clear();
                vect[j].shrink_to_fit();
            }
        });
    }

    pool.start();
    pool.wait(std::cout);
    pool.stop();

    for (long long i = 0; i < thread_count; i++) file_store[i].close();

    return 0;
}
