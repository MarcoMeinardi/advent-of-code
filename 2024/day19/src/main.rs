use std::collections::HashSet;
use std::time::Instant;
use std::io::{self, Read};


fn get_input() -> (Vec<String>, Vec<String>) {
    let stdin = io::stdin();
    let mut input = String::new();
    stdin.lock().read_to_string(&mut input).unwrap();

    let (towels, designs) = input.split_once("\n\n").unwrap();

    let towels = towels.split(", ").map(|towel| towel.to_string()).collect();
    let designs = designs.lines().map(|design| design.to_string()).collect();

    return (towels, designs);
}

fn possible_arrangements(towels_map: &HashSet<String>, longest_towel: usize, design: &String) -> u64 {
    let mut arrangements = vec![0; design.len() + 1];
    arrangements[0] = 1;

    for i in 0..design.len() {
        for j in i..design.len().min(i + longest_towel) {
            let towel = &design[i..=j];
            if towels_map.contains(towel) && towel.len() <= longest_towel {
                arrangements[j + 1] += arrangements[i];
            }
        }
    }

    return arrangements[design.len()];
}

fn part1(towels: &[String], designs: &[String]) -> u64 {
    let towels_map = towels.iter().cloned().collect::<HashSet<_>>();
    let longest_towel = towels.iter().map(|towel| towel.len()).max().unwrap();
    return designs.iter().filter(|design| possible_arrangements(&towels_map, longest_towel, design) > 0).count() as u64;
}

fn part2(towels: &[String], designs: &[String]) -> u64 {
    let towels_map = towels.iter().cloned().collect::<HashSet<_>>();
    let longest_towel = towels.iter().map(|towel| towel.len()).max().unwrap();
    return designs.iter().map(|design| possible_arrangements(&towels_map, longest_towel, design)).sum();
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
