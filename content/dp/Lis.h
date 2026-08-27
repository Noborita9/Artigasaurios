/**
 * Author: Joaquin Bonora
 * Date: 2026-08-26
 * License: CC0
 * Source: folklore
 * Description: Length of the longest strictly increasing subsequence, computed via patience-sorting (binary search over the tails array d). Uses a local sentinel oo (larger than any array value).
 * Time: O(N \log N)
 * Status: untested
 */
#pragma once
const int oo = 1e9;
int lis(vec<int> &a) {
    int n = SZ(a);
    vec<int> d(n+1, oo);
    d[0] = -oo;
    L(i,0,n){
        int l = upper_bound(d.begin(), d.end(), a[i]) - d.begin();
        if (d[l-1] < a[i] && a[i] < d[l]) d[l] = a[i];
    }
    int ans = 0;
    for (int l = 0; l <= n; l++) if (d[l] < oo) ans = l;
    return ans;
}