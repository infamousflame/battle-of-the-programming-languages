"""The second benchmark program. The Python language.
This will be used to test the various Python compilers.
This algorithm is the same one used across all of the benchmark programs,
to keep it fair.
"""

from sys import argv, exit as sys_exit, stdin
from time import time


def int_sqrt(n: int) -> int:
    x: int = n
    y: int = (x + 1) >> 1
    while y < x:
        x = y
        y = (x + n // x) >> 1
    return x


def factorise(n: int) -> int:
    if (
        n == 2 or n == 3 or n == 5 or n == 7
        or n == 11 or n == 13 or n == 17 or n == 19
        or n == 23 or n == 29 or n == 31 or n == 37
    ): return n
    if n % 2 == 0: return 2
    if n % 3 == 0: return 3
    end: int = int_sqrt(n)
    for i in range(6, end + 1, 6):
        if n % (i - 1) == 0: return i - 1
        if n % (i + 1) == 0: return i + 1
    return n


if __name__ == "__main__":
    if len(argv) > 2 or len(argv) < 1:
        print(f'Usage: {argv[0]} | {argv[0]} filename')
        sys_exit(1)
    stream = open(argv[1], 'r') if len(argv) == 2 else stdin
    start: float = time()
    lines: int = int(stream.readline())
    for i in range(lines):
        n: int = int(stream.readline())
        a: int = factorise(n)
        print(f'{n} = {a} * {n // a}')
    end: float = time()
    if stream != stdin: stream.close()
    print(f'Time taken: {end - start} s.')
