use std::collections::BinaryHeap;
use std::cmp::Reverse;
use std::time::Instant;
use std::io::{self, BufRead};

fn get_input() -> (Vec<Vec<bool>>, (usize, usize), (usize, usize)) {
    let stdin = io::stdin();

    let mut sy = 0;
    let mut sx = 0;
    let mut ey = 0;
    let mut ex = 0;

    let grid = stdin.lock().lines()
        .enumerate()
        .map(|(y, row)| row.unwrap()
            .chars()
            .enumerate()
            .map(|(x, c)|
                match c {
                    '#' => false,
                    '.' => true,
                    'S' => {
                        assert_eq!(sy, 0);
                        sy = y;
                        sx = x;
                        true
                    },
                    'E' => {
                        assert_eq!(ey, 0);
                        ey = y;
                        ex = x;
                        true
                    },
                    _ => panic!("Invalid character")
                }
            )
            .collect()
        )
        .collect();

    return (grid, (sy, sx), (ey, ex));
}

static DYX: [(i32, i32); 4] = [(0, 1), (1, 0), (0, -1), (-1, 0)];

fn dijkstra(grid: &[Vec<bool>], start: (usize, usize), end: (usize, usize), costs: &mut [Vec<Vec<u64>>]) {
    let mut queue = BinaryHeap::new();

    queue.push((Reverse(0), start.0, start.1, 0));
    costs[start.0][start.1][0] = 0;

    while !queue.is_empty() {
        let (Reverse(cost), y, x, dir) = queue.pop().unwrap();

        if costs[y as usize][x as usize][dir] < cost {
            continue;
        }

        if y == end.0 && x == end.1 {
            return;
        }

        let nexts = [
            (cost + 1, (y as i32 + DYX[dir].0) as usize, (x as i32 + DYX[dir].1) as usize, dir),
            (cost + 1000, y, x, (dir + 1) % 4),
            (cost + 1000, y, x, (dir + 3) % 4)
        ];

        for (ncost, ny, nx, ndir) in nexts {
            if grid[ny][nx] {
                if ncost < costs[ny][nx][ndir] {
                    costs[ny][nx][ndir] = ncost;
                    queue.push((Reverse(ncost), ny, nx, ndir));
                }
            }
        }
    }
}

fn part1(grid: &[Vec<bool>], start: (usize, usize), end: (usize, usize)) -> u64 {
    let mut costs = vec![vec![vec![u64::MAX; 4]; grid[0].len()]; grid.len()];
    dijkstra(grid, start, end, &mut costs);

    return costs[end.0][end.1].iter().cloned().min().unwrap();
}

fn part2(grid: &[Vec<bool>], start: (usize, usize), end: (usize, usize)) -> u64 {

    fn mark_best_paths(
        y: usize,
        x: usize,
        dir: usize,
        costs: &[Vec<Vec<u64>>],
        is_best_path: &mut [Vec<Vec<bool>>]
    ) {
        if is_best_path[y][x][dir] {
            return;
        }

        is_best_path[y][x][dir] = true;

        let cost = costs[y][x][dir];

        let prevs = [
            (cost - 1, (y as i32 - DYX[dir].0) as usize, (x as i32 - DYX[dir].1) as usize, dir),
            (cost - 1000, y, x, (dir + 3) % 4),
            (cost - 1000, y, x, (dir + 1) % 4)
        ];

        for (pcost, py, px, pdir) in prevs {
            if pcost > u64::MAX / 2 {  // overflows
                continue;
            }

            let real_pcost = costs[py][px][pdir];
            if real_pcost == pcost {
                mark_best_paths(py, px, pdir, costs, is_best_path);
            }
        }
    }

    let mut costs = vec![vec![vec![u64::MAX; 4]; grid[0].len()]; grid.len()];
    dijkstra(grid, start, (0, 0), &mut costs);

    let mut is_best_path = vec![vec![vec![false; 4]; grid[0].len()]; grid.len()];
    let min_cost = costs[end.0][end.1].iter().cloned().min().unwrap();
    for dir in 0..4 {
        if costs[end.0][end.1][dir] == min_cost {
            mark_best_paths(end.0, end.1, dir, &costs, &mut is_best_path);
        }
    }

    return is_best_path.iter().flatten().filter(|&b| b.iter().any(|&x| x)).count() as u64;
}

fn main() {
    let (grid, start, end) = get_input();

    let start_part_1 = Instant::now();
    let result_part_1 = part1(&grid, start, end);
    let end_part_1 = Instant::now();
    println!("Part 1: {} ( {:.2?} )", result_part_1, end_part_1.duration_since(start_part_1));

    let start_part_2 = Instant::now();
    let result_part_2 = part2(&grid, start, end);
    let end_part_2 = Instant::now();
    println!("Part 2: {} ( {:.2?} )", result_part_2, end_part_2.duration_since(start_part_2));
}
