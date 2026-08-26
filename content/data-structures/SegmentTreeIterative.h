/**
 * Author: Joaquin Bonora, Juan Manuel Duarte
 * Date: 2026-08-26
 * License: CC0
 * Source: folklore
 * Description: Iterative (bottom-up) segment tree for range-sum queries and point updates, built over the next power of two.
 * Time: O(N) construction, O(\log N) per update/query.
 * Status: untested
 */
#pragma once
struct STI {
    vec<ll> st; int n, K;
    STI(vec<ll> &a): n(SZ(a)), K(1) {
        while(K<n) K<<=1;
        st.assign(2*K, 0); // 0 default
        L(i,0,n) st[K+i] = a[i];
        for (int i = K - 1; i > 0; i --) st[i] = st[i*2] + st[i*2+1];}
    void upd(int i, ll w) {
        i += K; st[i] += w;
        while(i>>=1)st[i]=st[i*2]+st[i*2+1];}
    ll query(int l, int r) { // [l, r)
        ll res = 0;
        for (l += K, r += K; l < r; l>>=1, r>>=1){
            if (l & 1) res += st[l++];
            if (r & 1) res += st[--r];
        } 
        return res;
    }
};
