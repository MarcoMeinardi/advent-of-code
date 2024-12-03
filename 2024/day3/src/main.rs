use std::time::Instant;
use std::io::{self, Read};
use regex::Regex;

fn get_input() -> String {
    let stdin = io::stdin();
    let mut input = Vec::new();
    stdin.lock().read_to_end(&mut input).unwrap();

    return String::from_utf8(input).unwrap();
}

fn part1(input: &str) -> u64 {
    let re = Regex::new(r"mul\((\d+),(\d+)\)").unwrap();

    let total: u64 = re
        .captures_iter(input)
        .map(|c| c.extract())
        .map(|(_, [a, b])| a.parse::<u64>().unwrap() * b.parse::<u64>().unwrap())
        .sum();

    return total;
}

fn part2(input: &str) -> u64 {
    let re = Regex::new(r"mul\((?<num1>\d+),(?<num2>\d+)\)|(?<do>do\(\))|(?<dont>don't\(\))").unwrap();

    let mut enabled = true;
    let total: u64 = re
        .captures_iter(input)
        .map(|c| {
            if c.name("do").is_some() {
                enabled = true;
            } else if c.name("dont").is_some() {
                enabled = false;
            } else if enabled {
                return
                    c.name("num1").unwrap().as_str().parse::<u64>().unwrap() *
                    c.name("num2").unwrap().as_str().parse::<u64>().unwrap();
            }

            return 0;
        }).sum();

    return total;
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
