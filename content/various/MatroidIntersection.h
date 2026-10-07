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

template<class M1, class M2>
vec<int> matroid_intersect(int n, M1& m1, M2& m2) {
    vec<char> I(n, 0);
    L(i, 0, n) if (m1.check(i) and m2.check(i))
        I[i] = 1, m1.add(i), m2.add(i);
    while (true) {
        vec<int> frm(n, -1), in, out;
        L(i, 0, n) (I[i] ? in : out).pb(i);
        queue<int> q({n});
        auto fwd = [&](int a) {
            vec<int> ans; m1.clear();
            for (int v : in) if (v != a) m1.add(v);
            for (int b : out) if (frm[b] == -1 and m1.check(b))
                ans.pb(b), frm[b] = a;
            return ans;
        };
        auto back = [&](int b) {
            m2.clear();
            L(cas, 0, 2) {
                auto p = [&](int v) {
                    if ((frm[v] == -1) != cas) return -2;
                    if (m2.check(v)) return m2.add(v), -2;
                    if (cas) q.push(v), frm[v] = b;
                    return cas ? v : -1;
                };
                int r = p(b); if (r != -2) return r;
                for (int v : in)
                    if ((r = p(v)) != -2) return r;
            }
            return n;
        };
        bool aug = 0;
        while (!q.empty() and !aug) {
            int a = q.front(), c; q.pop();
            for (int b : fwd(a))
                while ((c = back(b)) >= 0) if (c == n) {
                    while (b != n) I[b] ^= 1, b = frm[b];
                    aug = 1; break;
                }
        }
        if (!aug) break;
    }
    vec<int> ans;
    L(i, 0, n) if (I[i]) ans.pb(i);
    return ans;
}
