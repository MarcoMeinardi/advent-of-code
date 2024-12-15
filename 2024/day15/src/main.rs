use std::time::Instant;
use std::io::{self, Read};

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
enum Cell {
    Wall,
    Empty,
    Box
}

static DYX: [(i32, i32); 4] = [(-1, 0), (0, 1), (1, 0), (0, -1)];

fn get_input() -> (Vec<Vec<Cell>>, Vec<usize>, (i32, i32)) {
    let stdin = io::stdin();
    let mut input = String::new();

    stdin.lock().read_to_string(&mut input).unwrap();

    let (grid, commands) = input.split_once("\n\n").unwrap();

    let mut py = -1;
    let mut px = -1;

    let grid = grid.lines().enumerate().map(|(y, line)| {
        line.chars().enumerate().map(|(x, c)| {
            match c {
                '#' => Cell::Wall,
                '.' => Cell::Empty,
                'O' => Cell::Box,
                '@' => {
                    py = y as i32;
                    px = x as i32;
                    Cell::Empty
                }
                _ => panic!("Invalid cell")
            }
        }).collect()
    }).collect();

    assert_ne!(py, -1);

    let commands = commands.chars().filter(|c| c != &'\n').map(|c| {
        match c {
            '^' => 0,
            '>' => 1,
            'v' => 2,
            '<' => 3,
            _ => panic!("Invalid command")
        }
    }).collect();

    return (grid, commands, (py, px));
}

fn part1(grid: &[Vec<Cell>], commands: &[usize], position: (i32, i32)) -> u64 {
    fn try_move(grid: &mut [Vec<Cell>], y: usize, x: usize, dyx: (i32, i32)) -> bool {
        if grid[y][x] == Cell::Empty {
            return true;
        }

        let ny = (y as i32 + dyx.0) as usize;
        let nx = (x as i32 + dyx.1) as usize;

        if grid[ny][nx] != Cell::Wall && try_move(grid, ny, nx, dyx) {
            grid[y][x] = Cell::Empty;
            grid[ny][nx] = Cell::Box;
            return true;
        }
        return false;
    }

    let mut grid = grid.to_vec();
    let (mut y, mut x) = position;

    grid[y as usize][x as usize] = Cell::Box;

    commands.iter().map(|c| DYX[*c]).for_each(|dyx| {
        if try_move(&mut grid, y as usize, x as usize, dyx) {
            y += dyx.0;
            x += dyx.1;
        }
    });

    grid[y as usize][x as usize] = Cell::Empty;

    return grid.iter().enumerate().skip(1).map(|(y, row)|
        row.iter().enumerate().skip(1).map(|(x, cell)|
            if *cell == Cell::Box {
                (y * 100 + x) as u64
            } else {
                0
            }
        ).sum::<u64>()
    ).sum();
}

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
enum WCell {
    Wall,
    Empty,
    Lbox,
    Rbox
}

fn part2(grid: &[Vec<Cell>], commands: &[usize], position: (i32, i32)) -> u64 {
    fn try_move(grid: &[Vec<WCell>], y: usize, x: usize, dyx: (i32, i32)) -> bool {
        if grid[y][x] == WCell::Empty {
            return true;
        }

        let ny = (y as i32 + dyx.0) as usize;
        let nx = (x as i32 + dyx.1) as usize;

        if grid[ny][nx] != WCell::Wall {
            if y == ny {
                if try_move(grid, y, nx, dyx) {
                    return true;
                }
            } else if grid[y][x] == WCell::Empty {
                return true;
            } else {
                let hnx = (x as i32 + if grid[y][x] == WCell::Lbox { 1 } else { -1 }) as usize;
                if grid[ny][hnx] != WCell::Wall && try_move(grid, ny, x, dyx) && try_move(grid, ny, hnx, dyx) {
                    return true;
                }
            }
        }
        return false;
    }

    fn do_move(grid: &mut [Vec<WCell>], y: usize, x: usize, dyx: (i32, i32)) {
        if grid[y][x] == WCell::Empty {
            return;
        }

        let ny = (y as i32 + dyx.0) as usize;
        let nx = (x as i32 + dyx.1) as usize;

        if grid[ny][nx] != WCell::Wall {
            if y == ny {
                do_move(grid, y, nx, dyx);
                let hnx = (x as i32 + dyx.1 / 2) as usize;
                grid[y][nx] = grid[y][hnx];
                grid[y][hnx] = grid[y][x];
                grid[y][x] = WCell::Empty;
            } else if grid[y][x] != WCell::Empty {
                let hnx = (x as i32 + if grid[y][x] == WCell::Lbox { 1 } else { -1 }) as usize;
                do_move(grid, ny, x, dyx);
                do_move(grid, ny, hnx, dyx);
                grid[ny][x] = grid[y][x];
                grid[ny][hnx] = grid[y][hnx];
                grid[y][x] = WCell::Empty;
                grid[y][hnx] = WCell::Empty;
            }
        }
    }

    static DYX2: [(i32, i32); 4] = [(-1, 0), (0, 2), (1, 0), (0, -2)];

    let mut wgrid = vec![vec![WCell::Empty; grid[0].len() * 2]; grid.len()];

    grid.iter().enumerate().for_each(|(y, row)| {
        row.iter().enumerate().for_each(|(x, cell)| {
            match cell {
                Cell::Wall => {
                    wgrid[y][x * 2] = WCell::Wall;
                    wgrid[y][x * 2 + 1] = WCell::Wall;
                },
                Cell::Empty => {
                    wgrid[y][x * 2] = WCell::Empty;
                    wgrid[y][x * 2 + 1] = WCell::Empty;
                },
                Cell::Box => {
                    wgrid[y][x * 2] = WCell::Lbox;
                    wgrid[y][x * 2 + 1] = WCell::Rbox;
                }
            }
        });
    });

    let (mut y, mut x) = position;
    x *= 2;
    
    for command in commands {
        let ny = y + DYX[*command].0;
        let nx = x + DYX[*command].1;

        if wgrid[ny as usize][nx as usize] != WCell::Wall && try_move(&wgrid, ny as usize, nx as usize, DYX2[*command]) {
            do_move(&mut wgrid, ny as usize, nx as usize, DYX2[*command]);
            y = ny;
            x = nx;
        }
    }

    return wgrid.iter().enumerate().skip(1).map(|(y, row)|
        row.iter().enumerate().skip(1).map(|(x, cell)|
            if *cell == WCell::Lbox {
                (y * 100 + x) as u64
            } else {
                0
            }
        ).sum::<u64>()
    ).sum();
}

fn main() {
    let (grid, commands, position) = get_input();

    let start_part_1 = Instant::now();
    let result_part_1 = part1(&grid, &commands, position);
    let end_part_1 = Instant::now();
    println!("Part 1: {} ( {:.2?} )", result_part_1, end_part_1.duration_since(start_part_1));

    let start_part_2 = Instant::now();
    let result_part_2 = part2(&grid, &commands, position);
    let end_part_2 = Instant::now();
    println!("Part 2: {} ( {:.2?} )", result_part_2, end_part_2.duration_since(start_part_2));
}
