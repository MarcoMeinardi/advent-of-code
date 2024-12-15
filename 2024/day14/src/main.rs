use statistical::variance;
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
    fn xgcd(a: i64, b: i64) -> (i64, i64, i64) {
        let (mut old_r, mut r) = (a, b);
        let (mut old_s, mut s) = (1, 0);
        let (mut old_t, mut t) = (0, 1);

        while r != 0 {
            let quotient = old_r / r;
            let temp = r;
            r = old_r - quotient * r;
            old_r = temp;

            let temp = s;
            s = old_s - quotient * s;
            old_s = temp;

            let temp = t;
            t = old_t - quotient * t;
            old_t = temp;
        }

        return (old_r, old_s, old_t);
    }

    fn crt(x1: i64, x2: i64, m1: i64, m2: i64) -> u64 {
        let (_, s, t) = xgcd(m1, m2);

        let x = (x1 * m2 * t + x2 * m1 * s).rem_euclid(m1 * m2);
        return x as u64;
    }

    #[allow(dead_code)]
    fn print_tree(iteration: i64, pos: &[(i64, i64, i64, i64)]) {
        let mut grid = vec![vec![false; 101]; 103];
        for (px, py, vx, vy) in pos {
            grid[(*py + iteration * vy).rem_euclid(103) as usize][(*px + iteration * vx).rem_euclid(101) as usize] = true;
        }

        eprintln!("{iteration} Seconds");
        for row in grid {
            for cell in row {
                eprint!("{}", if cell { '█' } else { ' ' });
            }
            eprintln!();
        };
    }

    let mut robots = input.iter().map(|(px, py, vx, vy)| (*px, *py, *vx, *vy)).collect::<Vec<_>>();

    let mut min_y_variance = 1e10_f64;
    let mut min_x_variance = 1e10_f64;
    let mut y_iteration: u64 = 0;
    let mut x_iteration: u64 = 0;

    for iteration in 1..103 {
        for (px, py, vx, vy) in &mut robots {
            *px = (*px + *vx).rem_euclid(101);
            *py = (*py + *vy).rem_euclid(103);
        }

        let y_values: Vec<f64> = robots.iter().map(|(_, y, _, _)| *y as f64).collect();
        let x_values: Vec<f64> = robots.iter().map(|(x, _, _, _)| *x as f64).collect();
        let y_variance = variance(&y_values, None);
        let x_variance = variance(&x_values, None);

        if y_variance < min_y_variance {
            min_y_variance = y_variance;
            y_iteration = iteration;
        }
        if x_variance < min_x_variance {
            min_x_variance = x_variance;
            x_iteration = iteration;
        }
    }

    assert_ne!(y_iteration, 0);

    let result = crt(y_iteration as i64, x_iteration as i64, 103, 101);

    #[cfg(debug_assertions)]
    print_tree(result as i64, input);

    return result;
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
