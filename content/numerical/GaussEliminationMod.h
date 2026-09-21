/**
 * Author: Juan Manuel Duarte
 * Date: 2026-08-26
 * License: CC0
 * Source: folklore (cp-algorithms, adapted)
 * Description: Gaussian elimination modulo a prime MOD. Returns 0 for no
 * solution, 1 for a unique solution, and INF (2) when free variables remain.
 * Mutates the augmented matrix.
 * Usage: Define: const ll MOD; the ModPow snippet for bPow(a, b, m).
 * Time: O(N M \min(N,M))
 * Status: untested
 */
#pragma once
// --- deps (drop what your solution already defines) --- // exclude-line
const ll MOD = 1e9 + 7; // exclude-line
ll bPow(ll a, ll b, ll m); // exclude-line
// ------------------------------------------------------ // exclude-line
const int INF = 2;

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
