use std::time::Instant;
use std::io::{self, BufRead};

fn get_input() -> Vec<u64> {
    let stdin = io::stdin();

    return stdin.lock().lines().map(|l| l.unwrap().parse::<u64>().unwrap()).collect();
}

fn step(mut x: u64) -> u64 {
    x = ((x <<  6) ^ x) & 0xffffff;
    x = ((x >>  5) ^ x) & 0xffffff;
    x = ((x << 11) ^ x) & 0xffffff;

    return x;
}

fn part1(input: &[u64]) -> u64 {
    fn evolve(mut x: u64) -> u64 {
        for _ in 0..2000 {
            x = step(x);
        }

        return x;
    }

    return input.iter().map(|x| evolve(*x)).sum();
}

fn part2(input: &[u64]) -> u64 {
    fn hash(diffs: &[i64], ind: usize) -> usize {
        return (
            ((diffs[ind - 0] + 10) <<  0) |
            ((diffs[ind - 1] + 10) <<  5) |
            ((diffs[ind - 2] + 10) << 10) |
            ((diffs[ind - 3] + 10) << 15)
        ) as usize;
    }

    let mut sequences_score = Vec::from([0; 1 << 20]);
    let mut seen = Vec::from([-1; 1 << 20]);
    let mut best = 0;

    let mut diffs = vec![0; 2000];

    for (i, &x) in input.iter().enumerate() {
        let mut x = x as i64;

        for step_ind in 0..2000 {
            let nx = step(x as u64) as i64;
            diffs[step_ind] = nx % 10 - x % 10;
            x = nx;

            if step_ind >= 3 {
                let key = hash(&diffs, step_ind);
                if seen[key] == i as i64 {
                    continue;
                }
                seen[key] = i as i64;

                let new_score = sequences_score[key] + nx as u64 % 10;
                sequences_score[key] = new_score;
                best = best.max(new_score);
            }
        }
    }

    return best;
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
