use std::collections::HashSet;
use std::time::Instant;
use std::io::{self, BufRead};

fn get_input() -> Vec<Vec<u8>> {
    let stdin = io::stdin();
    return stdin.lock()
        .lines()
        .map(|x| x.unwrap().chars()
            .map(|b| b as u8 - b'0').collect()
        ).collect();
}

static DYX: [(i32, i32); 4] = [(0, 1), (1, 0), (-1, 0), (0, -1)];

fn part1(input: &[Vec<u8>]) -> u64 {
    fn dfs(input: &[Vec<u8>], y: usize, x: usize, peaks: &mut HashSet<(usize, usize)>) {
        DYX.iter().for_each(|(dy, dx)| {
            let ny = (y as i32 + dy) as usize;
            let nx = (x as i32 + dx) as usize;

            if ny < input.len() && nx < input[0].len() && input[ny][nx] == input[y][x] + 1 {
                if input[ny][nx] == 9 {
                    peaks.insert((ny, nx));
                } else {
                    dfs(input, ny, nx, peaks);
                }
            }
        });
    }

    return (0..input.len()).map(|y| (0..input[0].len()).map(|x| {
        if input[y][x] == 0 {
            let mut peaks = HashSet::new();
            dfs(input, y, x, &mut peaks);
            return peaks.len() as u64;
        }
        return 0;
    }).sum::<u64>()).sum();
}

fn part2(input: &[Vec<u8>]) -> u64 {
    fn dfs(input: &[Vec<u8>], y: usize, x: usize) -> u64 {
        return DYX.iter().map(|(dy, dx)| {
            let ny = (y as i32 + dy) as usize;
            let nx = (x as i32 + dx) as usize;

            if ny < input.len() && nx < input[0].len() && input[ny][nx] == input[y][x] + 1 {
                if input[ny][nx] == 9 {
                    return 1;
                }
                return dfs(input, ny, nx);
            }
            return 0;
        }).sum::<u64>();
    }

    return (0..input.len()).map(|y| (0..input[0].len()).map(|x|
        if input[y][x] == 0 {
            dfs(input, y, x)
        } else {
            0
        }
    ).sum::<u64>()).sum();
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
