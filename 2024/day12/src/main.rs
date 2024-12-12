use std::time::Instant;
use std::io::{self, BufRead};

fn get_input() -> Vec<Vec<u8>> {
    let stdin = io::stdin();
    return stdin.lock()
        .lines()
        .map(|x| x.unwrap().chars()
            .map(|b| b as u8 - b'A').collect()
        ).collect();
}

static DY: [i32; 4] = [-1, 0, 1, 0];
static DX: [i32; 4] = [0, 1, 0, -1];

fn part1(input: &[Vec<u8>]) -> u64 {
    fn get_perimeter_area(grid: &[Vec<u8>], y: usize, x: usize, visited: &mut [Vec<bool>]) -> (u64, u64) {
        if visited[y][x] {
            return (0, 0);
        }
        visited[y][x] = true;

        let mut perimeter = 0;
        let mut area = 1;
        DY.iter().zip(DX.iter()).for_each(|(dy, dx)| {
            let ny = (y as i32 + dy) as usize;
            let nx = (x as i32 + dx) as usize;

            if ny >= grid.len() || nx >= grid[0].len() {
                perimeter += 1;
            } else if grid[ny][nx] == grid[y][x] {
                let (peri, ar) = get_perimeter_area(grid, ny, nx, visited);
                perimeter += peri;
                area += ar;
            } else {
                perimeter += 1;
            }
        });

        return (perimeter, area);
    }

    let mut visited = vec![vec![false; input[0].len()]; input.len()];

    return (0..input.len()).map(|y| (0..input[0].len()).map(|x| {
        let (peri, area) = get_perimeter_area(input, y, x, &mut visited);
        return peri * area;
    }).sum::<u64>()).sum();
}

fn part2(input: &[Vec<u8>]) -> u64 {
    fn get_n_sides_area(grid: &[Vec<u8>], y: usize, x: usize, visited: &mut [Vec<bool>]) -> (u64, u64) {
        if visited[y][x] {
            return (0, 0);
        }
        visited[y][x] = true;

        let mut n_sides = 0;
        let mut area = 1;
        DY.iter().zip(DX.iter()).enumerate().for_each(|(i, (dy, dx))| {
            let ny = (y as i32 + dy) as usize;
            let nx = (x as i32 + dx) as usize;

            if ny >= grid.len() || nx >= grid[0].len() || grid[ny][nx] != grid[y][x] {
                let py = (y as i32 + DY[(i - 1) % 4]) as usize;
                let px = (x as i32 + DX[(i - 1) % 4]) as usize;
                if py >= grid.len() || px >= grid[0].len() || grid[py][px] != grid[y][x] {
                    n_sides += 1;
                } else {
                    let pdy = (if *dy != 0 {
                        y as i32 + dy
                    } else {
                        y as i32 + DY[(i - 1) % 4]
                    }) as usize;

                    let pdx = (if *dx != 0 {
                        x as i32 + dx
                    } else {
                        x as i32 + DX[(i - 1) % 4]
                    }) as usize;

                    if pdy < grid.len() && pdx < grid[0].len() && grid[pdy][pdx] == grid[y][x] {
                        n_sides += 1;
                    }
                }
            } else {
                let (sides, ar) = get_n_sides_area(grid, ny, nx, visited);
                n_sides += sides;
                area += ar;
            }
        });

        return (n_sides, area);
    }

    let mut visited = vec![vec![false; input[0].len()]; input.len()];
    return (0..input.len()).map(|y| (0..input[0].len()).map(|x| {
        let (peri, area) = get_n_sides_area(input, y, x, &mut visited);
        return peri * area;
    }).sum::<u64>()).sum();
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
