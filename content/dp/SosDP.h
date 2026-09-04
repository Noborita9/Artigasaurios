/**
 * Author: Juan Manuel Duarte
 * Date: 2026-09-04
 * License: CC0
 * Source: folklore
 * Description: Sum Over Subsets DP. For every mask x, computes the sum of
 * a[s] over all submasks s of x. State dp[x][i] considers only the first i
 * bits, making the recurrence explicit at the cost of an extra dimension.
 * Usage: a must have size $2^n$. Call sos_dp(a, n).
 * Time: O(n 2^n), O(n 2^n) memory
 * Status: untested
 */
#pragma once
vec<ll> sos_dp(const vec<ll>& a, int n) {
    vec<ll> sos(1 << n);
    vec<vec<ll>> dp(1 << n, vec<ll>(n + 1));

    L(x, 0, 1 << n) {
        dp[x][0] = a[x];
        L(i, 0, n) {
            dp[x][i + 1] = dp[x][i];
            if (x & (1 << i))
                dp[x][i + 1] += dp[x ^ (1 << i)][i];
        }
        sos[x] = dp[x][n];
    }
    return sos;
}
