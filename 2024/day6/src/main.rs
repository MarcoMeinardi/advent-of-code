use std::collections::HashSet;
use std::time::Instant;
use std::io::{self, BufRead};

static DY: [i32; 4] = [-1, 0, 1, 0];
static DX: [i32; 4] = [0, 1, 0, -1];

#[derive(Eq, Hash, PartialEq, Clone, Debug)]
struct Guard {
    y: i32,
    x: i32,
    dir: usize
}

fn get_input() -> (Vec<Vec<bool>>, Guard) {
    let stdin = io::stdin();

    let mut guard = Guard { y: -1, x: -1, dir: 0 };

    let map = stdin.lock().lines().enumerate()
        .map(|(y, row)| row.unwrap().chars().enumerate()
            .map(|(x, c)| match c {
                '.' => false,
                '#' => true,
                _ => {
                    guard.y = y as i32;
                    guard.x = x as i32;
                    guard.dir = match c {
                        '^' => 0,
                        '>' => 1,
                        'v' => 2,
                        '<' => 3,
                        _ => panic!("Invalid character")
                    };
                    false
                }
            }).collect()
        ).collect();

    assert_ne!(guard.y, -1);

    return (map, guard);
}

fn part1(map: &[Vec<bool>], guard: &Guard) -> i32 {
    let mut guard = guard.clone();
    let mut visited: HashSet<(i32, i32)> = HashSet::new();

    loop {
        visited.insert((guard.y, guard.x));

        let ny = guard.y + DY[guard.dir];
        let nx = guard.x + DX[guard.dir];

        if ny < 0 || ny >= map.len() as i32 || nx < 0 || nx >= map[0].len() as i32 {
            break;
        } else if map[ny as usize][nx as usize] {
            guard.dir = (guard.dir + 1) % 4;
        } else {
            guard.y = ny;
            guard.x = nx;
        }
    }


    return visited.len() as i32;
}

fn part2(map: &mut [Vec<bool>], guard: &Guard) -> i32 {

    return (0..map.len()).map(|y| (0..map[0].len()).filter(|&x| {
        if map[y][x] {
            return false;
        }

        if y == guard.y as usize && x == guard.x as usize {
            return false;
        }

        map[y][x] = true;

        let mut guard = guard.clone();
        let mut visited: HashSet<Guard> = HashSet::new();

        while !visited.contains(&guard) {
            visited.insert(guard.clone());

            let ny = guard.y + DY[guard.dir];
            let nx = guard.x + DX[guard.dir];

            if ny < 0 || ny >= map.len() as i32 || nx < 0 || nx >= map[0].len() as i32 {
                map[y][x] = false;
                return false;
            } else if map[ny as usize][nx as usize] {
                guard.dir = (guard.dir + 1) % 4;
            } else {
                guard.y = ny;
                guard.x = nx;
            }
        }

        map[y][x] = false;
        return true;
    }).count() as i32).sum();
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

