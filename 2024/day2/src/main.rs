use std::time::Instant;
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

fn part1(inputs: &[Vec<i32>]) -> i32 {
    let total = inputs.iter().filter(|x| check_good(x)).count();

    return total as i32;
}

fn part2(inputs: &[Vec<i32>]) -> i32 {
    let total = inputs.iter().filter(|x| check_almost_good(x)).count();

    return total as i32;
}

fn main() {
    let inputs = get_input();

    let start_part_1 = Instant::now();
    let result_part_1 = part1(&inputs);
    let end_part_1 = Instant::now();
    println!("Part 1: {} ( {:.2?} )", result_part_1, end_part_1.duration_since(start_part_1));

    let start_part_2 = Instant::now();
    let result_part_2 = part2(&inputs);
    let end_part_2 = Instant::now();
    println!("Part 2: {} ( {:.2?} )", result_part_2, end_part_2.duration_since(start_part_2));
}
