/**
 * Author: Joaquin Bonora
 * Date: 2026-08-26
 * License: CC0
 * Source: folklore
 * Description: Lowest common ancestor with O(1) queries, via an Euler tour reduced to a sparse-table range-minimum-by-depth query. Call add\_edge to build the tree, then build(root), then get(u, v).
 * Time: O(N \log N) preprocessing, O(1) per query
 * Status: untested
 */
#pragma once
struct LCA {
    vec<int> depth, in, euler;
    vec<vec<int>> g, st;
    int K, n;
    inline int Min(int i, int j) {return depth[i] <= depth[j] ? i : j;}
    void dfs(int u, int p) {
        in[u] = SZ(euler);
        euler.pb(u);
        for (int v: g[u]) if (v != p){
            depth[v] = depth[u] + 1;
            dfs(v, u);
            euler.pb(u);
        }
    }
    LCA(int n_): depth(n_), in(n_), g(vec<vec<int>>(n_)), K(0), n(n_) { euler.reserve(2 * n); }
    void add_edge(int u, int v) {g[u].pb(v);}
    void build(int root){
        dfs(root, -1);
        int ln = SZ(euler);
        while((1<<K)<=ln)K++;
        st = vec<vec<int>> (K, vec<int>(ln));
        L(i,0,ln) st[0][i] = euler[i];
        for (int i = 1; (1 << i) <= ln; i ++) {
            for (int j = 0; j + (1<<i) <= ln; j ++) {
                st[i][j] = Min(st[i-1][j], st[i-1][j + (1<<(i-1))]);
            }
        }
    }
    int get(int u, int v) {
        int su = in[u];
        int sv = in[v];
        if (sv < su) swap(sv, su);
        int bit = __lg(sv - su + 1);
        return Min(st[bit][su], st[bit][sv - (1<<bit) + 1]);   
    }
};