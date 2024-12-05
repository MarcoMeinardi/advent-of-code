use std::collections::HashSet;
use std::time::Instant;
use std::io::{self, Read};

fn get_input() -> (Vec<(i32, i32)>, Vec<Vec<i32>>) {
    let stdin = io::stdin();
    let mut input = Vec::new();
    stdin.lock().read_to_end(&mut input).unwrap();

    let input_str = String::from_utf8(input).unwrap();
    let (first, second) = input_str.split_once("\n\n").unwrap();

    let first = first.lines()
        .map(|line| line.split_once('|').unwrap())
        .map(|(left, right)| (left.parse::<i32>().unwrap(), right.parse::<i32>().unwrap()))
        .collect();
    
    let second = second.lines().map(|line| {
        return line.split(',').map(|num| num.parse::<i32>().unwrap()).collect();
    }).collect();

    return (first, second);
}

fn make_priority_map(priorities: &[(i32, i32)]) -> HashSet<(i32, i32)> {
    return priorities.iter().map(|(left, right)| (*right, *left)).collect();
}

fn check_correct_ordering(priority_map: &HashSet<(i32, i32)>, manual: &[i32]) -> Option<(usize, usize)> {
    for i in 0..manual.len() - 1 {
        for j in i + 1..manual.len() {
            if priority_map.contains(&(manual[i], manual[j])) {
                return Some((i, j));
            }
        }
    }

    return None;
}

fn part1(priorities: &[(i32, i32)], manuals: &[Vec<i32>]) -> i32 {
    let priority_map = make_priority_map(priorities);

    return manuals.iter()
        .filter(|manual| check_correct_ordering(&priority_map, manual).is_none())
        .map(|manual| manual[manual.len() / 2])
        .sum();
}

fn part2(priorities: &[(i32, i32)], manuals: &[Vec<i32>]) -> i32 {
    let priority_map = make_priority_map(priorities);

    return manuals.to_owned().iter_mut()
        .filter_map(|manual| {
            let mut any_change = false;
            while let Some((i, j)) = check_correct_ordering(&priority_map, manual) {
                any_change = true;
                manual.swap(i, j);
            }

            if any_change {
                return Some(manual[manual.len() / 2]);
            }
            return None
        })
        .sum();
}

fn main() {
    let (priorities, manuals) = get_input();

    let start_part_1 = Instant::now();
    let result_part_1 = part1(&priorities, &manuals);
    let end_part_1 = Instant::now();
    println!("Part 1: {} ( {:.2?} )", result_part_1, end_part_1.duration_since(start_part_1));

    let start_part_2 = Instant::now();
    let result_part_2 = part2(&priorities, &manuals);
    let end_part_2 = Instant::now();
    println!("Part 2: {} ( {:.2?} )", result_part_2, end_part_2.duration_since(start_part_2));
}
