use std::collections::VecDeque;
use std::time::Instant;
use std::io::{self, BufRead};

fn get_input() -> Vec<(usize, usize)> {
    let stdin = io::stdin();

    return stdin.lock().lines().map(|line| {
        let line = line.unwrap();
        let (a, b) = line.split_once(',').unwrap();
        return (a.parse().unwrap(), b.parse().unwrap());
    }).collect();
}

static SIZE: usize = 71;
static TO_DROP: usize = 1024;

static DYX: [(i32, i32); 4] = [(1, 0), (0, 1), (-1, 0), (0, -1)];

fn part1(inputs: &[(usize, usize)]) -> u64 {
    fn get_min_dist(grid: &[Vec<bool>]) -> u64 {
        let mut dist = vec![vec![u64::MAX; SIZE]; SIZE];
        let mut q = VecDeque::new();
        q.push_back((0, 0));
        dist[0][0] = 0;

        while let Some((y, x)) = q.pop_front() {
            if y == SIZE - 1 && x == SIZE - 1 {
                return dist[y][x];
            }

            for (dy, dx) in DYX {
                let ny = (y as i32 + dy) as usize;
                let nx = (x as i32 + dx) as usize;

                if ny < SIZE && nx < SIZE && grid[ny][nx] && dist[y][x] + 1 < dist[ny][nx] {
                    dist[ny][nx] = dist[y][x] + 1;
                    q.push_back((ny, nx));
                }
            }
        }

        panic!("Cannot find path");
    }

    let mut grid = vec![vec![true; SIZE]; SIZE];
    inputs[..TO_DROP].iter().for_each(|(x, y)| {
        grid[*y][*x] = false;
    });

    return get_min_dist(&grid);
}

fn part2(inputs: &[(usize, usize)]) -> String {
    fn is_reachable(grid: &[Vec<u64>], iteration: u64) -> bool {
        let mut visited = vec![vec![false; SIZE]; SIZE];
        let mut q = VecDeque::new();
        q.push_back((0, 0));
        visited[0][0] = true;

        while let Some((y, x)) = q.pop_front() {
            if y == SIZE - 1 && x == SIZE - 1 {
                return true;
            }

            for (dy, dx) in DYX {
                let ny = (y as i32 + dy) as usize;
                let nx = (x as i32 + dx) as usize;

                if ny < SIZE && nx < SIZE && grid[ny][nx] > iteration && !visited[ny][nx] {
                    q.push_back((ny, nx));
                    visited[ny][nx] = true;
                }
            }
        }

        return false;
    }

    let mut grid = vec![vec![u64::MAX; SIZE]; SIZE];
    inputs.iter().enumerate().for_each(|(i, (x, y))| {
        grid[*y][*x] = i as u64;
    });


    let (mut l, mut r) = (0, inputs.len() as u64);

    while l < r {
        let m = l + (r - l) / 2;

        if is_reachable(&grid, m) {
            l = m + 1;
        } else {
            r = m;
        }
    }

    let res = inputs[l as usize];

    return format!("{},{}", res.0, res.1);
}

fn main() {
    let inputs = get_input();

    let start_part_1 = Instant::now();
    let result_part_1 = part1(&inputs);
    let end_part_1 = Instant::now();
    println!("Part 1: {} ( {:.2?} )", result_part_1, end_part_1.duration_since(start_part_1));

    let start_part_2 = Instant::now();
    let result_part_2 = part2(&inputs);
    let end_part_2 = Instant::now();
    println!("Part 2: {} ( {:.2?} )", result_part_2, end_part_2.duration_since(start_part_2));
}
