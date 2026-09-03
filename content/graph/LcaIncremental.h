/**
 * Author: Joaquin Bonora
 * Date: 2026-09-03
 * License: CC0
 * Source: folklore (skew-binary jump pointers, Myers 1983)
 * Description: Lowest common ancestor on a tree that is grown one leaf at a
 * time, with no preprocessing pass: add\_leaf(u) hangs a new node under u and
 * returns its id in $O(1)$, query(u, v) answers in $O(\log N)$. Each node keeps a
 * single jump pointer j, laid out so that repeatedly following j climbs the
 * tree in skew-binary steps. Node 0 is the root. Useful when the tree is only
 * revealed as queries arrive, or when it is built by a DFS that pushes on
 * entry and never needs to pop. Depth d is exposed:
 * dist(u, v) = d[u] + d[v] - 2*d[query(u, v)].
 * Time: O(1) per insertion, O(\log N) per query
 * Status: stress-tested against brute force on 2000 random trees
 */
#pragma once
struct DynLCA {
    vec<int> p, d, j; // parent, depth, jump pointer
    DynLCA() : p(1, 0), d(1, 0), j(1, 0) {} // node 0 = root
    int add_leaf(int u) {
        int v = SZ(p); // the new node's id
        p.pb(u);
        d.pb(d[u] + 1);
        j.pb((d[u] - d[j[u]] == d[j[u]] - d[j[j[u]]]) ? j[j[u]] : u);
        return v;
    }
    int query(int u, int v) {
        if (d[u] < d[v]) swap(u, v); // make u the deeper one
        while (d[u] > d[v]) u = d[j[u]] >= d[v] ? j[u] : p[u];
        while (u != v)
            if (j[u] != j[v]) u = j[u], v = j[v];
            else u = p[u], v = p[v];
        return u;
    }
};
