# include <iostream>
# include <vector>
# include <unordered_set>
using namespace std;

void print(vector<int> &v){
    for(vector<int>::size_type i=0; i< v.size(); i++){
        cout << v[i];
        cout << " ";
    }
    cout << "\n";
}

void print(vector< vector<int> > &v){
    for(vector<int>::size_type i=0; i < v.size(); i++){
        print(v[i]);
    }
    cout << "\n";
}

void print(int* x, int size){
    for(int i=0; i<size; i++){
        cout << x[i];
        cout << "\n";
    }
}

vector< vector<int> > populate() {
    //insert your sudoku here.
    int y[9][9] = {
        {8, 0, 0, 0, 0, 0, 2, 0, 7},
        {0, 0, 1, 8, 0, 2, 5, 0, 0},
        {0, 2, 0, 0, 7, 0, 0, 6, 8},
        //
        {0, 6, 8, 0, 5, 0, 0, 2, 0},
        {0, 1, 9, 0, 0, 8, 7, 4, 0},
        {0, 0, 0, 0, 0, 0, 0, 8, 0},
        //
        {0, 8, 0, 4, 0, 1, 0, 0, 2},
        {1, 0, 2, 0, 3, 0, 8, 0, 0},
        {9, 0, 0, 2, 8, 0, 0, 0, 3}};
    vector< vector<int> > board;
    for(int i=0; i<9; i++){
        vector<int> temp (y[i], y[i] + sizeof(y[i])/sizeof(y[i][0]));
        board.push_back(temp);
    }
    return board;
}

bool is_not_dup(int num, unordered_set<int> &seen){
    if(num != 0){
        if(seen.find(num) != seen.end()){
            return false;
        }
        seen.insert(num);
    }
    return true;
}


bool invalid(vector< vector<int> > &board){
    unordered_set< int > row;
    unordered_set< int > column;
    unordered_set< int > box;
    for(vector< vector< int > >::size_type i=0; i<board.size(); i++) {
        row.clear();
        column.clear();
        box.clear();
        for(vector< int >::size_type j=0; j<board[i].size(); j++) {
            bool result = is_not_dup(board[i][j], row) && is_not_dup(board[j][i], column) && is_not_dup(board[3*(i/3)+j/3][3*(i%3)+j%3], box);
            if(!result){
                return true;
            }
        }
    }
    return false;
}

void append_all(vector < vector< vector <int> > > &prefix, vector< vector< vector< int > > > &suffix) {
    for(vector< vector< vector< int > > >::size_type i=0; i<suffix.size(); i++){
        prefix.push_back(suffix[i]);
    }
}

vector< vector< vector< int > > > guess_and_check(vector< vector<int> > &board, int *count) {
    *count += 1;
    if(*count%10000 == 0) {
        cout << *count;
        cout << "\n";
    }
    vector< vector< vector< int > > > valid_guesses;
    if(invalid(board)){
        return valid_guesses;
    }
    for(vector< vector< int > >::size_type i=0; i<board.size(); i++) {
        for(vector< int >::size_type j=0; j<board[i].size(); j++) {
            if(board[i][j] == 0){
                for(int guess=1; guess<10; guess++){
                    board[i][j] = guess;
                    vector< vector< vector< int > > > valid = guess_and_check(board, count);
                    append_all(valid_guesses, valid);
                }
                board[i][j] = 0;
                return valid_guesses;
            }
        }
    }
    ////Nothing has been returned, hence the board must be complete and valid
    valid_guesses.push_back(board);
    return valid_guesses;
}

int main() {
    vector< vector<int> > board = populate();

    cout << "Solving:\n\n";
    print(board);

    int count = 0;
    vector< vector< vector< int > > > solutions = guess_and_check(board, &count);
    cout << "computed " << solutions.size() << " solution(s), after " << count << " guesses:\n\n";
    for(vector< vector< vector< int > > >::size_type i=0; i<solutions.size(); i++){
        print(solutions[i]);
    }
}

