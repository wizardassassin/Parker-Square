#include <mpi.h>

#include <chrono>
#include <cmath>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <utility>
#include <vector>

#include "compute_quiet.cpp"

int rank = -1;
int size = -1;

int64_t minValue = 0;
int64_t maxValue = 10000;
int64_t vectorSize = 4000;
int64_t rangeCount = -1;

std::vector<std::pair<int64_t, int64_t>> ranges;

std::string getTime() {
    auto time =
        std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::string str_time = std::ctime(&time);
    auto last_char = str_time.size() - 1;
    return str_time.substr(0, last_char);
}

void init_tasks() {
    int64_t i = minValue;
    while (i < maxValue) {
        int64_t nextValue =
            std::min((int64_t)std::sqrt(i * i + vectorSize * vectorSize /
                                                    (long double)size),
                     maxValue);
        ranges.push_back(std::pair(i, nextValue));
        i = nextValue;
    }
    ranges.shrink_to_fit();
    rangeCount = ranges.size();
}

int main(int argc, char** argv) {
    MPI::Init(argc, argv);
    int length = 0;
    char name[MPI_MAX_PROCESSOR_NAME];
    rank = MPI::COMM_WORLD.Get_rank();
    size = MPI::COMM_WORLD.Get_size();
    MPI::Get_processor_name(name, length);

    minValue = 0;
    maxValue = 10000;
    vectorSize = 4000;

    if (argc == 4) {
        minValue = std::stoll(argv[1]);
        maxValue = std::stoll(argv[2]);
        vectorSize = std::stoll(argv[3]);
    }

    init_tasks();

    std::vector<std::pair<int64_t, int64_t>> my_tasks;
    std::stringstream stream;

    for (int i = 0; i < rangeCount; i++) {
        if (i % size == rank) my_tasks.push_back(ranges[i]);
    }
    my_tasks.shrink_to_fit();

    int task_size = my_tasks.size();

    stream << "Process " << rank << " of " << size << " on " << name << " with "
           << task_size << " tasks at " << getTime() << std::endl;
    std::cout << stream.str();

    std::string outFileName =
        "mpi_" + std::to_string(rank) + "_" + std::to_string(size) + ".txt";
    std::ofstream outFile;
    outFile.open(outFileName);

    for (int i = 0; i < task_size; i++) {
        auto range = my_tasks[i];
        compute_quiet::main_compute(outFile, range.first, range.second);
        outFile << std::flush;
    }

    stream.str("");
    stream << "Process " << rank << " completed at " << getTime() << std::endl;
    std::cout << stream.str();

    outFile.close();
    MPI::Finalize();
    return 0;
}
