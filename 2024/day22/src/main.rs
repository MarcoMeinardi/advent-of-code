use std::time::Instant;
use std::io::{self, BufRead};


// This table can be precomputed at compile time, but rust sucks and it takes 2 minutes
//
// const fn const_step(mut x: u64) -> u64 {
//     x = ((x <<  6) ^ x) & 0xffffff;
//     x = ((x >>  5) ^ x) & 0xffffff;
//     x = ((x << 11) ^ x) & 0xffffff;
//
//     return x;
// }
//
// const fn precompute_table() -> [u64; 1 << 24] {
//     let mut table = [0; 1 << 24];
//
//     let mut x = 1;
//     let mut i = 0;
//     while i < 2000 {
//         x = const_step(x);
//         i += 1;
//     }
//
//     let mut px = 1;
//
//     i = 0;
//     while i < 1 << 24 {
//         table[px as usize] = x;
//         px = const_step(px);
//         x = const_step(x);
//         i += 1;
//     }
//
//     return table;
// }
//
// #[allow(long_running_const_eval)]
// const TABLE: [u64; 1 << 24] = precompute_table();

fn step(mut x: u64) -> u64 {
    x = ((x <<  6) ^ x) & 0xffffff;
    x = ((x >>  5) ^ x) & 0xffffff;
    x = ((x << 11) ^ x) & 0xffffff;

    return x;
}

fn precompute_table() -> Vec<u64> {
    let mut table = Vec::from([0; 1 << 24]);

    let mut x = 1;
    for _ in 0..2000 {
        x = step(x);
    }

    let mut px = 1;

    for _ in 0..1 << 24 {
        table[px as usize] = x;
        px = step(px);
        x = step(x);
    }

    return table;
}

fn get_input() -> Vec<u64> {
    let stdin = io::stdin();

    return stdin.lock().lines().map(|l| l.unwrap().parse::<u64>().unwrap()).collect();
}

fn part1(input: &[u64], table: &[u64]) -> u64 {
    return input.iter().map(|x| table[*x as usize]).sum();
}

fn part2(input: &[u64]) -> u64 {
    let mut sequences_score = Vec::from([0; 1 << 20]);
    let mut seen = Vec::from([0; 1 << 20]);
    let mut best = 0;

    for (i, &x) in input.iter().enumerate() {
        let mut x = x as i64;

        let mut key: usize = 0;
        for step_ind in 0..2000 {
            let nx = step(x as u64) as i64;
            let diff = nx % 10 - x % 10;
            x = nx;

            key = ((diff + 10) | ((key as i64) << 5) & 0xfffff) as usize;
            if seen[key] != i as i64 + 1 && step_ind >= 3 {
                seen[key] = i as i64 + 1;

                let new_score = sequences_score[key] + nx as u64 % 10;
                sequences_score[key] = new_score;
                best = best.max(new_score);
            }
        }
    }

    return best;
}

fn main() {
    let table = precompute_table();
    let input = get_input();

    let start_part_1 = Instant::now();
    let result_part_1 = part1(&input, &table);
    let end_part_1 = Instant::now();
    println!("Part 1: {} ( {:.2?} )", result_part_1, end_part_1.duration_since(start_part_1));

    let start_part_2 = Instant::now();
    let result_part_2 = part2(&input);
    let end_part_2 = Instant::now();
    println!("Part 2: {} ( {:.2?} )", result_part_2, end_part_2.duration_since(start_part_2));
}
