/**
 * Author: Juan Manuel Duarte
 * Date: 2026-08-26
 * License: CC0
 * Source: folklore (cp-algorithms, adapted)
 * Description: Gaussian elimination over an augmented matrix of doubles,
 * with partial pivoting. Returns 0 for no solution, 1 for a unique solution,
 * and INF (2) when free variables remain. The input matrix is copied.
 * Time: O(N M \min(N,M))
 * Status: untested
 */
#pragma once
// --- deps (drop what your solution already defines) --- // exclude-line
const double EPS = 1e-9;
const int INF = 2; // it doesn't actually have to be infinity or a big number

int gauss(vec < vec<double> > a, vec<double>& ans) {
    int n = SZ(a);
    int m = SZ(a[0]) - 1;
    vec<int> where(m, -1);
    for (int col = 0, row = 0; col < m && row < n; ++col) {
        int sel = row;
        L(i, row, n)
            if (abs(a[i][col]) > abs(a[sel][col]))
                sel = i;
        if (abs(a[sel][col]) < EPS)
            continue;
        L(i, col, m + 1)
            swap(a[sel][i], a[row][i]);
        where[col] = row;

        L(i, 0, n)
            if (i != row) {
                double c = a[i][col] / a[row][col];
                L(j, col, m + 1)
                    a[i][j] -= a[row][j] * c;
            }
        ++row;
    }
    ans.assign(m, 0);
    L(i, 0, m)
        if (where[i] != -1)
            ans[i] = a[where[i]][m] / a[where[i]][i];
    L(i, 0, n) {
        double sum = 0;
        L(j, 0, m)
            sum += ans[j] * a[i][j];
        if (abs(sum - a[i][m]) > EPS)
            return 0;
    }
    L(i, 0, m)
        if (where[i] == -1)
            return INF;
    return 1;
}
