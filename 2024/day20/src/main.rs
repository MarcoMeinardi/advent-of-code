use std::collections::VecDeque;
use std::time::Instant;
use std::io;

fn get_input() -> (Vec<Vec<bool>>, (usize, usize), (usize, usize)) {
    let stdin = io::stdin();

    let mut start = (0, 0);
    let mut end = (0, 0);

    let grid = stdin.lines().enumerate().map(|(y, row)|
        row.unwrap().chars().enumerate().map(|(x, c)|
            match c {
                '#' => false,
                '.' => true,
                'S' => {
                    assert_eq!(start, (0, 0));
                    start = (y, x);
                    true
                },
                'E' => {
                    assert_eq!(end, (0, 0));
                    end = (y, x);
                    true
                },
                _ => panic!("Invalid character")
            }
        ).collect()
    ).collect();

    return (grid, start, end);
}

static DYX: [(i32, i32); 4] = [(-1, 0), (0, 1), (1, 0), (0, -1)];

fn bfs(grid: &[Vec<bool>], start: &(usize, usize), dist: &mut [Vec<i64>]) {
    let mut q = VecDeque::new();
    q.push_back((0, *start));
    dist[start.0][start.1] = 0;

    while let Some((cost, (y, x))) = q.pop_front() {
        debug_assert!(cost == dist[y][x]);

        for (dy, dx) in DYX {
            let ny = (y as i32 + dy) as usize;
            let nx = (x as i32 + dx) as usize;

            if grid[ny][nx] && dist[ny][nx] == i64::MAX {
                dist[ny][nx] = cost + 1;
                q.push_back((cost + 1, (ny, nx)));
            }
        }
    }
}

fn part1(grid: &[Vec<bool>], start: &(usize, usize), end: &(usize, usize)) -> u64 {
    let mut dist_from_start = vec![vec![i64::MAX; grid[0].len()]; grid.len()];
    let mut dist_from_end = vec![vec![i64::MAX; grid[0].len()]; grid.len()];

    bfs(grid, start, &mut dist_from_start);
    bfs(grid, end, &mut dist_from_end);

    let best = dist_from_start[end.0][end.1];

    return (1..grid.len() - 1).map(|y| (1..grid[0].len() - 1)
        .filter(|x| grid[y][*x])
        .map(|x|
            DYX.iter().filter(|(dy, dx)| {
                let ny = (y as i32 + dy * 2) as usize;
                let nx = (x as i32 + dx * 2) as usize;

                if ny >= grid.len() || nx >= grid[0].len() || !grid[ny][nx] {
                    return false;
                }

                return dist_from_end[ny][nx] + dist_from_start[y][x] + 2 <= best - 100;
            }).count() as u64
        ).sum::<u64>()
    ).sum();
}

fn part2(grid: &[Vec<bool>], start: &(usize, usize), end: &(usize, usize)) -> u64 {
    fn good_skips(
        grid: &[Vec<bool>],
        start: &(usize, usize),
        start_cost: i64,
        dist_from_end: &[Vec<i64>],
        best: i64
    ) -> u64 {
        let mut dist = vec![vec![i64::MAX; grid[0].len()]; grid.len()];
        let mut q = VecDeque::new();
        q.push_back((start_cost, *start));
        let mut result = 0;
        dist[start.0][start.1] = start_cost;

        while let Some((cost, (y, x))) = q.pop_front() {
            debug_assert!(cost == dist[y][x]);

            for (dy, dx) in DYX {
                let ny = (y as i32 + dy) as usize;
                let nx = (x as i32 + dx) as usize;

                if ny >= grid.len() || nx >= grid[0].len() || dist[ny][nx] < i64::MAX {
                    continue;
                }
                dist[ny][nx] = cost + 1;

                if grid[ny][nx] && dist_from_end[ny][nx] + cost + 1 <= best - 100 {
                    debug_assert!(cost + 1 - start_cost <= 20);
                    result += 1;
                }

                if cost < start_cost + 19 {
                    q.push_back((cost + 1, (ny, nx)));
                }
            }
        }

        return result;
    }

    let mut dist_from_start = vec![vec![i64::MAX; grid[0].len()]; grid.len()];
    let mut dist_from_end = vec![vec![i64::MAX; grid[0].len()]; grid.len()];

    bfs(grid, start, &mut dist_from_start);
    bfs(grid, end, &mut dist_from_end);

    let best = dist_from_start[end.0][end.1];

    return (1..grid.len() - 1).map(|y| (1..grid[0].len() - 1)
        .filter(|x| grid[y][*x] && dist_from_start[y][*x] < best - 1)
        .map(|x|
            good_skips(grid, &(y, x), dist_from_start[y][x], &dist_from_end, best)
        ).sum::<u64>()
    ).sum();
}

fn main() {
    let (grid, start, end) = get_input();

    let start_part_1 = Instant::now();
    let result_part_1 = part1(&grid, &start, &end);
    let end_part_1 = Instant::now();
    println!("Part 1: {} ( {:.2?} )", result_part_1, end_part_1.duration_since(start_part_1));

    let start_part_2 = Instant::now();
    let result_part_2 = part2(&grid, &start, &end);
    let end_part_2 = Instant::now();
    println!("Part 2: {} ( {:.2?} )", result_part_2, end_part_2.duration_since(start_part_2));
}
