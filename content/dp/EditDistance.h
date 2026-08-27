/**
 * Author: Joaquin Bonora
 * Date: 2026-08-26
 * License: CC0
 * Source: folklore
 * Description: Levenshtein edit distance between two strings: minimum number of single-character insertions, deletions and substitutions to turn s1 into s2.
 * Time: O(N \cdot M)
 * Status: untested
 */
#pragma once
int editDistance(string& s1, string& s2) {
    int n = s1.length(), m = s2.length();
    vec<vec<int>> dp(n + 1, vec<int>(m + 1));
    for(int i = 0; i <= n; i++) dp[i][0] = i;
    for(int j = 0; j <= m; j++) dp[0][j] = j;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if(s1[i-1] == s2[j-1]) {
                dp[i][j] = dp[i-1][j-1];
            } else {
                dp[i][j] = 1 + min({dp[i-1][j],    // deletion
                                  dp[i][j-1],      // insertion
                                  dp[i-1][j-1]});  // replacement
            }
        }
    }
    return dp[n][m];
}
