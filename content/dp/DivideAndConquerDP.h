/**
 * Author: Juan Manuel Duarte
 * Date: 2026-08-26
 * License: CC0
 * Source: folklore
 * Description: Divide and conquer DP optimization for partitioning a prefix
 * into nonempty contiguous groups. The recurrence, base cases and required
 * monotonicity are given below. opt[g][i] is the smallest optimal start of
 * the last group. Initializes dp and returns the answer in dp[n][k].
 * Usage: Define: const int N, K; const ll oo; ll dp[N][K], cost[N][N].
 * Fill cost[l][r], then call dnc_dp(n, k), with 0 <= n < N, 0 <= k < K.
 * All finite transition sums must fit in ll and be strictly less than oo.
 * Time: O(N \log N) per layer, O(K N \log N) total
 * Status: tested
 */
#pragma once
// --- deps (drop what your solution already defines) --- // exclude-line
const int N = 5005, K = 505; // exclude-line
const ll oo = 1e18; // exclude-line
ll dp[N][K], cost[N][N]; // exclude-line
// ------------------------------------------------------ // exclude-line
// dp[i][g] = costo minimo de dividir los primeros i elementos en g grupos
//
// transicion:
// dp[i][g] = min(dp[p - 1][g - 1] + cost[p][i])
//             para g <= p <= i
//
// cost[l][r] = costo de tomar el intervalo [l, r] como un grupo
//
// requiere monotonicidad:
// opt[g][i] <= opt[g][i + 1]
//
// caso base:
// dp[0][0] = 0
// dp[i][0] = INF para i > 0
// dp[0][g] = INF para g > 0
//
// base 1 para los elementos; INF se representa con oo
void dnc_dp(int n, int k) {
    L(i, 0, n + 1)
        L(j, 0, k + 1)
            dp[i][j] = oo;

    dp[0][0] = 0;

    auto calc = [&](int j, int l, int r, int optL, int optR, auto&& self) -> void {
        if (l > r) return;

        int m = (l + r) >> 1;
        ll best = oo;
        int opt = optL;

        int hi = min(m, optR);

        L(i, optL, hi + 1) {
            if (dp[i - 1][j - 1] == oo) continue;
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
        calc(j, j, n, j, n, calc);
    }
}
