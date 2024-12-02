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

fn part1(inputs: &[Vec<i32>]) {
    let total = inputs.iter().map(|row| check_good(row) as i32).sum::<i32>();

    println!("Part 1: {}", total);
}

fn part2(inputs: &[Vec<i32>]) {
    let total: i32 = inputs.iter().map(|row| {
        if check_good(row) {
            return 1;
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
                return 1;
            }
        }

        return 0;
    }).sum();

    println!("Part 2: {}", total);
}

fn main() {
    let inputs = get_input();
    part1(&inputs);
    part2(&inputs);
}
