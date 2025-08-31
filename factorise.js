/* The fifth benchmark program. The JavaScript language.
 * This will be used to test the various JavaScript compilers.
 * This algorithm is the same one used across all of the benchmark programs,
 * to keep it fair.
 */

const fs = require('fs');
const { performance } = require('perf_hooks');

function int_sqrt(n) {
    let x = n;
    let y = (x + 1) >> 1;
    while (y < x) {
        x = y;
        y = (x + Math.floor(n / x)) >> 1;
    }
    return x;
}

function factorise(n) {
    if (
        n == 2 || n == 3 || n == 5 || n == 7
        || n == 11 || n == 13 || n == 17 || n == 19
        || n == 23 || n == 29 || n == 31 || n == 37
    ) return n;
    if (n % 2 == 0) return 2;
    if (n % 3 == 0) return 3;
    let end = int_sqrt(n);
    for (let i = 6; i <= end; i += 6) {
        if (n % (i - 1) == 0) return i - 1;
        if (n % (i + 1) == 0) return i + 1;
    }
    return n;
}


async function main() {
    const readline = require('readline');
    let argv = process.argv.slice(1);
    if (argv.length > 2 || argv.length < 1) {
        console.log("Usage: node factorise.js | node factorise.js filename");
        return 1;
    }
    let stream = argv.length == 2 ? fs.createReadStream(argv[1]) : process.stdin;
    const rl = readline.createInterface({
        input: stream,
        crlfDelay: Infinity
    });

    let start = performance.now();
    let lines = -1;
    let i = 0;
    for await (const line of rl) {
        if (lines === -1) {
            lines = parseInt(line);
            continue;
        }
        let n = parseInt(line);
        let a = factorise(n);
        console.log(`${n} = ${a} * ${Math.floor(n / a)}`);
        i++;
        if (i >= lines) {
            break;
        }
    }

    let end = performance.now();
    if (stream != process.stdin) stream.close();
    console.log(`Time taken: ${(end - start) / 1000} s.`);
    return 0;
}

main().then(process.exit);
