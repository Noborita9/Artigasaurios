/**
 * Author: Joaquin Bonora
 * Date: 2026-08-26
 * License: CC0
 * Source: folklore
 * Description: 0/1 knapsack. Given item values and weights and a capacity W, finds the maximum total value achievable without exceeding the capacity.
 * Time: O(N \cdot W)
 * Status: untested
 */
#pragma once
int knapsack(vec<int>& values, vec<int>& weights, int W) {
    int n = SZ(values);
    vec<vec<int>> dp(n + 1, vec<int>(W + 1, 0));
    
    for(int i = 1; i <= n; i++) {
        for(int w = 0; w <= W; w++) {
            if(weights[i-1] <= w) {
                dp[i][w] = max(dp[i-1][w], 
                              dp[i-1][w-weights[i-1]] + values[i-1]);
            } else {
                dp[i][w] = dp[i-1][w];
            }
        }
    }
    return dp[n][W];
}
