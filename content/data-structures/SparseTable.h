/**
 * Author: Joaquin Bonora
 * Date: 2026-09-16
 * License: CC0
 * Source: KACTL (kth-competitive-programming/kactl), content/data-structures/RMQ.h
 * Description: Sparse table for idempotent range queries over half-open $[l, r)$
 * (change the op to switch min for max/gcd/etc). Static after construction.
 * Time: O(N \log N) construction, O(1) per query.
 * Status: stress-tested against brute force
 */
#pragma once
template<class T> struct SPT {
    vec<vec<T>> st;
    SPT(const vec<T> &a): st(1, a) {
        for (int pw = 1, k = 1; pw * 2 <= SZ(a); pw *= 2, k ++) {
            st.emplace_back(SZ(a) - pw * 2 + 1);
            L(j,0,SZ(st[k])) st[k][j] = min(st[k-1][j], st[k-1][j + pw]); // change op
        }
    }
    T get(int l, int r) { // [l, r), needs l < r
        int k = __lg(r - l);
        return min(st[k][l], st[k][r - (1 << k)]); // change op
    }
};
