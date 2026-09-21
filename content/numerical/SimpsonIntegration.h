/**
 * Author: Joaquin Bonora, Juan Manuel Duarte
 * Date: 2026-08-26
 * License: CC0
 * Source: folklore
 * Description: Composite Simpson rule for numerical integration of f over
 * [a,b] using n subintervals, rounding n up to the next even number.
 * Time: O(N) evaluations of f.
 * Status: untested
 */
#pragma once
ld simpsonRule(function<ld(ld)> f, ld a, ld b, int n) {
    // Make sure n is even
    if (n % 2 != 0) {
        n++;
    }
    ld h = (b - a) / n;
    ld s = f(a) + f(b);

    // Sum the interior terms with their weights
    L(i, 1, n) {
        ld x = a + i * h;
        s += (i % 2 == 1 ? 4.0L : 2.0L) * f(x);
    }
    // Multiply by h/3
    return (h / 3.0L) * s;
}
