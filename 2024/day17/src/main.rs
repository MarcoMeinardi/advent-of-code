use z3::{ast::BV, ast::Ast, Context, Config, Solver};
use num_derive::FromPrimitive;
use num_traits::FromPrimitive;

use std::time::Instant;
use std::io::{self, BufRead};


fn get_input() -> ((u64, u64, u64), Vec<u8>) {
    let stdin = io::stdin();
    let lines = stdin.lock().lines().map(|x| x.unwrap()).collect::<Vec<_>>();

    assert_eq!(lines.len(), 5);

    let a = lines[0].split(' ').last().unwrap().parse().unwrap();
    let b = lines[1].split(' ').last().unwrap().parse().unwrap();
    let c = lines[2].split(' ').last().unwrap().parse().unwrap();

    let prog = lines[4].split_once(' ').unwrap().1.split(',').map(|x| x.parse().unwrap()).collect();

    return ((a, b, c), prog);
}

struct VM {
    code: Vec<u8>,
    regs: [u64; 3],
    ip: usize,
    out: Vec<u8>
}

#[derive(FromPrimitive, Debug)]
enum Instr {
    ADV,
    BXL,
    BST,
    JNZ,
    BXC,
    OUT,
    BDV,
    CDV
}

enum Reg {
    A,
    B,
    C
}

impl VM {
    pub fn new(code: &[u8], regs: &(u64, u64, u64)) -> Self {
        return Self {
            code: code.to_vec(),
            regs: [regs.0, regs.1, regs.2],
            ip: 0,
            out: Vec::new()
        };
    }

    fn get_combo(&self, val: u8) -> u64 {
        if val < 4 {
            return val as u64
        }
        if val < 7 {
            return self.regs[val as usize - 4];
        }
        panic!("Invalid combo value");
    }

    fn parse_instruction(&mut self) -> Option<(Instr, u8)> {
        if self.ip + 1 >= self.code.len() {
            return None
        }
        let res = Some((FromPrimitive::from_u8(self.code[self.ip]).unwrap(), self.code[self.ip + 1]));
        self.ip += 2;
        return res;
    }

    fn adv(&mut self, op: u8) {
        self.regs[Reg::A as usize] >>= self.get_combo(op);
    }

    fn bxl(&mut self, op: u8) {
        self.regs[Reg::B as usize] ^= op as u64;
    }

    fn bst(&mut self, op: u8) {
        self.regs[Reg::B as usize] = self.get_combo(op) & 0b111;
    }

    fn jnz(&mut self, op: u8) {
        if self.regs[Reg::A as usize] != 0 {
            self.ip = op as usize;
        }
    }

    fn bxc(&mut self, _: u8) {
        self.regs[Reg::B as usize] ^= self.regs[Reg::C as usize];
    }

    fn out(&mut self, op: u8) {
        self.out.push((self.get_combo(op) & 0b111) as u8);
    }

    fn bdv(&mut self, op: u8) {
        self.regs[Reg::B as usize] = self.regs[Reg::A as usize] >> self.get_combo(op);
    }

    fn cdv(&mut self, op: u8) {
        self.regs[Reg::C as usize] = self.regs[Reg::A as usize] >> self.get_combo(op);
    }

    pub fn run(&mut self) {
        while let Some((instr, op)) = self.parse_instruction() {
            match instr {
                Instr::ADV => { self.adv(op) },
                Instr::BXL => { self.bxl(op) },
                Instr::BST => { self.bst(op) },
                Instr::JNZ => { self.jnz(op) },
                Instr::BXC => { self.bxc(op) },
                Instr::OUT => { self.out(op) },
                Instr::BDV => { self.bdv(op) },
                Instr::CDV => { self.cdv(op) }
            }
        }
    }

    pub fn get_output(&self) -> Vec<u8> {
        return self.out.clone();
    }
}

fn part1(regs: &(u64, u64, u64), prog: &[u8]) -> String {
    let mut vm = VM::new(prog, regs);
    vm.run();

    let out = vm.get_output();
    return out.iter().map(std::string::ToString::to_string).collect::<Vec<String>>().join(",")
}

struct SymVM<'a> {
    code: Vec<u8>,
    ctx: &'a Context,
    regs: [BV<'a>; 3],
    ip: usize,
    out: Vec<BV<'a>>,
    n_cycles: u64
}

impl<'a> SymVM<'a> {
    pub fn new(code: &[u8], a: &'a BV, regs: &(u64, u64), ctx: &'a Context, n_cycles: u64) -> Self {
        return Self {
            code: code.to_vec(),
            ctx,
            regs: [
                a.clone(),
                BV::from_u64(ctx, regs.0, 64),
                BV::from_u64(ctx, regs.1, 64)
            ],
            ip: 0,
            out: Vec::new(),
            n_cycles
        };
    }

