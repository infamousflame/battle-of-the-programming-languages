/* The first benchmark program. The C language.
 * This will be used to test the various C compilers.
 * This algorithm is the same one used across all of the benchmark programs,
 * to keep it fair.
 */

#include <inttypes.h>
#include <stdio.h>
#include <time.h>


uint64_t int_sqrt(uint64_t n) {
    uint64_t x = n;
    uint64_t y = (x + 1) >> 1;
    while (y < x) {
        x = y;
        y = (x + n / x) >> 1;
    }
    return x;
}


uint64_t factorise(uint64_t n) {
    if (
        n == 2 || n == 3 || n == 5 || n == 7
        || n == 11 || n == 13 || n == 17 || n == 19
        || n == 23 || n == 29 || n == 31 || n == 37
    ) return n;
    if (n % 2 == 0) return 2;
    if (n % 3 == 0) return 3;
    uint64_t end = int_sqrt(n);
    for (uint64_t i = 6; i <= end; i += 6) {
        if (n % (i - 1) == 0) return i - 1;
        if (n % (i + 1) == 0) return i + 1;
    }
    return n;
}


int main(int argc, char **argv) {
    if (argc > 2 || argc < 1) {
        printf("Usage: %s | %s filename\n", argv[0], argv[0]);
        return 1;
    }
    clock_t start, end;
    FILE* stream = argc == 2 ? fopen(argv[1], "r") : stdin;
    start = clock();
    uint64_t n, a;
    int lines;
    fscanf(stream, "%d", &lines);
    for (int i = 0; i < lines; i++) {
        fscanf(stream, "%" PRIu64, &n);
        a = factorise(n);
        printf("%" PRIu64 " * %" PRIu64 " = %" PRIu64 "\n", a, n / a, n);
    }
    end = clock();
    if (stream != stdin) fclose(stream);
    printf("Time taken: %f s.\n", ((double)(end - start)) / CLOCKS_PER_SEC);
    return 0;
}
