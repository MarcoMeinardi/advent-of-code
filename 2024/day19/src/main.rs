use rayon::prelude::*;
use std::time::Instant;
use std::io::{self, Read};


fn get_input() -> (Vec<Vec<u8>>, Vec<Vec<u8>>) {
    let stdin = io::stdin();
    let mut input = String::new();
    stdin.lock().read_to_string(&mut input).unwrap();

    let (towels, designs) = input.split_once("\n\n").unwrap();

    let towels = towels.split(", ").map(|towel| towel.bytes().collect()).collect();
    let designs = designs.lines().map(|design| design.bytes().collect()).collect();

    return (towels, designs);
}

fn possible_arrangements(towels: &[Vec<u8>], design: &[u8]) -> u64 {
    let mut arrangements = vec![0; design.len() + 1];
    arrangements[0] = 1;

    for i in 0..design.len() {
        if arrangements[i] == 0 {
            continue;
        }

        for towel in towels {
            if i + towel.len() <= design.len() && towel == &design[i..i + towel.len()] {
                arrangements[i + towel.len()] += arrangements[i];
            }
        }
    }

    return arrangements[design.len()];
}

fn part1(towels: &[Vec<u8>], designs: &[Vec<u8>]) -> u64 {
    return designs.par_iter().filter(|design| possible_arrangements(towels, design) > 0).count() as u64;
}

fn part2(towels: &[Vec<u8>], designs: &[Vec<u8>]) -> u64 {
    return designs.par_iter().map(|design| possible_arrangements(towels, design)).sum();
}

fn main() {
    let (towels, designs) = get_input();

    let start_part_1 = Instant::now();
    let result_part_1 = part1(&towels, &designs);
    let end_part_1 = Instant::now();
    println!("Part 1: {} ( {:.2?} )", result_part_1, end_part_1.duration_since(start_part_1));

    let start_part_2 = Instant::now();
    let result_part_2 = part2(&towels, &designs);
    let end_part_2 = Instant::now();
    println!("Part 2: {} ( {:.2?} )", result_part_2, end_part_2.duration_since(start_part_2));
}
