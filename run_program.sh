#!/bin/bash

if [ "$1" = "main_mpi" ]; then
    mpirun ./$1 $2 $3 $4
else
    ./$1 --minValue=$2 --maxValue=$3 --vectorSize=$4 --threadCount=0
fi
