#!/usr/bin/python
from __future__ import print_function
import copy
import doctest

def populate():
    #insert your sudoku here.
    return [[8,0,0, 0,0,0, 2,0,7],
            [0,0,1, 8,0,2, 5,0,0],
            [0,2,0, 0,7,0, 0,6,8],

            #[0,6,8, 0,5,0, 0,2,0],
            [0,6,8, 0,0,0, 0,2,0],
            [0,1,9, 0,0,8, 7,4,0],
            [0,0,0, 0,0,0, 0,8,0],

            [0,8,0, 4,0,1, 0,0,2],
            [1,0,2, 0,3,0, 8,0,0],
            [9,0,0, 2,8,0, 0,0,3]]

def is_not_dup(num, seen):
    if num != 0:
        if num in seen:
            return False
    seen.add(num)
    return True

def invalid(board):
    """
    >>> invalid([[8,0,0, 0,0,0, 2,0,7], [8,0,1, 8,0,2, 5,0,0], [0,2,0, 0,7,0, 0,6,8], [0,6,8, 0,5,0, 0,2,0], [0,1,9, 0,0,8, 7,4,0], [0,0,0, 0,0,0, 0,8,0], [0,8,0, 4,0,1, 0,0,2], [1,0,2, 0,3,0, 8,0,0], [9,0,0, 2,8,0, 0,0,3]])
    True
    >>> invalid([[8,0,8, 0,0,0, 2,0,7], [0,0,1, 8,0,2, 5,0,0], [0,2,0, 0,7,0, 0,6,8], [0,6,8, 0,5,0, 0,2,0], [0,1,9, 0,0,8, 7,4,0], [0,0,0, 0,0,0, 0,8,0], [0,8,0, 4,0,1, 0,0,2], [1,0,2, 0,3,0, 8,0,0], [9,0,0, 2,8,0, 0,0,3]])
    True
    >>> invalid([[8,0,0, 0,0,0, 2,5,7], [0,0,1, 8,0,2, 5,0,0], [0,2,0, 0,7,0, 0,6,8], [0,6,8, 0,5,0, 0,2,0], [0,1,9, 0,0,8, 7,4,0], [0,0,0, 0,0,0, 0,8,0], [0,8,0, 4,0,1, 0,0,2], [1,0,2, 0,3,0, 8,0,0], [9,0,0, 2,8,0, 0,0,3]])
    True
    >>> invalid([[8,0,0, 0,0,0, 2,0,7], [0,0,1, 8,0,2, 5,0,0], [0,2,0, 0,7,0, 0,6,8], [0,6,8, 0,5,0, 0,2,0], [0,1,9, 0,0,8, 7,4,0], [0,0,0, 0,0,0, 0,8,0], [0,8,0, 4,0,1, 0,0,2], [1,0,2, 0,3,0, 8,0,0], [9,0,0, 2,8,0, 0,0,3]])
    False
    """
    row = set()
    column = set()
    box = set()
    for i in range(len(board)):
        row = set()
        column = set()
        box = set()
        for j in range(len(board)):
            result = is_not_dup(board[i][j], row) and is_not_dup(board[j][i], column) and is_not_dup(board[3*(i//3) + j//3][3*(i%3)+j%3], box)
            if not result:
                return True
    return False

def guess_and_check(board, count):
    count[0] += 1
    if count[0] % 10000 == 0:
        print("count:", count)
    if invalid(board):
        return []
    valid_guesses = []
    for i in range(len(board)):
        for j in range(len(board)):
            if board[i][j] == 0: 
                for guess in range(1,10):
                    board[i][j] = guess
                    valid_guesses += guess_and_check(board, count)
                board[i][j] = 0
                return valid_guesses
    #Nothing has been returned, hence the board must be complete and valid
    return [copy.deepcopy(board)]

def pretty_print(board):
    for row in board:
        print(row)

def main():
    board = populate()
    pretty_print(board)
    print("")
    count = [0]
    solutions = guess_and_check(board, count)
    print("computed",  len(solutions), "solution(s), after", count[0], "guesses")
    for solution in solutions:
        print("")
        pretty_print(solution)

if __name__ == "__main__":
    doctest.testmod()
    main()
