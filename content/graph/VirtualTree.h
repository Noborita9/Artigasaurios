/**
 * Author: Joaquin Bonora
 * Date: 2026-08-29
 * License: CC0
 * Source: folklore
 * Description: Virtual (auxiliary) tree over a subset S of vertices: the
 * minimal tree containing S that is closed under LCA, so it has fewer than
 * 2|S| nodes. build\_virt fills virt[] with (child, distance) pairs and
 * returns the root; only downward edges are added, so a DFS from the root
 * visits each node once. Nodes keep their original ids. Clears virt[] for
 * every node it touches, so consecutive queries do not need a global reset.
 * Returns -1 for an empty subset. Requires LcaConstant.h, built first.
 * Usage: Define: const int N. LCA lca(n); add edges; lca.build(root).
 * Time: O(K \log K) for |S| = K, dominated by the two sorts.
 * Status: stress-tested against brute force on 3000 random trees
 */
#pragma once
#include "LcaConstant.h"
// --- deps (drop what your solution already defines) --- // exclude-line
const int N = 2e5 + 5; // exclude-line
// ------------------------------------------------------ // exclude-line
vec<pair<int, int>> virt[N]; // virt[u] = {child, dist(u, child)}
int build_virt(LCA& lca, vec<int> v) {
    if (v.empty()) return -1; // v.size()-1 would wrap below
    auto cmp = [&](int i, int j) { return lca.in[i] < lca.in[j]; };
    sort(ALL(v), cmp);
    for (int i = SZ(v) - 1; i; i--) v.pb(lca.get(v[i], v[i - 1]));
    sort(ALL(v), cmp); // the pushed LCAs are now part of v
    v.erase(unique(ALL(v)), v.end());
    for (int u : v) virt[u].clear();
    L(i, 1, SZ(v)) {
        int p = lca.get(v[i - 1], v[i]); // p is an ancestor of v[i]
        virt[p].eb(v[i], lca.depth[v[i]] - lca.depth[p]);
    }
    return v[0];
}
