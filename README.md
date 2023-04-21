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
icpx -fast main.cpp -o main.out
# or gnu compiler
g++ -Ofast -march=native -flto main.cpp -o main.out
```

Run the code

```bash
./main.out --computeProgram=1 --minValue=0 --maxValue=100000 --vectorSize=10000 --threadCount=8
```
