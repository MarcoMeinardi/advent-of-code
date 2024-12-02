use std::io::{self, BufRead};
use more_asserts::assert_ge;
use for_else::for_;
use num_traits::sign::signum;

fn get_input() -> Vec<Vec<i32>> {
    let stdin = io::stdin();
    let mut lines = stdin.lock().lines();

    let mut res = Vec::new();

    while let Some(Ok(line)) = lines.next() {
        let inputs: Vec<i32> = line
            .split_whitespace()
            .map(|x| x.parse().unwrap())
            .collect();

        assert_ge!(inputs.len(), 2);
        res.push(inputs);
    }

    return res;
}

fn part1(inputs: &Vec<Vec<i32>>) {
    let mut total = 0;

    for row in inputs {
        let diff_0 = row[1] - row[0];

        for_! { i in 0..(row.len() - 1) {
            let diff = row[i + 1] - row[i];
            if signum(diff) != signum(diff_0) || diff.abs() < 1 || diff.abs() > 3 {
                break;
            }
        } else {
            total += 1;
        } }
    }

    println!("Part 1: {}", total);
}

fn part2(inputs: &Vec<Vec<i32>>) {
    let mut total = 0;

    for row in inputs {
        let diff_0 = row[1] - row[0];

        for_! { i in 0..(row.len() - 1) {
            let diff = row[i + 1] - row[i];
            if signum(diff) != signum(diff_0) || diff.abs() < 1 || diff.abs() > 3 {
                break;
            }
        } else {
            total += 1;
            continue;
        } }

        for bad in 0..row.len() {
            let good_row: Vec<i32> = row.iter().enumerate().filter_map(|(ind, x)|
                if ind == bad {
                    None
                } else {
                    Some(x.clone())
                }
            ).collect();

            let diff_0 = good_row[1] - good_row[0];
            for_! { i in 0..(good_row.len() - 1) {
                let diff = good_row[i + 1] - good_row[i];
                if signum(diff) != signum(diff_0) || diff.abs() < 1 || diff.abs() > 3 {
                    break;
                }
            } else {
                total += 1;
                break;
            } }
        }

    }

    println!("Part 2: {}", total);
}

fn main() {
    let inputs = get_input();
    part1(&inputs);
    part2(&inputs);
}