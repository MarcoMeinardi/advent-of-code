use std::io::{self, BufRead};
use std::collections::HashMap;

fn get_input() -> Vec<(i32, i32)> {
    let stdin = io::stdin();
    let mut lines = stdin.lock().lines();

    let mut res = Vec::new();

    while let Some(Ok(line)) = lines.next() {
        let inputs: Vec<i32> = line
            .split_whitespace()
            .map(|x| x.parse().unwrap())
            .collect();

        assert_eq!(inputs.len(), 2);
        res.push((inputs[0], inputs[1]));
    }

    return res;
}

fn part1(input: &Vec<(i32, i32)>) {
    let mut total = 0;

    let mut left = Vec::new();
    let mut right = Vec::new();

    for (a, b) in input.iter() {
        left.push(*a);
        right.push(*b);
    }

    left.sort();
    right.sort();

    for (a, b) in left.iter().zip(right.iter()) {
        total += (a - b).abs();
    }

    println!("Part 1: {}", total);
}

fn part2(input: &Vec<(i32, i32)>) {
    let mut frequency: HashMap<i32, i32> = HashMap::new();

    for (_, b) in input.iter() {
        *frequency.entry(*b).or_insert(0) += 1;
    }

    let mut total = 0;

    for (a, _) in input.iter() {
        if let Some(b) = frequency.get(a) {
            total += a * b;
        }
    }

    println!("Part 2: {}", total);
}

fn main() {
    let input = get_input();
    part1(&input);
    part2(&input);
}
