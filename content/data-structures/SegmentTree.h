/**
 * Author: Joaquin Bonora
 * Date: 2026-08-26
 * License: CC0
 * Source: folklore
 * Description: Recursive segment tree with lazy propagation, storing running max and supporting range-add updates (0 as the default/identity value).
 * Time: O(N) construction, O(\log N) per update/query.
 * Status: untested
 */
#pragma once
struct ST { // max st with 0s as defualt
    int n;vec<ll> st, lz;
    ST(int n_): n(n_), st(4*n+5), lz(4*n+5) {}
    void push(int v, int L, int R){
        if (lz[v]) {
            if (R - L > 1) {
                st[2 * v] += lz[v];
                st[2 * v + 1] += lz[v];
                lz[2 * v] += lz[v];
                lz[2 * v + 1] += lz[v];
            }
            lz[v] = 0;
        }
    }
    void upd(int v, int L, int R, int ql, int qr, ll w) {
        if (qr <= L || ql >= R) return;
        push(v, L, R);
        if (ql <= L && R <= qr){
            lz[v] = w;
            st[v] += w;
            return;
        } 
        int m = (L + R) / 2;
        upd(2 * v, L, m, ql, qr, w);
        upd(2 * v + 1, m, R, ql, qr, w);
        st[v] = max(st[2*v], st[2*v+1]);
    }
    ll query(int v, int L, int R, int ql, int qr) {
        if (ql >= R || qr <= L) return 0ll;
        push(v, L, R);
        if(ql <= L && R <= qr) return st[v];
        int m = (L + R) / 2;
        return max(query(2 * v, L, m, ql, qr), query(2 * v + 1, m, R, ql, qr));
    }
    void upd(int l, int r, ll w){return upd(1,0,n,l,r,w);}
    ll query(int l, int r){return query(1,0,n,l,r);}
};
