use std::time::Instant;
use std::io::{self, Read};

fn get_input() -> Vec<(i64, i64, i64, i64, i64, i64)> {
    let stdin = io::stdin();
    let mut input = String::new();
    stdin.lock().read_to_string(&mut input).unwrap();

    return input.split("\n\n").map(|group| {
        let lines: Vec<&str> = group.lines().collect();
        assert_eq!(lines.len(), 3);

        let (left, right) = lines[0].split_once(',').unwrap();
        let ax = left.split_once('+').unwrap().1.parse::<i64>().unwrap();
        let ay = right.split_once('+').unwrap().1.parse::<i64>().unwrap();

        let (left, right) = lines[1].split_once(',').unwrap();
        let bx = left.split_once('+').unwrap().1.parse::<i64>().unwrap();
        let by = right.split_once('+').unwrap().1.parse::<i64>().unwrap();

        let (left, right) = lines[2].split_once(',').unwrap();
        let x = left.split_once('=').unwrap().1.parse::<i64>().unwrap();
        let y = right.split_once('=').unwrap().1.parse::<i64>().unwrap();

        return (ax, ay, bx, by, x, y);
    }).collect();
}

fn solve_linear_system(ax: i64, ay: i64, bx: i64, by: i64, x: i64, y: i64) -> i64 {
    let bc_den = by * ax - ay * bx;
    if bc_den == 0 {
        return 0;
    }

    let bc_num = y * ax - ay * x;
    let (bc, bc_rem) = num_integer::div_rem(bc_num, bc_den);
    if bc_rem != 0 {
        return 0;
    }

    let ac_num = x - bx * bc;

    let (ac, ac_rem) = num_integer::div_rem(ac_num, ax);
    if ac_rem != 0 {
        return 0;
    }

    return ac * 3 + bc;
}

fn part1(input: &[(i64, i64, i64, i64, i64, i64)]) -> i64 {
    return input.iter().map(|(ax, ay, bx, by, x, y)|
        solve_linear_system(*ax, *ay, *bx, *by, *x, *y)
    ).sum();
}

fn part2(input: &[(i64, i64, i64, i64, i64, i64)]) -> i64 {
    return input.iter().map(|(ax, ay, bx, by, x, y)|
        solve_linear_system(*ax, *ay, *bx, *by, *x + 10000000000000, *y + 10000000000000)
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
