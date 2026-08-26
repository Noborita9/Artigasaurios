/**
 * Author: Joaquin Bonora
 * Date: 2026-08-26
 * License: CC0
 * Source: folklore
 * Description: Disjoint-set union with path compression (find) and union by
 * size (join). Tracks component sizes in sz[].
 * Time: O(\alpha(N)) amortized per operation.
 * Status: untested
 */
#pragma once
struct DSU {
    vec<int> par, sz; int n;
    DSU(int n = 1): par(n), sz(n, 1), n(n) { iota(ALL(par), 0); }
    int find(int a){return a == par[a] ? a : par[a] = find(par[a]);}
    void join(int a, int b){
        a=find(a);b=find(b);
        if (a == b) return;
        if (sz[b] > sz[a]) swap(a,b);
        par[b] = a; sz[a] += sz[b];
    }
};
