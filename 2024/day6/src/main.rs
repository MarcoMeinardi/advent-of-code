use std::time::Instant;
use std::io::{self, BufRead};

static DY: [i32; 4] = [-1, 0, 1, 0];
static DX: [i32; 4] = [0, 1, 0, -1];

#[derive(Eq, Hash, PartialEq, Clone, Debug)]
struct Guard {
    y: usize,
    x: usize,
    dir: usize
}

fn get_input() -> (Vec<Vec<bool>>, Guard) {
    let stdin = io::stdin();

    let mut guard: Option<Guard> = None;

    let map = stdin.lock().lines().enumerate()
        .map(|(y, row)| row.unwrap().chars().enumerate()
            .map(|(x, c)| match c {
                '.' => false,
                '#' => true,
                _ => {
                    assert!(guard.is_none());
                    guard = Some(Guard { y, x, dir: match c {
                        '^' => 0,
                        '>' => 1,
                        'v' => 2,
                        '<' => 3,
                        _ => panic!("Invalid guard direction")
                    }});
                    false
                }
            }).collect()
        ).collect();

    assert!(guard.is_some());

    return (map, guard.unwrap());
}

fn do_step(map: &[Vec<bool>], guard: &mut Guard) -> bool {
    let ny = guard.y as i32 + DY[guard.dir];
    let nx = guard.x as i32 + DX[guard.dir];

    if ny < 0 || ny >= map.len() as i32 || nx < 0 || nx >= map[0].len() as i32 {
        return false;
    } else if map[ny as usize][nx as usize] {
        guard.dir = (guard.dir + 1) % 4;
    } else {
        guard.y = ny as usize;
        guard.x = nx as usize;
    }

    return true;
}

fn part1(map: &[Vec<bool>], guard: &Guard) -> i32 {
    let mut guard = guard.clone();
    let mut visited = vec![vec![false; map[0].len()]; map.len()];
    let mut total = 0;

    loop {
        total += !visited[guard.y][guard.x] as i32;
        visited[guard.y][guard.x] = true;

        if !do_step(map, &mut guard) {
            break;
        }
    }

    return total;
}

fn check_loop(map: &[Vec<bool>], mut guard: Guard) -> bool {
    let mut visited = vec![vec![0; map[0].len()]; map.len()];

    while (visited[guard.y][guard.x] & (1 << guard.dir) as u8) == 0 {
        visited[guard.y][guard.x] |= 1 << guard.dir as u8;

        if !do_step(map, &mut guard) {
            return false;
        }
    }
    return true;
}

fn part2(map: &mut [Vec<bool>], guard: &Guard) -> i32 {
    let mut guard = guard.clone();
    let mut visited = vec![vec![false; map[0].len()]; map.len()];

    let mut total = 0;

    loop  {
        visited[guard.y][guard.x] = true;

        let ny = guard.y as i32 + DY[guard.dir];
        let nx = guard.x as i32 + DX[guard.dir];

        if ny < 0 || ny >= map.len() as i32 || nx < 0 || nx >= map[0].len() as i32 {
            break;
        }

        if !map[ny as usize][nx as usize] && !visited[ny as usize][nx as usize] {
            map[ny as usize][nx as usize] = true;
            total += check_loop(map, guard.clone()) as i32;
            map[ny as usize][nx as usize] = false;
        }

        if map[ny as usize][nx as usize] {
            guard.dir = (guard.dir + 1) % 4;
        } else {
            guard.y = ny as usize;
            guard.x = nx as usize;
        }
    }

    return total;
}

fn main() {
    let (mut map, guard) = get_input();

    let start_part_1 = Instant::now();
    let result_part_1 = part1(&map, &guard);
    let end_part_1 = Instant::now();
    println!("Part 1: {} ( {:.2?} )", result_part_1, end_part_1.duration_since(start_part_1));

    let start_part_2 = Instant::now();
    let result_part_2 = part2(&mut map, &guard);
    let end_part_2 = Instant::now();
    println!("Part 2: {} ( {:.2?} )", result_part_2, end_part_2.duration_since(start_part_2));
}

