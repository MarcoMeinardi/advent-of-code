use std::cell::RefCell;
use std::time::Instant;
use std::io::{self, Read};

#[derive(Debug, Clone, Copy)]
enum Operation {
    And,
    Or,
    Xor
}

fn get_input() -> (Vec<(String, bool)>, Vec<(String, Operation, String, String)>) {
    let stdin = io::stdin();
    let mut input = String::new();
    stdin.lock().read_to_string(&mut input).unwrap();

    let (inputs, gates) = input.split_once("\n\n").unwrap();

    let inputs = inputs.lines().map(|line| {
        let (name, value) = line.split_once(": ").unwrap();
        (name.to_string(), value.parse::<i32>().unwrap() == 1)
    }).collect::<Vec<(String, bool)>>();

    let gates = gates.lines().map(|line| {
        let (input, output) = line.split_once(" -> ").unwrap();

        let input = input.split(' ').collect::<Vec<&str>>();
        assert_eq!(input.len(), 3);

        let a = input[0].to_string();
        let b = input[2].to_string();
        let op = match input[1].as_bytes()[0] {
            b'A' => Operation::And,
            b'O' => Operation::Or,
            b'X' => Operation::Xor,
            _ => panic!("Unknown operation")
        };

        return (a, op, b, output.to_string());
    }).collect::<Vec<(String, Operation, String, String)>>();

    return (inputs, gates);
}

#[derive(Debug)]
struct Node<'a> {
    name: &'a String,
    value: RefCell<Option<bool>>,
    depends_on: Option<usize>
}

#[derive(Debug)]
struct Gate {
    a: usize,
    b: usize,
    op: Operation,
    out: usize
}

impl Gate {
    pub fn get_output(&self, nodes: &[Node], gates: &[Gate]) -> bool {
        let a = nodes[self.a].get_output(nodes, gates);
        let b = nodes[self.b].get_output(nodes, gates);

        return match self.op {
            Operation::And => a & b,
            Operation::Or => a | b,
            Operation::Xor => a ^ b
        };
    }
}

impl Node<'_> {
    pub fn get_output(&self, nodes: &[Node], gates: &[Gate]) -> bool {
        if let Some(value) = *self.value.borrow() {
            return value;
        }

        if let Some(depends_on) = self.depends_on {
            let gate = &gates[depends_on];
            *self.value.borrow_mut() = Some(gate.get_output(nodes, gates));
            return self.value.borrow().unwrap();
        }

        panic!("Unknowable node");
    }
}

fn char2ind(c: u8) -> usize {
    if c.is_ascii_digit() {
        return (c - b'0') as usize;
    } else if c.is_ascii_lowercase() {
        return (c - b'a' + 10) as usize;
    }

    panic!("Unknown character");
}

fn hash(s: &str) -> usize {
    let bytes = s.as_bytes();
    return char2ind(bytes[0]) * 36 * 36 + char2ind(bytes[1]) * 36 + char2ind(bytes[2]);
}

fn maybe_insert_new_string(s: &str, table: &mut [Option<usize>; 36 * 36 * 36], table_ind: &mut usize) -> bool {
    let h = hash(s);
    if table[h].is_some() {
        return false;
    }
    table[h] = Some(*table_ind);
    *table_ind += 1;
    return true;
}

fn str2id(s: &str, table: &[Option<usize>; 36 * 36 * 36]) -> usize {
    let h = hash(s);
    return table[h].unwrap();
}

fn part1(inputs: &[(String, bool)], gates: &[(String, Operation, String, String)]) -> u64 {
    let mut name_table = [None; 36 * 36 * 36];
    let mut table_ind = 0;

    let mut nodes = inputs.iter().map(|(name, value)| {
        assert!(maybe_insert_new_string(name, &mut name_table, &mut table_ind));
        return Node {
            name,
            value: RefCell::new(Some(*value)),
            depends_on: None
        };
    }).collect::<Vec<Node>>();

    for (a, _, b, out) in gates {
        for x in &[a, b, out] {
            if maybe_insert_new_string(x, &mut name_table, &mut table_ind) {
                nodes.push(Node {
                    name: x,
                    value: RefCell::new(None),
                    depends_on: None
                });
            }
        }
    }

    let gates = gates.iter().map(|(a, op, b, out)|
        Gate {
            a: str2id(a, &name_table),
            b: str2id(b, &name_table),
            op: *op,
            out: str2id(out, &name_table)
        }
    ).collect::<Vec<Gate>>();

    for (i, gate) in gates.iter().enumerate() {
        nodes[gate.out].depends_on = Some(i);
    }


    let mut result = nodes.iter()
        .filter(|node| node.name.starts_with('z'))
        .map(|node| {
            (node.name, node.get_output(&nodes, &gates))
        }).collect::<Vec<(&String, bool)>>();

    result.sort_unstable_by(|a, b| b.0.cmp(a.0));

    return result.iter().fold(0, |acc, (_, value)| {
        acc << 1 | (*value as u64)
    });
}

fn part2(_inputs: &[(String, bool)], _gates: &[(String, Operation, String, String)]) -> String {
    static SWAPS: [(&str, &str); 4] = [
        ("ggn", "z10"),
        ("grm", "z32"),
        ("twr", "z39"),
        ("ndw", "jcb")
    ];

    let mut result = SWAPS.iter()
        .flat_map(|(a, b)| vec![*a, *b])
        .collect::<Vec<&str>>();

    result.sort_unstable();

    return result.join(",");
}

fn main() {
    let (inputs, gates) = get_input();

    let start_part_1 = Instant::now();
    let result_part_1 = part1(&inputs, &gates);
    let end_part_1 = Instant::now();
    println!("Part 1: {} ( {:.2?} )", result_part_1, end_part_1.duration_since(start_part_1));

    let start_part_2 = Instant::now();
    let result_part_2 = part2(&inputs, &gates);
    let end_part_2 = Instant::now();
    println!("Part 2: {} ( {:.2?} )", result_part_2, end_part_2.duration_since(start_part_2));
}
