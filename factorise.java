/* The first benchmark program. The Java language.
 * This will be used to test the various Java compilers.
 * This algorithm is the same one used across all of the benchmark programs,
 * to keep it fair.
 */

import java.io.File;
import java.io.InputStream;
import java.util.Scanner;

public class factorise {
    private static long int_sqrt(long n) {
        long x = n;
        long y = (x + 1) >>> 1;
        while (Long.compareUnsigned(y, x) < 0) {
            x = y;
            y = (x + Long.divideUnsigned(n, x)) >>> 1;
        }
        return x;
    }

    private static long factorise(long n) {
        if (
            n == 2 || n == 3 || n == 5 || n == 7
            || n == 11 || n == 13 || n == 17 || n == 19
            || n == 23 || n == 29 || n == 31 || n == 37
        ) return n;
        if (Long.remainderUnsigned(n, 2) == 0) return 2;
        if (Long.remainderUnsigned(n, 3) == 0) return 3;
        long end = int_sqrt(n);
        for (long i = 6; Long.compareUnsigned(i, end) <= 0; i += 6) {
            if (Long.remainderUnsigned(n, i - 1) == 0) return i - 1;
            if (Long.remainderUnsigned(n, i + 1) == 0) return i + 1;
        }
        return n;
    }

    public static void main(String[] args) throws Exception {
        if (args.length > 1) {
            System.out.printf(
                "Usage: java factorise | java factorise filename\n"
            );
            System.exit(1);
        }
        long start, end;
        File file = args.length == 1 ? new File(args[0]) : null;
        Scanner scanner = (file == 
            null ? new Scanner(System.in) : new Scanner(file)
        );
        start = System.nanoTime();
        long n, a;
        int lines;
        lines = scanner.nextInt();
        for (int i = 0; i < lines; i++) {
            n = scanner.nextLong();
            a = factorise(n);
            System.out.printf("%d = %d * %d\n", n, a, n / a);
        }
        end = System.nanoTime();
        if (file != null) scanner.close();
        System.out.printf("Time taken: %f s.\n", (
            (double)(end - start)) / 1e9
        );
    }
}
