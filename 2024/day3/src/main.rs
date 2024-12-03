use std::io::{self, Read};
use regex::Regex;

fn get_input() -> String {
    let stdin = io::stdin();
    let mut input = Vec::new();
    stdin.lock().read_to_end(&mut input).unwrap();

    return String::from_utf8(input).unwrap();
}

fn part1(input: &str) {
    let re = Regex::new(r"mul\((\d+),(\d+)\)").unwrap();

    let total: u64 = re
        .captures_iter(input)
        .map(|c| c.extract())
        .map(|(_, [a, b])| a.parse::<u64>().unwrap() * b.parse::<u64>().unwrap())
        .sum();

    println!("Part 1: {}", total);
}

fn part2(input: &str) {
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

    println!("Part 2: {}", total);
}

fn main() {
    let input = get_input();
    part1(&input);
    part2(&input);
}
