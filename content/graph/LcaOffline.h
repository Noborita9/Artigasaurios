/**
 * Author: Joaquin Bonora
 * Date: 2026-09-03
 * License: CC0
 * Source: folklore (Tarjan)
 * Description: Tarjan's offline LCA: one DFS answers every query at once, so
 * all pairs must be known up front. Add each query to both endpoints, then
 * solve(root) fills ans[] by query index. No jump table and no sparse table
 * to build -- nothing to precompute beyond the DFS itself.
 * Usage: Define: const int N; vec<int> g[N], the tree.
 * q[u].eb(v, i) and q[v].eb(u, i) for query i; LCAOffline(n).solve(root).
 * Time: O((N + Q) \alpha(N))
 * Status: stress-tested against brute force
 */
#pragma once
#include "../data-structures/UnionFind.h"
// --- deps (drop what your solution already defines) --- // exclude-line
const int N = 2e5 + 5; // exclude-line
vec<int> g[N]; // exclude-line
// ------------------------------------------------------ // exclude-line
vec<pair<int, int>> q[N]; // q[u] = {other end, query id}
int ans[N];
struct LCAOffline {
    DSU ds; vec<int> anc; vec<bool> vis;
    LCAOffline(int n): ds(n), anc(n), vis(n) {}
    void dfs(int u, int p) {
        anc[u] = u; // u starts as its own set
        for (int v: g[u]) if (v != p) {
            dfs(v, u);
            ds.join(u, v);
            anc[ds.find(u)] = u; // u tops the merged set
        }
        vis[u] = 1;
        for (auto& [v, ix]: q[u])
            if (vis[v]) ans[ix] = anc[ds.find(v)];
    }
    void solve(int root) { dfs(root, -1); }
};
