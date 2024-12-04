use std::time::Instant;
use std::io::{self, BufRead};

fn get_input() -> Vec<Vec<u8>> {
    let stdin = io::stdin();
    return stdin.lock().lines().map(|x| x.unwrap().into_bytes()).collect();
}

static XMAS: &[u8] = b"XMAS";

static DY: [i32; 8] = [-1, -1, -1, 0, 0, 1, 1, 1];
static DX: [i32; 8] = [-1, 0, 1, -1, 1, -1, 0, 1];

fn check_full_xmas(input: &[Vec<u8>], x: i32, y: i32, dy: i32, dx: i32) -> bool {
    let last_y = y + dy * 3;
    let last_x = x + dx * 3;

    if last_y < 0 || last_y >= input.len() as i32 || last_x < 0 || last_x >= input[0].len() as i32 {
        return false;
    }

    if input[last_y as usize][last_x as usize] != XMAS[3] {
        return false;
    }

    if input[(y + dy * 2) as usize][(x + dx * 2) as usize] != XMAS[2] {
        return false;
    }

    return true;
}

fn check_xmas(input: &[Vec<u8>], x: usize, y: usize) -> i32 {
    return DY.iter().zip(DX.iter()).filter(|(&dy, &dx)| {
        let ny = y as i32 + dy;
        let nx = x as i32 + dx;

        if ny < 0 || ny >= input.len() as i32 || nx < 0 || nx >= input[0].len() as i32 {
            return false;
        }

        if input[ny as usize][nx as usize] == XMAS[1] {
            return check_full_xmas(input, x as i32, y as i32, dy, dx);
        }

        return false;
    }).count() as i32;
}

fn part1(input: &[Vec<u8>]) -> i32 {
    return (0..input.len()).map(|y|
        (0..input[0].len())
            .filter(|&x| input[y][x] == XMAS[0])
            .map(|x| check_xmas(input, x, y))
            .sum::<i32>()
    ).sum();
}

static DY2: [i32; 4] = [-1, -1, 1, 1];
static DX2: [i32; 4] = [-1, 1, -1, 1];

static MAS: &[u8; 3] = b"MAS";

fn check_x_mas(input: &[Vec<u8>], x: usize, y: usize) -> bool {
    return DY2.iter().zip(DX2.iter()).filter(|(&dy, &dx)|
        input[(y as i32 + dy) as usize][(x as i32 + dx) as usize] == MAS[0]
    ).filter(|(&dy, &dx)|
        input[(y as i32 - dy) as usize][(x as i32 - dx) as usize] == MAS[2]
    ).count() == 2;
}

fn part2(input: &[Vec<u8>]) -> i32 {
    return (1..input.len() - 1).map(|y|
        (1..input[0].len() - 1)
            .filter(|&x| input[y][x] == MAS[1])
            .filter(|&x| check_x_mas(input, x, y))
            .count() as i32
    ).sum();
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
