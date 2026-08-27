/**
 * Author: Juan Manuel Duarte
 * Date: 2026-08-26
 * License: CC0
 * Source: folklore
 * Description: Divide and conquer DP optimization. Computes dp[k][i] = min over j <= i of dp[k-1][j] + cost(j,i), requiring that the optimal split point opt[k][i] is monotone in i. Fill cost[j][i] and call dnc\_dp(n, k) (1-indexed).
 * Time: O(N \log N) per layer, O(K N \log N) total
 * Status: untested
 */
#pragma once
// --- deps (drop what your solution already defines) ---
const int N = 5005, K = 505;
const ll oo = 1e18;
ll dp[N][K], cost[N][N];
// ------------------------------------------------------
// dp[k][i] = min(dp[k-1][j] + cost(j,i)), con j <= i
// requiere monotonicidad: opt[k][i] <= opt[k][i+1]
// uso: definir cost[j][i] y llamar dnc_dp(n, k)
// base 1
void dnc_dp(int n, int k) {
    auto calc = [&](int j, int l, int r, int optL, int optR, auto&& self) -> void {
        if (l > r) return;
        int m = (l + r) >> 1;
        ll best = oo;
        int opt = optL;
        int hi = min(m, optR);
        L(i, optL, hi + 1) {
            ll v = dp[i - 1][j - 1] + cost[i][m];
            if (v < best) {
                best = v;
                opt = i;
            }
        }
        dp[m][j] = best;
        self(j, l, m - 1, optL, opt, self);
        self(j, m + 1, r, opt, optR, self);
    };
    L(j, 1, k + 1) {
        calc(j, 1, n, 1, n, calc);
    }
}