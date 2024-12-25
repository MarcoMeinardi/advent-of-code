use std::time::Instant;
use std::io::{self, Read};

fn get_input() -> Vec<Vec<String>> {
    let stdin = io::stdin();
    let mut input = String::new();
    stdin.lock().read_to_string(&mut input).unwrap();

    return input.split("\n\n").map(|l| l.lines().map(std::string::ToString::to_string).collect()).collect();
}

fn part1(input: &[Vec<String>]) -> u64 {
    fn parse_pins(input: &[String]) -> (bool, u32) {
        let mut res = 0;
        for (i, line) in input[1..input.len() - 1].iter().enumerate() {
            for (j, c) in line.chars().enumerate() {
                if c == '#' {
                    res |= 1 << (i * 5 + j);
                }
            }
        }

        return (input[0].starts_with('#'), res);
    }

    let parsed_pins = input.iter().map(|l| parse_pins(l)).collect::<Vec<_>>();

    let keys = parsed_pins.iter().filter(|(k, _)| *k).map(|(_, v)| *v).collect::<Vec<_>>();
    let holes = parsed_pins.iter().filter(|(k, _)| !*k).map(|(_, v)| *v).collect::<Vec<_>>();

    return keys.iter().map(|key|
        holes.iter().filter(|&hole| key & hole == 0).count() as u64
    ).sum()
}

fn main() {
    let input = get_input();

    let start_part_1 = Instant::now();
    let result_part_1 = part1(&input);
    let end_part_1 = Instant::now();
    println!("Part 1: {} ( {:.2?} )", result_part_1, end_part_1.duration_since(start_part_1));
}
