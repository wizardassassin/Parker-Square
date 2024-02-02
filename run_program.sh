#!/bin/bash

if [[ "$1" == *"mpi"* ]]; then
    mpirun --use-hwthread-cpus ./$1.out $2 $3 $4
else
    ./$1.out --minValue=$2 --maxValue=$3 --vectorSize=$4 --threadCount=0
fi
