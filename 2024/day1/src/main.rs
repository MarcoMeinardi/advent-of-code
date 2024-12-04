use std::time::Instant;
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

fn part1(left: &[i32], right: &[i32]) -> i32 {
    let mut left = left.to_owned();
    let mut right = right.to_owned();
    left.sort_unstable();
    right.sort_unstable();

    let total: i32 = left.iter().zip(right.iter()).map(|(a, b)| (a - b).abs()).sum();

    return total;
}

fn part2(left: &[i32], right: &[i32]) -> i32 {
    let mut frequency: HashMap<i32, i32> = HashMap::new();

    for b in right {
        *frequency.entry(*b).or_insert(0) += 1;
    }

    let total: i32 = left.iter().map(|a| a * frequency.get(a).unwrap_or(&0)).sum();

    return total;
}

fn main() {
    let (left, right) = get_input();

    let start_part_1 = Instant::now();
    let result_part_1 = part1(&left, &right);
    let end_part_1 = Instant::now();
    println!("Part 1: {} ( {:.2?} )", result_part_1, end_part_1.duration_since(start_part_1));

    let start_part_2 = Instant::now();
    let result_part_2 = part2(&left, &right);
    let end_part_2 = Instant::now();
    println!("Part 2: {} ( {:.2?} )", result_part_2, end_part_2.duration_since(start_part_2));
}
