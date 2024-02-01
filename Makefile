CXX = g++
CXXFLAGS = -std=c++17 -pthread -Ofast -march=native -flto
MPICXX = mpicxx

.PHONY: all

all: main main_quiet main_mpi

main:
	$(CXX) $(CXXFLAGS) main.cpp -o main.out

main_quiet:
	$(CXX) $(CXXFLAGS) main_quiet.cpp -o main_quiet.out

main_mpi:
	$(MPICXX) $(CXXFLAGS) mpi/main_mpi.cpp -o main_mpi.out

clean:
	rm main.out main_quiet.out main_mpi.out compute_*.txt aggregated_*.txt mpi_*.txt
