use std::env;
use std::fs::File;
use std::io::{BufRead, BufReader};

fn populate(file_name: &str) -> [[u8; 9]; 9] {
    let file = File::open(file_name).unwrap();
    let reader = BufReader::new(file);
    let mut board: [[u8; 9]; 9] = [[0;9];9];
    for (i, line) in reader.lines().enumerate() {
        let line_str = line.unwrap();
        let elements = line_str.split(",");
        for (j, element) in elements.enumerate() {
            board[i][j] = element.parse::<u8>().unwrap()
        }
    }
    board
}

fn is_not_dup(num: usize, seen: &mut [bool]) -> bool {
    if num != 0 {
        if seen[num - 1] {
            return false;
        }
        seen[num - 1] = true;
    }
    true
}

fn clear(seen: &mut [bool]) {
    for it in seen.iter_mut() {
        *it = false;
    }
}

fn invalid(board: &[[u8; 9]; 9]) -> bool {
    let mut row = [false; 9];
    let mut column = [false; 9];
    let mut bbox = [false; 9];
    for i in 0..9 {
        clear(&mut row);
        clear(&mut column);
        clear(&mut bbox);
        for j in 0..9 {
            let result = is_not_dup(board[i][j] as usize, &mut row) && is_not_dup(board[j][i] as usize, &mut column) && is_not_dup(board[3*(i/3)+j/3][3*(i%3)+j%3] as usize, &mut bbox);
            if !result {
                return true;
            }
        }
    }
    false
}

fn guess_and_check(board: &mut [[u8; 9]; 9], count: &mut u32) -> Vec<[[u8; 9]; 9]> {
    *count += 1;
    if *count % 10_000 == 0 {
        println!("{}", *count);
    }
    if invalid(board) {
        return vec![];
    }
    let mut valid_guesses = vec![];
    for i in 0..9 {
        for j in 0..9 {
            if board[i][j] == 0 {
                for guess in 1..10 {
                    board[i][j] = guess;
                    valid_guesses.append(&mut guess_and_check(board, count));
                }
                board[i][j] = 0;
                return valid_guesses;
            }
        }
    }
    // Nothing has been returned, hence the board must be complete and valid
    vec![*board]
}

fn pretty_print(board: &[[u8; 9]; 9]) {
    for row in board.iter() {
        println!("{:?}", row);
    }
}

fn main() {
    let args: Vec<_> = env::args().collect();
    if args.len() < 2 {
        println!("please supply an input file");
        return;
    }
    let mut board = populate(&args[1]);
    pretty_print(&board);
    println!("");
    let mut count = 0;
    let solutions = guess_and_check(&mut board, &mut count);
    println!("computed {} solution(s), after {} guesses", solutions.len(), count);
}
