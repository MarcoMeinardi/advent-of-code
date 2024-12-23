use std::collections::BTreeSet;
use std::time::Instant;
use std::io::{self, BufRead};

fn get_input() -> Vec<(String, String)> {
    let stdin = io::stdin();
    return stdin.lock().lines()
        .map(|line| line.unwrap())
        .map(|line| {
            let (a, b) = line.split_once('-').unwrap();
            return (a.to_string(), b.to_string());
        })
        .collect();
}

fn hash(s: &str) -> usize {
    return (s.as_bytes()[0] - b'a') as usize * 26 + (s.as_bytes()[1] - b'a') as usize;
}

fn str2id<'a>(s: &'a String, table: &mut [Option<usize>; 26 * 26], table_ind: &mut usize, r_table: &mut [Option<&'a String>; 26 * 26]) -> usize {
    let h = hash(s);
    if let Some(id) = table[h] {
        return id;
    }

    table[h] = Some(*table_ind);
    r_table[*table_ind] = Some(s);
    *table_ind += 1;
    return *table_ind - 1;
}

fn part1(input: &[(String, String)]) -> u64 {
    let mut table = [None; 26 * 26];
    let mut r_table = [None; 26 * 26];
    let mut table_ind = 0;

    let nodes = input.iter()
        .map(|(a, b)|
            (
                str2id(a, &mut table, &mut table_ind, &mut r_table),
                str2id(b, &mut table, &mut table_ind, &mut r_table)
            )
        )
        .collect::<Vec<_>>();

    let n = table_ind;

    let mut adj = vec![vec![false; n]; n];

    for (a, b) in nodes {
        adj[a][b] = true;
        adj[b][a] = true;
    }

    let mut total = 0;

    for i in 0..n - 2 {
        for j in i + 1..n - 1 {
            if !adj[i][j] {
                continue;
            }
            for k in j + 1..n {
                if
                    adj[j][k] && adj[k][i] &&
                    (r_table[i].unwrap().starts_with('t') || r_table[j].unwrap().starts_with('t') || r_table[k].unwrap().starts_with('t'))
                {
                    total += 1;
                }
            }
        }
    }

    return total;
}

fn part2(input: &[(String, String)]) -> String {
    #[allow(non_snake_case)]
    fn bron_kerbosch(R: &mut BTreeSet<usize>, P: &mut BTreeSet<usize>, X: &mut BTreeSet<usize>, adj: &Vec<BTreeSet<usize>>, best: &mut BTreeSet<usize>) {
        if P.is_empty() && X.is_empty() {
            if R.len() > best.len() {
                *best = R.clone();
            }
            return;
        }

        while !P.is_empty() {
            let v = *P.iter().next().unwrap();

            R.insert(v);
            let mut P_new = BTreeSet::new();

            for p in P.iter() {
                if adj[v].contains(p) {
                    P_new.insert(*p);
                }
            }

            let mut X_new = BTreeSet::new();
            for x in X.iter() {
                if adj[v].contains(x) {
                    X_new.insert(*x);
                }
            }

            bron_kerbosch(R, &mut P_new, &mut X_new, adj, best);

            R.remove(&v);
            P.remove(&v);
            X.insert(v);
        }
    }

    let mut table = [None; 26 * 26];
    let mut r_table = [None; 26 * 26];
    let mut table_ind = 0;

    let nodes = input.iter()
        .map(|(a, b)|
            (
                str2id(a, &mut table, &mut table_ind, &mut r_table),
                str2id(b, &mut table, &mut table_ind, &mut r_table)
            )
        )
        .collect::<Vec<_>>();

    let n = table_ind;

    let mut adj = vec![BTreeSet::new(); n];

    for (a, b) in nodes {
        adj[a].insert(b);
        adj[b].insert(a);
    }

    let mut best = BTreeSet::new();

    let mut vertices = BTreeSet::new();
    for i in 0..n {
        vertices.insert(i);
    }

    bron_kerbosch(&mut BTreeSet::new(), &mut vertices, &mut BTreeSet::new(), &adj, &mut best);

    let mut result = best.iter().map(|i| r_table[*i].unwrap().clone()).collect::<Vec<_>>();
    result.sort_unstable();
    let result = result.join(",");

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
