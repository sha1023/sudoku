# include <iostream>
# include <vector>
using namespace std;

void populate(int board[9][9]){
    int y[9][9] = {
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
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            board[i][j] = y[i][j];
        }
    }
}

bool is_not_dup(int num, bool *seen){
    if(num != 0){
        if(seen[num - 1]){
            return false;
        }
        seen[num - 1] = true;
    }
    return true;
}

void clear(bool seen[9]) {
    for(int i=0;i<9;i++){
        seen[i] = false;
    }
}

bool invalid(int board[9][9]){
    bool row[9];
    bool column[9];
    bool box[9];
    for(int i=0; i<9; i++) {
        clear(row);
        clear(column);
        clear(box);
        for(int j=0; j<9; j++) {
            bool result = is_not_dup(board[i][j], row) && is_not_dup(board[j][i], column) && is_not_dup(board[3*(i/3)+j/3][3*(i%3)+j%3], box);
            if(!result){
                return true;
            }
        }
    }
    return false;
}

void append(vector < vector< vector <int> > > &prefix, int suffix[9][9]) {
    vector< vector<int> > board;
    for(int i=0; i<9; i++){
        vector<int> temp (suffix[i], suffix[i] + 9);
        board.push_back(temp);
    }
    prefix.push_back(board);
}

void guess_and_check(vector< vector< vector< int > > > &valid_guesses, int board[9][9], int &count) {
    count += 1;
    if(count%10000 == 0) {
        cout << count << "\n";
    }
    if(invalid(board)){
        return;
    }
    for(int i=0; i<9; i++) {
        for(int j=0; j<9; j++) {
            if(board[i][j] == 0){
                for(int guess=1; guess<10; guess++){
                    board[i][j] = guess;
                    guess_and_check(valid_guesses, board, count);
                }
                board[i][j] = 0;
                return;
            }
        }
    }
    ////Nothing has been returned, hence the board must be complete and valid
    append(valid_guesses, board);
}

void print(int x[9]){
    for(int i=0; i<9; i++){
        cout << x[i] << " ";
    }
}

void print(int x[9][9]){
    for(int i=0; i<9; i++){
        print(x[i]);
        cout << "\n";
    }
}

int main() {
    int board[9][9];
    populate(board);

    cout << "Solving:\n\n";
    print(board);

    int count = 0;
    vector< vector< vector< int > > > solutions;
    guess_and_check(solutions, board, count);
    cout << "\n";
    cout << "computed " << solutions.size() << " solution(s), after " << count << " guesses:\n\n";
    //for(vector< vector< vector< int > > >::size_type i=0; i<solutions.size(); i++){
    //    print(solutions[i]);
    //}
}

