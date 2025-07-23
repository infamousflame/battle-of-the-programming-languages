/* This program just creates the problems for the benchmarked programs to
 * solve. The problem in question is factorising a 64-bit RSA key.
 * Non-cryptographic strength is used here because I do not have forever.
 */

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
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

char is_prime(uint64_t n) {
    if (
        n == 2 || n == 3 || n == 5 || n == 7
        || n == 11 || n == 13 || n == 17 || n == 19
        || n == 23 || n == 29 || n == 31 || n == 37
    ) return 1;
    if (n < 37) return 0;
    if (n % 2 == 0 || n % 3 == 0) return 0;
    uint64_t end = int_sqrt(n);
    for (uint64_t i = 6; i <= end; i += 6)
        if (n % (i - 1) == 0 || n % (i + 1) == 0)
            return 0;
    return 1;
}

int main(int argc, char **argv) {
    if (argc > 3 || argc < 2) {
        fprintf(stderr, "Usage: %s lines | %s lines filename\n", argv[0], argv[0]);
        return 1;
    }
    srand(time(NULL));
    FILE *stream = argc == 3 ? fopen(argv[2], "w") : stdout;
    uint64_t a, b;
    int lines;
    sscanf(argv[1], "%d", &lines);
    fprintf(stream, "%d\n", lines);
    for (int i = 0; i < lines; i++) {
        do a = rand(); while (!is_prime(a));
        do b = rand(); while (!is_prime(b));
        printf("%" PRIu64 " * %" PRIu64 " = %" PRIu64 "\n", a, b, a * b);
        if (stream != stdout) fprintf(stream, "%" PRIu64 "\n", a * b);
    }
    if (stream != stdout) fclose(stream);
    return 0;
}
