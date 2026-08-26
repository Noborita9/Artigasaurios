/**
 * Author: Joaquin Bonora
 * Date: 2026-08-26
 * License: CC0
 * Source: folklore
 * Description: Sparse table for idempotent range-min queries (change the op to switch to range-max/gcd/etc). Static after construction.
 * Time: O(N \log N) construction, O(1) per query.
 * Status: untested
 */
#pragma once
struct SPT {
    vec<vec<int>> st;
    SPT(vec<int> &a) {
        int n = SZ(a), K = 0; while((1<<K)<=n) K ++;
        st = vec<vec<int>>(K, vec<int>(n));
        L(i,0,n) st[0][i] = a[i];
        L(i,1,K) for (int j = 0; j + (1 << i) <= n; j ++) 
            st[i][j] = min(st[i-1][j], st[i - 1][j + (1 << (i - 1))]); // change op
    }
    int get(int l, int r) {
        int bit = __lg(r - l + 1);
        return min(st[bit][l], st[bit][r - (1<<bit) + 1]); // change op
    }
};