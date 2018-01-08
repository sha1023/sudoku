# sudoku

Three sudoku solvers. They do nothing clever, but they get the job done. If there are too many solutions I recommend learning to use "ctrl-C."

On my machine the go solver is 34 times faster than the python solver, and about as legible.

Strangely enough Java seems comparable to go, although slower to write.

After compiling with optimizations, c++ is the clear winner, as I'd expect.

To run performance measurements simply use:

```
bash run.sh
```

