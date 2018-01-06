# sudoku

Three sudoku solvers. They do nothing clever, but they get the job done. If there are too many solutions I recommend learning to use "ctrl-C."

syntax: "python sudoku.py" or "go run sudoku.go" or "g++ sudoku.cpp && ./a.out"

On my machine the go solver is 34 times faster than the python solver, and about as legible.

`sudoku_array.cpp` is the fastest of the c++ solvers. It's currently twice as fast as `sudoku.cpp` and still half as fast as the go solver.

Time measurements were made using:
`time python sudoku.py`
`g++ sudoku.cpp && time ./a.out`
`g++ sudoku_array.cpp && time ./a.out`
`time go run sudoku.go`

