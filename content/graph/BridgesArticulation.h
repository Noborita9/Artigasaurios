/**
 * Author: Joaquin Bonora
 * Date: 2026-08-26
 * License: CC0
 * Source: folklore
 * Description: Finds bridges and articulation points of an undirected graph, given by global adjacency list g, via DFS low-link values. Bridges are printed as they are found; ap[u] is set for articulation points. Set root to the DFS root before calling dfs(root).
 * Time: O(V + E)
 * Status: untested
 */
#pragma once
// --- deps (drop what your solution already defines) ---
const int N = 2e5 + 5;
vec<int> g[N];
// ------------------------------------------------------
vec<int> dfs_low(N, -1), dfs_num(N, -1), ap(N, 0); // ap for Articulation Points
int dfs_count = 0;
int root = -1; // For AP
void dfs(int u, int p = -1){
    dfs_low[u]=dfs_num[u]=dfs_count++;
    int child = 0;
    for (int v: g[u]){
        if (v == p) continue;
        if (dfs_num[v] == -1){
            child ++;
            dfs(v, u);
            dfs_low[u] = min(dfs_low[u], dfs_low[v]);
            if (dfs_low[v] > dfs_num[u]){
              cout << "Bridge " << u << " -> " << v << "\n";
            } 
            if (dfs_low[v] >= dfs_num[u]) {
                ap[u] = 1;
            }
        } else dfs_low[u] = min(dfs_low[u], dfs_num[v]);
    }
    if (u == root){
        ap[u] = child > 1;
    }
}