/**
 * Author: Joaquin Bonora
 * Date: 2026-08-26
 * License: CC0
 * Source: folklore
 * Description: Heavy-light decomposition over global adjacency list g, mapping the tree onto positions pos[] queryable with an external segment tree st (query must support a max range query, referenced as st.query). Call dfs(root) then decompose(root, root) to build; query(a, b) answers a path max query.
 * Time: O(N) preprocessing, O(\log^2 N) per query
 * Status: untested
 */
#pragma once
int ans[N], par[N], depth[N], head[N], pos[N];
vec<int> heavy(N, - 1);
int t = 0;
vec<int> g[N];
int dfs(int u) {
    int size = 1;
    int max_size = 0;
    for (int v: g[u]) if (v != par[u]) {
        par[v] = u;
        depth[v] = depth[u] + 1;
        int cur_size = dfs(v);
        size += cur_size;
        if (cur_size > max_size) {
            max_size = cur_size;
            heavy[u] = v; 
        }
    }
    return size;
}
void decompose(int u, int h){
    head[u] = h;
    pos[u] = t ++;
    if (heavy[u] != -1){ decompose(heavy[u], h); }
    for (int v: g[u]) if (v != par[u] && v != heavy[u]) {
        decompose(v, v);
    }
}
int query(int a, int b) {
    int resp = -1;
    for (; head[a] != head[b]; b = par[head[b]]){ // Subi todo el heavy path y a su padre // Next
        if (depth[head[a]] > depth[head[b]]) swap(a, b);
        resp = max(resp, st.query(pos[head[b]], pos[b])); // pos[head[b]] < pos[b]
    }
    if (depth[a] > depth[b]) swap(a, b); // Una vez misma path(head) entonces es una query [a,b]
    resp = max(resp, st.query(pos[a], pos[b]));
    return resp;
}
dfs(root);
decompose(root, root);