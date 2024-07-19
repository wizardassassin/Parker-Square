CXX = g++
CXXFLAGS = -std=c++17 -pthread -Ofast -march=native -flto
MPICXX = mpicxx

.PHONY: all

all: main main_quiet main_mpi

main:
	$(CXX) $(CXXFLAGS) main.cpp -o main.out

main_quiet:
	$(CXX) $(CXXFLAGS) main_quiet.cpp -o main_quiet.out

main_threaded:
	$(CXX) $(CXXFLAGS) threaded_compute/main_threaded.cpp -o main_threaded.out

main_mpi:
	$(MPICXX) $(CXXFLAGS) mpi/main_mpi.cpp -o main_mpi.out

main_mpi2:
	$(MPICXX) $(CXXFLAGS) mpi2/main_mpi2.cpp -o main_mpi2.out

main_mpi2_mem:
	$(MPICXX) $(CXXFLAGS) mpi2_mem/main_mpi2_mem.cpp -o main_mpi2_mem.out

clean:
	rm -f main_*.out compute_*.txt aggregated_*.txt mpi_*.txt
