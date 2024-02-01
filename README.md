# Parker-Square

A program that searches for solutions to the magic square of squares.

## Getting Started

Clone the repository

```bash
git clone https://github.com/wizardassassin/Parker-Square.git
cd Parker-Square
```

Compile the source code  
**On windows**, replace the .out file extension with .exe

```bash
# intel compiler
icpx -pthread -fast main.cpp -o main.out
# or gnu compiler
g++ -pthread -Ofast -march=native -flto main.cpp -o main.out
```

Run the code

```bash
./main.out --minValue=0 --maxValue=100000 --vectorSize=10000 --threadCount=8
```

### Running MPI

Enter the directory

```bash
cd mpi
```

Compile the code using mpi

```bash
# intel-mpi compiler
mpicxx -cxx=icpx -fast main_mpi.cpp -o main_mpi.out
# openmpi compiler with g++
mpicxx -Ofast -march=native main_mpi.cpp -o main_mpi.out
```

Run the code

```bash
time mpirun -np 8 ./main_mpi.out 0 100000 10000
```

## Algorithm

The algorithm is based on the observation that opposite sides of a magic square have to sum up to the same total.

```
1   1   2   3   2
  +---+---+---+
1 | a | b | c |
  +---+---+---+
2 | d | e | f |
  +---+---+---+
3 | g | h | i |
  +---+---+---+
```

Row 2 = Col 2 = Diag 1 = Diag 2  
$d+e+f=b+e+h=a+e+i=c+e+g$  
$d+f=b+h=a+i=c+g$

## Results

The search space I chose was from $0$ to $5000000^2$ i.e. the first $2.5*10^{13}$ or 25,000,000,000,000 numbers. The computation took 109.3 hours, or a little over 4.5 days on an intel compute node with 44 cores and 256 GB of ram. 149557 separate files/jobs were created in the compute process.

Sadly, no suitable numbers were found that satisfy the magic square of squares. The aggregated results can be found in [aggregated_0_5mil.txt](./results/aggregated_0_5mil.txt).

An interesting side note is that for every set of diagonal numbers, the horizontal condition was never satisfied (only the vertical condition was satisfied). Also, only one pair satisfied the vertical condition per set.

If I were to extend the search range to the max value of a long long, which is $2^{63}-1$. The computation would take ~1680190.94 days or about 46.033 centuries. If I modified the code to use an unsigned long long ($2^{64}-1$), it would take about 92.065 centuries.

## Notes

If $a=371, b=559, c=149, d=541, e=49, f=421$  
then $a^2+f^2=c^2+d^2=b^2+e^2$  
and $a^2+b^2+c^2=d^2+e^2+f^2$  
and $a^4+b^4+c^4=d^4+e^4+f^4$
