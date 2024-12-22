use lazy_static::lazy_static;
use std::time::Instant;
use std::io::{self, BufRead};

fn get_input() -> Vec<Vec<u8>> {
    let stdin = io::stdin();

    return stdin.lock().lines()
        .map(|line| line.unwrap().as_bytes().to_vec())
        .collect();
}

#[derive(Debug, Clone, Copy)]
enum Direction {
    A,
    Up,
    Down,
    Left,
    Right
}

lazy_static! {
    static ref PATHS: [[Vec<Direction>; 5]; 5] = [
        [
            vec![Direction::A],
            vec![Direction::Left, Direction::A],
            vec![Direction::Left, Direction::Down, Direction::A],
            vec![Direction::Down, Direction::Left, Direction::Left, Direction::A],
            vec![Direction::Down, Direction::A]
        ],
        [
            vec![Direction::Right, Direction::A],
            vec![Direction::A],
            vec![Direction::Down, Direction::A],
            vec![Direction::Down, Direction::Left, Direction::A],
            vec![Direction::Down, Direction::Right, Direction::A]
        ],
        [
            vec![Direction::Up, Direction::Right, Direction::A],
            vec![Direction::Up, Direction::A],
            vec![Direction::A],
            vec![Direction::Left, Direction::A],
            vec![Direction::Right, Direction::A]
        ],
        [
            vec![Direction::Right, Direction::Right, Direction::Up, Direction::A],
            vec![Direction::Right, Direction::Up, Direction::A],
            vec![Direction::Right, Direction::A],
            vec![Direction::A],
            vec![Direction::Right, Direction::Right, Direction::A]
        ],
        [
            vec![Direction::Up, Direction::A],
            vec![Direction::Left, Direction::Up, Direction::A],
            vec![Direction::Left, Direction::A],
            vec![Direction::Left, Direction::Left, Direction::A],
            vec![Direction::A]
        ]
    ];
}

fn get_cost(line: &[u8], costs: &[Vec<u64>]) -> u64 {
    let mut y = 0;
    let mut x = 2;

    let mut move_cost = 0;
    for &c in line {
        let (ny, nx) = match c {
            b'A' => (0, 2),
            b'0' => (0, 1),
            b'1'..=b'9' => ((c - b'1' + 3) / 3, (c - b'1') % 3),
            _ => panic!("Invalid input")
        };

        let dy = ny as i32 - y;
        let dx = nx as i32 - x;

        let mut ppos = Direction::A;

        if x == 0 && ny == 0 {
            move_cost += costs[Direction::A as usize][Direction::Right as usize] + dx as u64 - 1;
            move_cost += costs[Direction::Right as usize][Direction::Down as usize] + (-dy - 1) as u64;
            ppos = Direction::Down;
        } else if y == 0 && nx == 0 {
            move_cost += costs[Direction::A as usize][Direction::Up as usize] + dy as u64 - 1;
            move_cost += costs[Direction::Up as usize][Direction::Left as usize] + (-dx - 1) as u64;
            ppos = Direction::Left;
        } else {
            if dx < 0 {
                move_cost += costs[ppos as usize][Direction::Left as usize] + (-dx - 1) as u64;
                ppos = Direction::Left;
            }
            if dy < 0 {
                move_cost += costs[ppos as usize][Direction::Down as usize] + (-dy - 1) as u64;
                ppos = Direction::Down;
            }
            if dy > 0 {
                move_cost += costs[ppos as usize][Direction::Up as usize] + dy as u64 - 1;
                ppos = Direction::Up;
            }
            if dx > 0 {
                move_cost += costs[ppos as usize][Direction::Right as usize] + dx as u64 - 1;
                ppos = Direction::Right;
            }
        }

        move_cost += costs[ppos as usize][Direction::A as usize];

        y = ny as i32;
        x = nx as i32;
    }

    let input_cost = String::from_utf8(line[0..line.len() - 1].to_vec()).unwrap().parse::<u64>().unwrap();
    return move_cost * input_cost;
}

fn part1(input: &[Vec<u8>]) -> u64 {
    let mut costs = vec![vec![vec![1; 5]; 5]; 3];

    for layer in 1..3 {
        for from in 0..5 {
            for to in 0..5 {
                let mut pos = Direction::A;
                costs[layer][from][to] = PATHS[from][to].iter().map(|d| {
                    let old_pos = pos;
                    pos = *d;
                    return costs[layer - 1][old_pos as usize][pos as usize];
                }).sum();
            }
        }
    }

    let final_costs = costs.last().unwrap();

    return input.iter().map(|line| get_cost(line, final_costs)).sum();
}

fn part2(input: &[Vec<u8>]) -> u64 {
    let mut costs = vec![vec![vec![1; 5]; 5]; 26];

    for layer in 1..26 {
        for from in 0..5 {
            for to in 0..5 {
                let mut pos = Direction::A;
                costs[layer][from][to] = PATHS[from][to].iter().map(|d| {
                    let old_pos = pos;
                    pos = *d;
                    return costs[layer - 1][old_pos as usize][pos as usize];
                }).sum();
            }
        }
    }

    let final_costs = costs.last().unwrap();

    return input.iter().map(|line| get_cost(line, final_costs)).sum();
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
