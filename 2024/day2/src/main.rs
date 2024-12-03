use std::io::{self, BufRead};
use num_traits::sign::signum;

fn get_input() -> Vec<Vec<i32>> {
    let stdin = io::stdin();
    let lines = stdin.lock().lines();

    return lines.
        into_iter()
        .map(|line| line.unwrap()
            .split_whitespace()
            .map(|x| x.parse().unwrap())
            .collect()
        ).collect();
}

fn check_good(row: &[i32]) -> bool {
    let diff_0 = row[1] - row[0];

    for i in 0..(row.len() - 1) {
        let diff = row[i + 1] - row[i];
        if signum(diff) != signum(diff_0) || diff.abs() < 1 || diff.abs() > 3 {
            return false;
        }
    }

    return true;
}

fn check_almost_good(row: &[i32]) -> bool {
    if check_good(row) {
        return true;
    }

    for bad in 0..row.len() {
        let good_row: Vec<i32> = row.iter().enumerate().filter_map(|(ind, x)|
            if ind == bad {
                None
            } else {
                Some(*x)
            }
        ).collect();

        if check_good(&good_row) {
            return true;
        }
    }

    return false;
}

fn part1(inputs: &[Vec<i32>]) {
    let total = inputs.iter().filter(|x| check_good(x)).count();

    println!("Part 1: {}", total);
}

fn part2(inputs: &[Vec<i32>]) {
    let total = inputs.iter().filter(|x| check_almost_good(x)).count();

    println!("Part 2: {}", total);
}

fn main() {
    let inputs = get_input();
    part1(&inputs);
    part2(&inputs);
}