    fn get_combo(&self, val: u8) -> BV<'a> {
        if val < 4 {
            return BV::from_u64(self.ctx, val as u64, 64);
        }
        if val < 7 {
            return self.regs[val as usize - 4].clone();
        }
        panic!("Invalid combo value");
    }

    fn parse_instruction(&mut self) -> Option<(Instr, u8)> {
        if self.ip + 1 >= self.code.len() {
            return None
        }
        let res = Some((FromPrimitive::from_u8(self.code[self.ip]).unwrap(), self.code[self.ip + 1]));
        self.ip += 2;
        return res;
    }

    fn adv(&mut self, op: u8) {
        self.regs[Reg::A as usize] = self.regs[Reg::A as usize].bvlshr(&self.get_combo(op));
    }

    fn bxl(&mut self, op: u8) {
        self.regs[Reg::B as usize] ^= &BV::from_u64(self.ctx, op as u64, 64);
    }

    fn bst(&mut self, op: u8) {
        self.regs[Reg::B as usize] = self.get_combo(op) & BV::from_u64(self.ctx, 0b111, 64);
    }

    fn jnz(&mut self, op: u8) {
        if self.n_cycles > 0 {
            self.n_cycles -= 1;
            self.ip = op as usize;
        }
    }

    fn bxc(&mut self, _: u8) {
        self.regs[Reg::B as usize] = &self.regs[Reg::B as usize] ^ &self.regs[Reg::C as usize];
    }

    fn out(&mut self, op: u8) {
        self.out.push(self.get_combo(op).bvand(&BV::from_u64(self.ctx, 0b111, 64)));
    }

    fn bdv(&mut self, op: u8) {
        self.regs[Reg::B as usize] = self.regs[Reg::A as usize].bvlshr(&self.get_combo(op));
    }

    fn cdv(&mut self, op: u8) {
        self.regs[Reg::C as usize] = self.regs[Reg::A as usize].bvlshr(&self.get_combo(op));
    }

    pub fn run(&mut self) {
        while let Some((instr, op)) = self.parse_instruction() {
            match instr {
                Instr::ADV => { self.adv(op) },
                Instr::BXL => { self.bxl(op) },
                Instr::BST => { self.bst(op) },
                Instr::JNZ => { self.jnz(op) },
                Instr::BXC => { self.bxc(op) },
                Instr::OUT => { self.out(op) },
                Instr::BDV => { self.bdv(op) },
                Instr::CDV => { self.cdv(op) }
            }
        }
    }

    pub fn get_output(&self) -> Vec<BV> {
        return self.out.clone();
    }

    pub fn get_regs(&self) -> [BV<'a>; 3] {
        return self.regs.clone();
    }
}

fn part2(regs: &(u64, u64, u64), prog: &[u8]) -> u64 {
    let (_, b, c) = regs;

    assert_eq!(*prog.last().unwrap(), 0);

    let cfg = Config::new();
    let ctx = Context::new(&cfg);
    let a = BV::new_const(&ctx, "a", 64);
    let mut vm = SymVM::new(prog, &a, &(*b, *c), &ctx, (prog.len() - 1) as u64);

    vm.run();

    let out = vm.get_output();
    assert_eq!(out.len(), prog.len());

    let solver = Solver::new(&ctx);

    for (sym_b, prog_b) in out.iter().zip(prog.iter()) {
        solver.assert(&sym_b._eq(&BV::from_u64(&ctx, *prog_b as u64, 64)));
    }
    let regs = vm.get_regs();
    solver.assert(&regs[Reg::A as usize]._eq(&BV::from_u64(&ctx, 0, 64)));

    assert_eq!(solver.check(), z3::SatResult::Sat);

    return solver.get_model().unwrap().eval(&a, true).unwrap().as_u64().unwrap();
}

fn main() {
    let (regs, prog) = get_input();

    let start_part_1 = Instant::now();
    let result_part_1 = part1(&regs, &prog);
    let end_part_1 = Instant::now();
    println!("Part 1: {} ( {:.2?} )", result_part_1, end_part_1.duration_since(start_part_1));

    let start_part_2 = Instant::now();
    let result_part_2 = part2(&regs, &prog);
    let end_part_2 = Instant::now();
    println!("Part 2: {} ( {:.2?} )", result_part_2, end_part_2.duration_since(start_part_2));
}
