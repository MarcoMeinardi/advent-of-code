use std::collections::HashMap;
use std::time::Instant;
use std::io::{self, BufRead};

fn get_input() -> Vec<u64> {
    let stdin = io::stdin();

    let mut input = String::new();
    stdin.lock().read_line(&mut input).unwrap();
    return input.split_whitespace()
        .map(|x| x.parse().unwrap())
        .collect();
}

fn n_digits(stone: u64) -> usize {
    // stone.to_string().len()
    match stone {
        0..10                                => 1,
        10..100                              => 2,
        100..1000                            => 3,
        1000..10000                          => 4,
        10000..100000                        => 5,
        100000..1000000                      => 6,
        1000000..10000000                    => 7,
        10000000..100000000                  => 8,
        100000000..1000000000                => 9,
        1000000000..10000000000              => 10,
        10000000000..100000000000            => 11,
        100000000000..1000000000000          => 12,
        1000000000000..10000000000000        => 13,
        10000000000000..100000000000000      => 14,
        _ => panic!("Too many digits")
    }
}

fn expand_stone(stone: u64, depth: usize, cache: &mut HashMap<(u64, usize), u64>) -> u64 {
    if depth == 0 {
        return 1;
    }

    if let Some(&value) = cache.get(&(stone, depth)) {
        return value;
    }

    let result;
    if stone == 0 {
        result = expand_stone(1, depth - 1, cache);
    } else {
        let digits = n_digits(stone);
        if digits % 2 == 0 {
            let (first, second) = num_integer::div_rem(stone, 10_u64.pow((digits / 2) as u32));

            result = expand_stone(first, depth - 1, cache) + expand_stone(second, depth - 1, cache);
        } else {
            result = expand_stone(stone.checked_mul(2024).unwrap(), depth - 1, cache);
        }
    }

    cache.insert((stone, depth), result);

    return result;
}

fn part1(input: &[u64]) -> u64 {
    let mut cache = HashMap::new();
    return input.iter().map(|x| expand_stone(*x, 25, &mut cache)).sum();
}

fn part2(input: &[u64]) -> u64 {
    let mut cache = HashMap::new();
    return input.iter().map(|x| expand_stone(*x, 75, &mut cache)).sum();
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

