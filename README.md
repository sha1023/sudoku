# sudoku

Three sudoku solvers. They do nothing clever, but they get the job done. If there are too many solutions I recommend learning to use "ctrl-C."

syntax: "python sudoku.py" or "go run sudoku.go" or "g++ sudoku.cpp && ./a.out"

On my machine the go solver is 34 times faster than the python solver, and about as legible.

After compiling with optimizations, c++ is the clear winner, as I'd expect.

Time measurements were made using:

```
time python sudoku.py
go build sudoku.go && time ./sudoku
g++ -O sudoku.cpp && time ./a.out
g++ -O sudoku_array.cpp && time ./a.out
```

