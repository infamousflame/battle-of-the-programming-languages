/* The first benchmark program. The Rust language.
 * This will be used to test the various Rust compilers.
 * This algorithm is the same one used across all of the benchmark programs,
 * to keep it fair.
 */

use std::env::args;
use std::fs::File;
use std::io::{BufRead, BufReader};
use std::process::exit;
use std::time::Instant;

fn int_sqrt(n: u64) -> u64 {
    let mut x: u64 = n;
    let mut y: u64 = (x + 1) >> 1;
    while y < x {
        x = y;
        y = (x + n / x) >> 1;
    }
    x
}

fn factorise(n: u64) -> u64 {
    if n == 2 || n == 3 || n == 5 || n == 7
        || n == 11 || n == 13 || n == 17 || n == 19
        || n == 23 || n == 29 || n == 31 || n == 37
    { return n; }
    if n % 2 == 0 { return 2; }
    if n % 3 == 0 { return 3; }
    let end: u64 = int_sqrt(n);
    for i in (6..=end).step_by(6) {
        if n % (i - 1) == 0 { return i - 1; }
        if n % (i + 1) == 0 { return i + 1; }
    }
    n
}

fn main() {
    let argv: Vec<String> = args().collect();
    let argc: u32 = argv.len() as u32;
    if argc > 2 || argc < 1 {
        println!("Usage: {} | {} filename", argv[0], argv[0]);
        exit(1);
    }
    let (start, end): (Instant, Instant);
    let mut line: String = String::new();
    let mut stream: BufReader<File> = BufReader::new(File::open(if argc == 2 { &argv[1] } else { "/dev/stdin" }).unwrap());
    start = Instant::now();
    let (mut n, mut a): (u64, u64);
    let lines: u32;
    stream.read_line(&mut line).unwrap();
    lines = line.trim().parse().unwrap();
    for _ in 0..lines {
        stream.read_line(&mut line).unwrap();
        n = line.trim().parse().unwrap();
        a = factorise(n);
        println!("{} = {} * {}", n, a, n / a);
    }
    end = Instant::now();
    println!("Time taken: {} s.", (end - start).as_secs_f64());
}
