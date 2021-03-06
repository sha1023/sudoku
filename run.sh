#!/bin/bash

InputFile=complex.csv
PythonInputFile=simple.csv
echo "---"
echo ""
echo "python (with less complex input to avoid slowing things down too much.):"
time python sudoku.py ${PythonInputFile} | grep -v "^count\|^[0-9][0-9]\+"

echo "---"
echo ""
echo golang:
go build sudoku.go && time ./sudoku ${InputFile} | grep -v "^count\|^[0-9][0-9]\+"

echo "---"
echo ""
echo java:
javac Sudoku.java && time java Sudoku ${InputFile} | grep -v "^count\|^[0-9][0-9]\+"

echo "---"
echo ""
echo rust:
rustc -O sudoku.rs && time ./sudoku ${InputFile} | grep -v "^count\|^[0-9][0-9]\+"

echo "---"
echo ""
echo c++ without optimization flags:
g++ sudoku.cpp && time ./a.out ${InputFile} | grep -v "^count\|^[0-9][0-9]\+"

echo "---"
echo ""
echo c++:
g++ -O sudoku.cpp && time ./a.out ${InputFile} | grep -v "^count\|^[0-9][0-9]\+"

echo "---"
echo ""
echo c++ array version:
g++ -O sudoku_array.cpp && time ./a.out ${InputFile} | grep -v "^count\|^[0-9][0-9]\+"

