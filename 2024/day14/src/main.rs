use std::time::Instant;
use std::io::{self, BufRead};

fn get_input() -> Vec<(i64, i64, i64, i64)> {
    let stdin = io::stdin();

    return stdin.lock().lines().map(|line| {
        let line = line.unwrap();
        let (p, v) = line.split_once(' ').unwrap();
        let p = p.split_once('=').unwrap().1;
        let v = v.split_once('=').unwrap().1;

        let (px, py) = p.split_once(',').unwrap();
        let px = px.parse::<i64>().unwrap();
        let py = py.parse::<i64>().unwrap();

        let (vx, vy) = v.split_once(',').unwrap();
        let vx = vx.parse::<i64>().unwrap();
        let vy = vy.parse::<i64>().unwrap();

        return (px, py, vx, vy);
    }).collect();
}

fn part1(input: &[(i64, i64, i64, i64)]) -> u64 {
    let final_pos = input.iter().map(|(px, py, vx, vy)|
        ((px + 100 * vx).rem_euclid(101), (py + 100 * vy).rem_euclid(103))
    ).collect::<Vec<_>>();

    let quadrants = final_pos.iter().fold((0, 0, 0, 0), |acc, (x, y)| {
        let (q1, q2, q3, q4) = acc;
        if *x == 50 || *y == 51 {
            return (q1, q2, q3, q4);
        }

        return match (*x < 50, *y < 51) {
            (true, true) => (q1 + 1, q2, q3, q4),
            (true, false) => (q1, q2 + 1, q3, q4),
            (false, true) => (q1, q2, q3 + 1, q4),
            (false, false) => (q1, q2, q3, q4 + 1),
        };
    });

    return quadrants.0 * quadrants.1 * quadrants.2 * quadrants.3;
}

fn part2(input: &[(i64, i64, i64, i64)]) -> u64 {
    fn print_tree(iteration: u64, pos: &[(i64, i64, i64, i64)]) {
        let mut grid = vec![vec![false; 101]; 103];
        for (px, py, _, _) in pos {
            grid[*py as usize][*px as usize] = true;
        }

        eprintln!("{iteration} Seconds");
        for row in grid {
            for cell in row {
                eprint!("{}", if cell { '█' } else { ' ' });
            }
            eprintln!();
        };
    }

    fn all_disjoint(pos: &mut [(i64, i64, i64, i64)]) -> bool {
        pos.sort_unstable();
        for i in 0..pos.len() - 1 {
            if pos[i].0 == pos[i + 1].0 && pos[i].1 == pos[i + 1].1 {
                return false;
            }
        }
        return true;
    }

    let mut input = input.iter().map(|(px, py, vx, vy)| (*px, *py, *vx, *vy)).collect::<Vec<_>>();

    let mut iteration = 0;

    loop {
        iteration += 1;
        for (px, py, vx, vy) in &mut input {
            *px = (*px + *vx).rem_euclid(101);
            *py = (*py + *vy).rem_euclid(103);
        }

        if all_disjoint(&mut input) {
            break;
        }
    }
    print_tree(iteration, &input);

    return iteration;
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
