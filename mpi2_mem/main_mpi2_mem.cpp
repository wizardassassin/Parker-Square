#include <mpi.h>

#include <cassert>
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

#include "compute_increment.cpp"

int rank = -1;
int size = -1;

int64_t minValue = 0;
int64_t maxValue = 10000;
int64_t vectorSize = 4000;

std::string getTime() {
    auto time =
        std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::string str_time = std::ctime(&time);
    auto last_char = str_time.size() - 1;
    return str_time.substr(0, last_char);
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

    int64_t nextValue = (int64_t)std::sqrt(
        maxValue * maxValue + vectorSize * vectorSize / (long double)size);
    assert(nextValue != maxValue);

    std::stringstream stream;

    int64_t range = maxValue - minValue;

    int task_size = range / size;
    if (rank < range % size) task_size++;

    stream << "Process " << rank << " of " << size << " on " << name << " with "
           << task_size << " tasks at " << getTime() << std::endl;
    std::cout << stream.str();
    stream.str("");

    std::string outFileName =
        "mpi_" + std::to_string(rank) + "_" + std::to_string(size) + ".txt";
    std::ofstream outFile;
    outFile.open(outFileName);

    std::vector<std::vector<int64_t>> vect(2 * maxValue + 1);
    // std::vector<std::vector<int64_t>> vect;
    // vect.shrink_to_fit();
    for (int64_t i = minValue + rank; i < maxValue; i += size) {
        compute_increment::main_compute(outFile, vect, i);
        outFile << std::flush;
    }

    stream << "Process " << rank << " completed at " << getTime() << std::endl;
    std::cout << stream.str();

    outFile.close();
    MPI::Finalize();
    return 0;
}
