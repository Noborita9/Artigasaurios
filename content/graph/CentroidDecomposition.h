/**
 * Author: Joaquin Bonora
 * Date: 2026-08-26
 * License: CC0
 * Source: folklore
 * Description: Centroid decomposition of a tree given by the global adjacency list g, which the caller builds. build(u) recursively finds the centroid of each remaining component, marks it removed, and recurses into the resulting subtrees, returning the root of the decomposition.
 * Usage: Define: const int N; vec<int> g[N], the tree.
 * Time: O(N \log N)
 * Status: untested
 */
#pragma once
// --- deps (drop what your solution already defines) --- // exclude-line
const int N = 2e5 + 5; // exclude-line
vec<int> g[N]; // exclude-line
// ------------------------------------------------------ // exclude-line
int sz[N];
bool removed[N];
int getSize(int u, int p){
    sz[u] = 1;
    for(int v: g[u]) if (v != p && !removed[v]){
        sz[u] += getSize(v, u);
    }
    return sz[u];
}
int centroid(int u, int p, int tz){
    for (int v: g[u])
        if (v != p && !removed[v] && sz[v] * 2 > tz) return centroid(v, u, tz);
    return u;
}
int build(int u){
    int c = centroid(u, -1, getSize(u, -1));
    removed[c] = 1;
    for (int v: g[c]) if (!removed[v]) { build(v); }
    return c;
}
