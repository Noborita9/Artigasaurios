/**
 * Author: Juan Manuel Duarte
 * Date: 2026-08-26
 * License: CC0
 * Source: folklore
 * Description: Knuth's optimization for interval DP of the form dp[i][j] = min over i<=k<j of dp[i][k] + dp[k+1][j] + cost(i,j), applicable when opt[i][j-1] <= opt[i][j] <= opt[i+1][j] (e.g. cost satisfies the quadrangle inequality). Requires dp[i][i]=0 and opt[i][i]=i initialized beforehand and cost(i,j) defined; relies on external globals dp, opt, n, oo and macro L.
 * Time: O(N^2)
 * Status: untested
 */
#pragma once
// dp[i][j] = min(dp[i][k] + dp[k+1][j] + cost(i,j))
// requiere: opt[i][j-1] <= opt[i][j] <= opt[i+1][j]
// uso: inicializar dp[i][i]=0 y opt[i][i]=i, definir cost(i,j)
vec<vec<ll>> dp(n + 1, vec<ll>(n + 1, oo));
vec<vec<ll>> opt(n + 1, vec<ll>(n + 1, oo));
L(s, 1, n) {
    L(i, 0, n - s) {
        ll j = i + s;
        ll l = opt[i][j - 1];
        ll r = opt[i + 1][j];
        l = max(l, i);
        r = min(r, j - 1);
        if (l > r) swap(l, r);
        L(k, l, r+1) {
            ll val = dp[i][k] + dp[k + 1][j] + cost(i, j);
            if (val < dp[i][j]) {
                dp[i][j] = val;
                opt[i][j] = k;
            }
        }
    }
}
