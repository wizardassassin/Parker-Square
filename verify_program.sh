#!/bin/bash

if [[ "$1" == *"thread"* ]]; then
    diff <(grep -h " | " ./$1 | sort) <(cat ./tests/test_0_50000_odd.txt | sort)
else
    diff <(grep -h " | " ./$1 | sort) <(cat ./tests/test_0_50000.txt | sort)
fi
