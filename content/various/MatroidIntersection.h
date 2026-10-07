/**
 * Author: tfg, Aeren, pajenegod, chilli, adapted by Joaquin Bonora
 * Date: 2026-10-07
 * License: CC0
 * Source: https://codeforces.com/blog/entry/69287
 * Description: Computes the maximum common independent set of two matroids.
 * m1 and m2 must implement clear(), add(x), and check(x).
 * Pass the matroid with more expensive add/clear operations to M1.
 * Time: O(R^2 N \cdot C + R^3 \cdot A) where C, A are check/add costs
 * Status: tested on SWERC 2011D
 */
#pragma once

template <class M1, class M2> struct MatroidIsect {
    int n;
    vec<char> iset;
    M1 m1; M2 m2;
    MatroidIsect(M1 m1_, M2 m2_, int n_) : n(n_), iset(n_ + 1), m1(m1_), m2(m2_) {}
    vec<int> solve() {
        L(i, 0, n) if (m1.check(i) && m2.check(i))
            iset[i] = 1, m1.add(i), m2.add(i);
        while (augment());
        vec<int> ans;
        L(i, 0, n) if (iset[i]) ans.pb(i);
        return ans;
    }
    bool augment() {
        vec<int> frm(n, -1);
        queue<int> q({n}); // starts at dummy node
        vec<int> I, out_set;
        L(i, 0, n) {
            if (iset[i]) I.pb(i);
            else out_set.pb(i);
        }
        auto fwdE = [&](int a) {
            vec<int> ans;
            m1.clear();
            for (int v : I) if (v != a) m1.add(v);
            for (int b : out_set) if (frm[b] == -1 && m1.check(b))
                ans.pb(b), frm[b] = a;
            return ans;
        };
        auto backE = [&](int b) {
            m2.clear();
            L(cas, 0, 2) {
                auto process = [&](int v) {
                    if ((frm[v] == -1) == cas) {
                        if (!m2.check(v)) {
                            if (cas) { q.push(v); frm[v] = b; return v; }
                            return -1;
                        }
                        m2.add(v);
                    }
                    return -2;
                };
                int res = process(b);
                if (res != -2) return res;
                for (int v : I) {
                    res = process(v);
                    if (res != -2) return res;
                }
            }
            return n;
        };
        while (!q.empty()) {
            int a = q.front(), c; q.pop();
            for (int b : fwdE(a))
                while ((c = backE(b)) >= 0) if (c == n) {
                    while (b != n) iset[b] ^= 1, b = frm[b];
                    return true;
                }
        }
        return false;
    }
};
