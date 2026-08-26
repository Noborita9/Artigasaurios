/**
 * Author: Joaquin Bonora
 * Date: 2026-08-26
 * License: CC0
 * Source: folklore
 * Description: Centroid decomposition of a tree given by global adjacency lists G/g. build(u) recursively finds the centroid of each remaining component, marks it removed, and recurses into the resulting subtrees, returning the root of the decomposition tree.
 * Time: O(N \log N)
 * Status: untested
 */
#pragma once
int sz[N];
bool removed[N];
int getSize(int u, int p){
    sz[u] = 1;
    for(int v: G[u]) if (v != p && !removed[v]){
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
    for (int v: G[c]) if (!removed[v]) { build(v); }
    return c;
}
