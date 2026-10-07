/**
 * Author: Joaquin Bonora
 * Date: 2026-10-04
 * License: CC0
 * Source: folklore
 * Description: Computes the maximum common independent set of two matroids.
 * m1 and m2 must implement clear(), add(i), can_add(i), and can_swap(out, in).
 * Time: O(r^2 N + r N^2 T_{swap}) where r is rank and T_{swap} is time to check swap
 * Status: untested
 */
#pragma once

template<class M1, class M2>
vec<int> matroid_intersect(int N, M1& m1, M2& m2) {
    vec<bool> I(N, 0);
    while (true) {
        m1.clear(); m2.clear();
        vec<int> in, out;
        L(i, 0, N) {
            if (I[i]) m1.add(i), m2.add(i), in.pb(i);
            else out.pb(i);
        }
        vec<int> p(N, -1);
        vec<bool> vis(N, 0), snk(N, 0);
        queue<int> q;
        int tar = -1;
        for (int i : out) {
            bool c1 = m1.can_add(i), c2 = m2.can_add(i);
            if (c1 && c2) { tar = i; break; }
            if (c1) q.push(i), vis[i] = 1;
            if (c2) snk[i] = 1;
        }
        if (tar != -1) { I[tar] = 1; continue; }
        while (!q.empty()) {
            int u = q.front(); q.pop();
            if (snk[u]) { tar = u; break; }
            if (!I[u]) { 
                for (int v : in) if (!vis[v] && m2.can_swap(u, v))
                    vis[v] = 1, p[v] = u, q.push(v);
            } else { 
                for (int v : out) if (!vis[v] && m1.can_swap(v, u))
                    vis[v] = 1, p[v] = u, q.push(v);
            }
        }
        if (tar == -1) break;
        for (int c = tar; c != -1; c = p[c]) I[c] = !I[c];
    }
    vec<int> ans;
    L(i, 0, N) if (I[i]) ans.pb(i);
    return ans;
}
/* Example: Colorful Matroid (At most one edge of each color)
struct ColorMatroid {
    int n; vec<int> c, ec;
    ColorMatroid(int n_, vec<int> ec_): n(n_), c(n), ec(ec_) {}
    void clear() { c.assign(n, 0); }
    void add(int i) { c[ec[i]] = 1; }
    bool can_add(int i) { return !c[ec[i]]; }
    bool can_swap(int add, int rem) { return ec[add] == ec[rem]; }
};
*/
