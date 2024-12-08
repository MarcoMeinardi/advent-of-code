use array_init::array_init;
use std::collections::HashSet;
use std::time::Instant;
use std::io::{self, BufRead};

fn get_input() -> Vec<Vec<u8>> {
    let stdin = io::stdin();
    return stdin.lock().lines().map(|x| x.unwrap().into_bytes()).collect();
}

fn get_nodes(input: &[Vec<u8>]) -> [Vec<(i32, i32)>; 0x80 - 0x20] {
    let mut nodes: [Vec<(i32, i32)>; 0x80 - 0x20] = array_init(|_| Vec::new());

    input.iter().enumerate().for_each(|(y, line)| {
        line.iter().enumerate().for_each(|(x, &c)| {
            if c != b'.' {
                nodes[c as usize - 0x30].push((x as i32, y as i32));
            }
        });
    });

    return nodes;
}

fn part1(input: &[Vec<u8>]) -> i32 {
    let width = input[0].len() as i32;
    let height = input.len() as i32;

    let nodes = get_nodes(input);

    let mut antinodes: HashSet<(i32, i32)> = HashSet::new();

    nodes.iter().for_each(|node_list| {
        for (x1, y1) in node_list.iter() {
            for (x2, y2) in node_list.iter() {
                if (x1, y1) != (x2, y2) {
                    let dx = x2 - x1;
                    let dy = y2 - y1;

                    if (0..width).contains(&(x1 - dx)) && (0..height).contains(&(y1 - dy)) {
                        antinodes.insert((x1 - dx, y1 - dy));
                    }
                    if (0..width).contains(&(x2 + dx)) && (0..height).contains(&(y2 + dy)) {
                        antinodes.insert((x2 + dx, y2 + dy));
                    }
                }
            }
        }
    });

    return antinodes.len() as i32;
}

fn part2(input: &[Vec<u8>]) -> i32 {
    let width = input[0].len() as i32;
    let height = input.len() as i32;

    let nodes = get_nodes(input);

    let mut antinodes: HashSet<(i32, i32)> = HashSet::new();

    nodes.iter().for_each(|node_list| {
        for (x1, y1) in node_list.iter() {
            antinodes.insert((*x1, *y1));
            for (x2, y2) in node_list.iter() {
                if (x1, y1) != (x2, y2) {
                    let dx = x2 - x1;
                    let dy = y2 - y1;

                    let mut xx;
                    let mut yy;

                    xx = x1 - dx;
                    yy = y1 - dy;
                    while (0..width).contains(&xx) && (0..height).contains(&yy) {
                        antinodes.insert((xx, yy));
                        xx -= dx;
                        yy -= dy;
                    }

                    xx = x2 + dx;
                    yy = y2 + dy;
                    while (0..width).contains(&xx) && (0..height).contains(&yy) {
                        antinodes.insert((xx, yy));
                        xx += dx;
                        yy += dy;
                    }
                }
            }
        }
    });

    return antinodes.len() as i32;
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
