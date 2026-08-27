/**
 * Author: Juan Manuel Duarte
 * Date: 2026-08-26
 * License: CC0
 * Source: folklore
 * Description: Simplex method for linear programs in standard form: maximise
 * c dot x subject to Ax <= b, x >= 0. Returns the optimal value together with
 * the achieving vector. Sentinels: NaN if the program is infeasible, and
 * +infinity if it is unbounded - test for both before using the value.
 * Time: exponential in the worst case; polynomial in practice on typical
 * contest inputs.
 * Status: untested
 */
#pragma once
pair<ld, vec<ld>> simplex(vec<vec<ld>> A, vec<ld> b, vec<ld> c) {
    const ld EPS = (ld)1e-9;
    int n = SZ(b), m = SZ(c);

    vec<int> X(m), Y(n);
    L(j, 0, m) X[j] = j;        
    L(i, 0, n) Y[i] = m + i;    

    ld z = 0; 

    auto pivot = [&](int x, int y) {
        swap(X[y], Y[x]);

        ld inv = (ld)1 / A[x][y];
        b[x] *= inv;
        L(j, 0, m) if (j != y) A[x][j] *= inv;
        A[x][y] = inv;

        L(i, 0, n) if (i != x && fabsl(A[i][y]) > EPS) {
            ld coef = A[i][y];
            b[i] -= coef * b[x];
            L(j, 0, m) if (j != y) A[i][j] -= coef * A[x][j];
            A[i][y] = -coef * A[x][y];
        }

        z += c[y] * b[x];
        L(j, 0, m) if (j != y) c[j] -= c[y] * A[x][j];
        c[y] = -c[y] * A[x][y];
        };

    while (true) {
        int x = -1, y = -1;
        ld mn = -EPS;
        L(i, 0, n) if (b[i] < mn) { mn = b[i]; x = i; }
        if (x < 0) break;
        L(j, 0, m) if (A[x][j] < -EPS) { y = j; break; }
        if (y < 0) {
            return { numeric_limits<ld>::quiet_NaN(), {} };
        }
        pivot(x, y);
    }

    while (true) {
        int y = -1, x = -1;
        ld mx = EPS;
        L(j, 0, m) if (c[j] > mx) { mx = c[j]; y = j; }
        if (y < 0) break;

        ld best = numeric_limits<ld>::infinity();
        L(i, 0, n) if (A[i][y] > EPS) {
            ld val = b[i] / A[i][y];
            if (val < best) { best = val; x = i; }
        }
        if (x < 0) {
            return { numeric_limits<ld>::infinity(), {} };
        }
        pivot(x, y);
    }

    vec<ld> sol(m, 0);
    L(i, 0, n) if (Y[i] < m) sol[Y[i]] = b[i];
    return { z, sol };
}