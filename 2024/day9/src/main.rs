use std::time::Instant;
use std::io::{self, BufRead};

fn get_input() -> Vec<u64> {
    let stdin = io::stdin();
    return stdin.lock().lines().next().unwrap().unwrap().chars()
        .map(|x| x as u64 - b'0' as u64)
        .collect();
}

fn range_sum(start: u64, length: u64) -> u64 {
    if length == 0 {
        return 0;
    } else {
        return length * (length - 1) / 2 + start * length;
    }
}

fn part1(input: &[u64]) -> u64 {
    let full: Vec<u64> = input.iter().step_by(2).map(|&x| x).collect();
    let empty: Vec<u64> = input.iter().skip(1).step_by(2).map(|&x| x).collect();

    let mut total = 0;

    let mut curr_id = full.len() as u64 - 1;
    let mut left_id = 0;
    let mut full_left = full[curr_id as usize];
    let mut empty_idx = 0;
    let mut empty_left = empty[0];
    let mut index = full[0];

    loop {
        let to_take = std::cmp::min(full_left, empty_left);
        total += curr_id * range_sum(index, to_take);
        index += to_take;
        empty_left -= to_take;
        full_left -= to_take;

        if full_left == 0 {
            curr_id -= 1;
            full_left = full[curr_id as usize];
        }

        if empty_left == 0 {
            left_id += 1;
            if left_id >= curr_id {
                total += left_id * range_sum(index, full_left);
                break;
            }

            total += left_id * range_sum(index, full[left_id as usize]);
            index += full[left_id as usize];
            empty_idx += 1;
            empty_left = empty[empty_idx as usize];
        }
    }

    return total;
}

fn part2(input: &[u64]) -> u64 {
    let mut files: Vec<(u64, u64)> = Vec::new();
    let mut empty: Vec<(u64, u64)> = Vec::new();

    let mut index = 0;
    input.iter().enumerate().for_each(|(i, &x)| {
        if (i & 1) == 0 {
            files.push((index, x));
        } else {
            empty.push((index, x));
        }
        index += x;
    });

    files.iter_mut().rev().for_each(|file| {
        for (index, space) in empty.iter_mut().enumerate() {
            if file.0 < space.0 {
                break;
            }
            if space.1 >= file.1 {
                file.0 = space.0;
                if space.1 == file.1 {
                    empty.remove(index);
                } else {
                    space.1 -= file.1;
                    space.0 += file.1;
                }
                break;
            }
        }
    });

    return files.iter().enumerate().skip(1).map(|(i, file)| i as u64 * range_sum(file.0, file.1)).sum();
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

