// use itertools::Itertools;
// use itertools::FoldWhile::{Continue, Done};
use std::time::Instant;
use std::io::{self, BufRead};

fn get_input() -> Vec<(u64, Vec<u64>)> {
    let stdin = io::stdin();
    return stdin.lock().lines().map(|line| {
        let line = line.unwrap();
        let (target, rest) = line.split_once(": ").unwrap();
        let target = target.parse().unwrap();

        let values: Vec<u64> = rest.split(' ').map(|v| v.parse().unwrap()).collect();

        return (target, values);
    }).collect();
}

fn part1(input: &[(u64, Vec<u64>)]) -> u64 {
    fn try_all(target: u64, values: &[u64], index: usize, acc: u64) -> bool {
        if index == values.len() {
            return acc == target;
        }

        let value = values[index];
        return
            try_all(target, values, index + 1, acc + value) ||
            try_all(target, values, index + 1, acc * value);
    }

    fn check_possible(target: u64, values: &[u64]) -> bool {
        return try_all(target, values, 1, values[0]);
    }

    return input.iter()
        .filter_map(|(target, values)| 
            if check_possible(*target, values) {
                return Some(*target);
            } else {
                return None;
            }
        )
        .sum();

    // return input.iter().filter(|(target, values)|
    //     vec![['+', '*']; values.len() - 1].iter().multi_cartesian_product().any(|ops|
    //         values.iter().skip(1).zip(ops.iter()).fold(values[0], |acc, (&value, &op)|
    //             match op {
    //                 '+' => acc + value,
    //                 '*' => acc * value,
    //                 _ => panic!()
    //             }
    //         ) == *target
    //     )
    // ).map(|(target, _)| *target).sum();
}


fn part2(input: &[(u64, Vec<u64>)]) -> u64 {
    fn concat(a: u64, b: u64) -> u64 {
        // return a * 10_u64.pow(((b + 1) as f64).log10().ceil() as u32) + b
        match b {
            0..10     => return a * 10   + b,
            10..100   => return a * 100  + b,
            100..1000 => return a * 1000 + b,
            _ => panic!()
        }
    }

    fn try_all(target: u64, values: &[u64], index: usize, acc: u64) -> bool {
        if index == values.len() {
            return acc == target;
        }

        let value = values[index];
        return
            try_all(target, values, index + 1, acc + value) ||
            try_all(target, values, index + 1, acc * value) ||
            try_all(target, values, index + 1, concat(acc, value));
    }

    fn check_possible(target: u64, values: &[u64]) -> bool {
        return try_all(target, values, 1, values[0]);
    }

    return input.iter()
        .filter_map(|(target, values)|
            if check_possible(*target, values) {
                Some(*target)
            } else {
                None
            }
        )
        .sum();

    // return input.iter().filter(|(target, values)|
    //     vec![['+', '*', '|']; values.len() - 1].iter().multi_cartesian_product().any(|ops|
    //         values.iter().skip(1).zip(ops.iter()).fold_while(values[0], |acc, (&value, &op)| {
    //             let val = match op {
    //                 '+' => acc + value,
    //                 '*' => acc * value,
    //                 '|' => concat(acc, value),
    //                 _ => panic!()
    //             };
    //
    //             if val > *target {
    //                 return Done(0);
    //             }
    //             return Continue(val);
    //         }).into_inner() == *target
    //     )
    // ).map(|(target, _)| *target).sum();
}

fn main() {
    let input = get_input();

    let start_part_1 = Instant::now();
    let result_part_1 = part1(&input);
    let end_part_1 = Instant::now();
    println!("Part 1: {} ( {:.2?} )", result_part_1, end_part_1.duration_since(start_part_1));

    let start_part_2 = Instant::now();
    let result_part_2 = part2(&input);
    let end_part_2 = Instant::now();
    println!("Part 2: {} ( {:.2?} )", result_part_2, end_part_2.duration_since(start_part_2));
}
