import java.util.ArrayList;
import java.util.List;

public class Sudoku {
    public static void print(int[] array){
        for(int element: array){
            System.out.print(element);
            System.out.print(" ");
        }
    }

    public static void print(int[][] array) {
        for(int[] element: array){
            print(element);
            System.out.print("\n");
        }
    }

    private static int[][] populate(){
        return new int[][] {
            {8, 0, 0, 0, 0, 0, 2, 0, 7},
            {0, 0, 1, 8, 0, 2, 5, 0, 0},
            {0, 2, 0, 0, 7, 0, 0, 6, 8},
            //
            //{0, 6, 8, 0, 5, 0, 0, 2, 0},
            {0, 6, 8, 0, 0, 0, 0, 2, 0},
            //{0, 1, 9, 0, 0, 8, 7, 4, 0},
            {0, 0, 0, 0, 0, 0, 7, 4, 0},
            {0, 0, 0, 0, 0, 0, 0, 8, 0},
            //
            {0, 8, 0, 4, 0, 1, 0, 0, 2},
            {1, 0, 2, 0, 3, 0, 8, 0, 0},
            {9, 0, 0, 2, 8, 0, 0, 0, 3}};
    }

    private static void clear(boolean[] seen){
        for(int i=0;i<9;i++){
            seen[i] = false;
        }
    }

    private static boolean isNotDup(int num, boolean[] seen){
        if(num != 0){
            if(seen[num - 1]){
                return false;
            }
            seen[num - 1] = true;
        }
        return true;
    }

    private static boolean invalid(int[][] board){
        boolean row[] = new boolean[9];
        boolean column[] = new boolean[9];
        boolean box[] = new boolean[9];
        for(int i=0; i<board.length; i++) {
            clear(row);
            clear(column);
            clear(box);
            for(int j=0; j<board[i].length; j++) {
                boolean result = isNotDup(board[i][j], row) && isNotDup(board[j][i], column) && isNotDup(board[3*(i/3)+j/3][3*(i%3)+j%3], box);
                if(!result){
                    return true;
                }
            }
        }
        return false;
    }

    private static List<int[][]> guessAndCheck(int[][] board, int[] count) {
        count[0] += 1;
        if(count[0]%10000 == 0) {
            System.out.println(count[0]);
        }
        List<int[][]> validGuesses = new ArrayList<int[][]> ();
        if(invalid(board)){
            return validGuesses;
        }
        for(int i=0; i<board.length; i++) {
            for(int j=0; j<board[i].length; j++) {
                if(board[i][j] == 0){
                    for(int guess=1; guess<10; guess++){
                        board[i][j] = guess;
                        validGuesses.addAll(guessAndCheck(board, count));
                    }
                    board[i][j] = 0;
                    return validGuesses;
                }
            }
        }
        ////Nothing has been returned, hence the board must be complete and valid
        validGuesses.add(board);
        return validGuesses;
    }

    public static void main(String args[]) {
        int[][] board = populate();
        System.out.println("Solving:\n");
        print(board);

        int count[] = new int[] {0};
        List<int[][]> solutions = guessAndCheck(board, count);
        System.out.println("computed " + solutions.size() + " solution(s), after " + count[0] + " guesses:\n\n");
        //for(vector< vector< vector< int > > >::size_type i=0; i<solutions.size(); i++){
        //    print(solutions[i]);
        //}
    }
}


