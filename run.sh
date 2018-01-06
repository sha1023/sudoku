#!/bin/bash

time python sudoku.py | grep -v "^count\|^[0-9][0-9]\+"
go build sudoku.go && time ./sudoku | grep -v "^count\|^[0-9][0-9]\+"
g++ -O sudoku.cpp && time ./a.out | grep -v "^count\|^[0-9][0-9]\+"
g++ -O sudoku_array.cpp && time ./a.out  | grep -v "^count\|^[0-9][0-9]\+"

