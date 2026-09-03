/**
 * Author: Joaquin Bonora
 * Date: 2026-08-29
 * License: CC0
 * Source: folklore
 * Description: The minimal tree containing a subset S and closed under LCA,
 * so fewer than 2|S| nodes. build\_virt fills virt[] with downward (child,
 * distance) edges and returns the root, or -1 if S is empty; it clears
 * virt[] as it goes, so back-to-back queries need no reset. Needs
 * LcaConstant.h, built first.
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
