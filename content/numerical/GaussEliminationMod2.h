/**
 * Author: Juan Manuel Duarte
 * Date: 2026-08-26
 * License: CC0
 * Source: folklore (cp-algorithms, adapted)
 * Description: Gaussian elimination over GF(2), using bitsets as augmented
 * matrix rows. Returns 0 for no solution, 1 for a unique solution, and INF
 * (2) when free variables remain. The input matrix is copied.
 * Usage: Define: const int BS, at least the number of variables plus one.
 * Time: O(N M \min(N,M) / W), where W is the machine word size
 * Status: untested
 */
#pragma once
// --- deps (drop what your solution already defines) --- // exclude-line
const int BS = 1005; // exclude-line
// ------------------------------------------------------ // exclude-line
int gauss_mod2(vec<bitset<BS>> a, int n, int m, bitset<BS>& ans) {
    const int INF = 2;
    vec<int> where(m, -1);
    int row = 0;
    for (int col = 0; col < m && row < n; ++col) {
        int sel = -1;
        L(i, row, n) {
            if (a[i][col]) { sel = (int)i; break; }
        }
        if (sel == -1) continue;
        swap(a[sel], a[row]);
        where[col] = row;
        L(i, 0, n) {
            if ((int)i != row && a[i][col]) a[i] ^= a[row];
        }
        ++row;
    }
    ans.reset();
    int free_col = -1;
    L(j, 0, m) {
        if (where[j] == -1) { free_col = (int)j; break; }
    }
    if (free_col != -1) ans[free_col] = 1;
    L(col, 0, m) {
        if (where[col] == -1) continue;
        int r = where[col];
        bool v = a[r][m];
        L(j, 0, m) {
            if (where[j] == -1 && a[r][j] && ans[j]) v ^= 1;
        }
        ans[col] = v;
    }
    L(i, 0, n) {
        bool lhs = 0;
        L(j, 0, m) {
            if (ans[j] && a[i][j]) lhs ^= 1;
        }
        if (lhs != a[i][m]) return 0;
    }
    L(i, 0, m) if (where[i] == -1) return INF;
    return 1;
}
