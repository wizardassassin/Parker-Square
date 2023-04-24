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

## Notes

There are

If $a=371, b=559, c=149, d=541, e=49, f=421$  
then $a^2+f^2=c^2+d^2=b^2+e^2$  
and $a^2+b^2+c^2=d^2+e^2+f^2$  
and $a^4+b^4+c^4=d^4+e^4+f^4$
