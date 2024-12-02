use std::io::{self, BufRead};
use std::collections::HashMap;

fn get_input() -> (Vec<i32>, Vec<i32>) {
    let stdin = io::stdin();
    let lines = stdin.lock().lines();

    let (left, right): (Vec<i32>, Vec<i32>) = lines
        .into_iter()
        .map(|line| {
            let parsed: Vec<i32> = line
                .unwrap()
                .split_whitespace()
                .map(|x| x.parse().unwrap())
                .collect();

            assert_eq!(parsed.len(), 2);
            return (parsed[0], parsed[1]);
        })
        .unzip();

    return (left, right);
}

fn part1(left: &[i32], right: &[i32]) {
    let mut left = left.to_owned();
    let mut right = right.to_owned();
    left.sort();
    right.sort();

    let total: i32 = left.iter().zip(right.iter()).map(|(a, b)| (a - b).abs()).sum();

    println!("Part 1: {}", total);
}

fn part2(left: &[i32], right: &[i32]) {
    let mut frequency: HashMap<i32, i32> = HashMap::new();

    for b in right.iter() {
        *frequency.entry(*b).or_insert(0) += 1;
    }

    let total: i32 = left.iter().map(|a| a * frequency.get(a).unwrap_or(&0)).sum();

    println!("Part 2: {}", total);
}

fn main() {
    let (left, right) = get_input();
    part1(&left, &right);
    part2(&left, &right);
}
