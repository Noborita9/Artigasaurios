/**
 * Author: Juan Manuel Duarte
 * Date: 2026-08-26
 * License: CC0
 * Source: folklore (cp-algorithms, adapted)
 * Description: Gaussian elimination over an augmented matrix in three
 * flavours: gauss() over doubles with partial pivoting, gauss\_mod2() over
 * GF(2) with bitset rows, and a modular variant. Each returns 0 for no
 * solution, 1 for one, INF (2) when free variables remain. gauss() copies
 * its matrix; the other two mutate the caller's.
 * Usage: Define: const int BS; const ll MOD; the ModPow snippet for bPow(a, b, m).
 * Time: O(N M \min(N,M)) for the dense variants; the GF(2) variant divides
 * the inner work by the machine word size.
 * Status: untested
 */
#pragma once
// --- deps (drop what your solution already defines) --- // exclude-line
const int BS = 1005; // exclude-line
const ll MOD = 1e9 + 7; // exclude-line
ll bPow(ll a, ll b, ll m); // exclude-line
// ------------------------------------------------------ // exclude-line
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

int gauss_mod2(vec< bitset<BS> > a, int n, int m, bitset<BS>& ans) {
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

int gauss_mod(vec<vec<ll>>& a, vec<ll>& ans) {
    int n = SZ(a);
    int m = SZ(a[0]) - 1;
    L(i, 0, n) L(j, 0, m + 1) {
        a[i][j] %= MOD;
        if (a[i][j] < 0) a[i][j] += MOD;
    }
    vec<int> where(m, -1);
    for (int col = 0, row = 0; col < m && row < n; ++col) {
        int sel = -1;
        L(i, row, n) {
            if (a[i][col] != 0) { sel = (int)i; break; }
        }
        if (sel == -1) continue;
        swap(a[sel], a[row]);
        where[col] = row;
        ll inv_pivot = bPow(a[row][col], MOD - 2, MOD);
        L(i, 0, n) if ((int)i != row && a[i][col] != 0) {
            ll c = (a[i][col] * inv_pivot) % MOD;
            L(j, col, m + 1) {
                ll sub = (a[row][j] * c) % MOD;
                a[i][j] = a[i][j] - sub;
                a[i][j] %= MOD;
                if (a[i][j] < 0) a[i][j] += MOD;
            }
        }
        ++row;
    }
    ans.assign(m, 0);
    L(i, 0, m) if (where[i] != -1) {
        int r = where[i];
        ll inv_diag = bPow(a[r][i], MOD - 2, MOD);
        ans[i] = (a[r][m] * inv_diag) % MOD;
    }
    L(i, 0, n) {
        ll sum = 0;
        L(j, 0, m) {
            sum = (sum + (ans[j] * a[i][j]) % MOD) % MOD;
        }
        if (sum != a[i][m]) return 0;
    }
    L(i, 0, m) if (where[i] == -1) return INF;
    return 1;
}
