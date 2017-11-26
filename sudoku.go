package main

import (
	"fmt"
)

func Populate() [][]int {
	//insert your sudoku here.
	return [][]int{
		[]int{8, 0, 0, 0, 0, 0, 2, 0, 7},
		[]int{0, 0, 1, 8, 0, 2, 5, 0, 0},
		[]int{0, 2, 0, 0, 7, 0, 0, 6, 8},

		[]int{0, 6, 8, 0, 5, 0, 0, 2, 0},
		[]int{0, 1, 9, 0, 0, 8, 7, 4, 0},
		[]int{0, 0, 0, 0, 0, 0, 0, 8, 0},

		[]int{0, 8, 0, 4, 0, 1, 0, 0, 2},
		[]int{1, 0, 2, 0, 3, 0, 8, 0, 0},
		[]int{9, 0, 0, 2, 8, 0, 0, 0, 3}}
}

func IsNotDup(num int, seen map[int]bool) bool {
	if num != 0 {
		_, contains := seen[num]
		if contains {
			return false
		}
		seen[num] = true
	}
	return true
}

func Invalid(board [][]int) bool {
	row := map[int]bool{}
	column := map[int]bool{}
	box := map[int]bool{}
	for i := range board {
		row = map[int]bool{}
		column = map[int]bool{}
		box = map[int]bool{}
		for j := range board {
			result := IsNotDup(board[i][j], row) && IsNotDup(board[j][i], column) && IsNotDup(board[3*(i/3)+j/3][3*(i%3)+j%3], box)
			if !result {
				return true
			}
		}
	}
	return false
}

func AppendAll(a [][][]int, b [][][]int) [][][]int {
	if len(b) == 0 {
		return a
	}
	c := make([][][]int, len(a)+len(b))
	for i, board := range a {
		c[i] = board
	}
	for i, board := range b {
		c[i+len(a)] = board
	}
	return c
}

func Copy(in [][]int) [][]int {
	out := make([][]int, len(in))
	for i, sub := range in {
		out[i] = make([]int, len(sub))
		for j, num := range sub {
			out[i][j] = num
		}
	}
	return out
}

func GuessAndCheck(board [][]int, count *int) [][][]int {
	*count += 1
	if *count%10000 == 0 {
		fmt.Println(*count)
	}
	if Invalid(board) {
		return [][][]int{}
	}
	validGuesses := [][][]int{}
	for i := range board {
		for j := range board {
			if board[i][j] == 0 {
				for guess := 1; guess < 10; guess++ {
					board[i][j] = guess
					validGuesses = AppendAll(validGuesses, GuessAndCheck(board, count))
				}
				board[i][j] = 0
				return validGuesses
			}
		}
	}
	//Nothing has been returned, hence the board must be complete and valid
	return [][][]int{Copy(board)}
}

func PrettyPrint(board [][]int) {
	for _, row := range board {
		fmt.Println(row)
	}
}

func main() {
	board := Populate()
	PrettyPrint(board)
	fmt.Println("")
	count := 0
	solutions := GuessAndCheck(board, &count)
	fmt.Println("computed", len(solutions), "solution(s), after", count, "guesses")
	for _, solution := range solutions {
		fmt.Println("")
		PrettyPrint(solution)
	}
}
