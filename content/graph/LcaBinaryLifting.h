/**
 * Author: Joaquin Bonora
 * Date: 2026-08-26
 * License: CC0
 * Source: folklore
 * Description: Lowest common ancestor via binary lifting over global adjacency list g. K must be set so that (1 << K) > n before calling dfs(root, -1) to build the jump table; then LCA(u, v) answers queries. Distance between u and v is depth[u] + depth[v] - 2*depth[lca].
 * Time: O(N \log N) preprocessing, O(\log N) per query
 * Status: untested
 */
#pragma once
// --- deps (drop what your solution already defines) ---
const int N = 2e5 + 5;
const int K = 18; // K should be set so that (1 << K) > n
// ------------------------------------------------------
vec<int> g[N];
int jump[K][N]; // Inicializar en -1
int depth[N]; // dist(u,v)=depth[u]+depth[v]-2*depth[lca]
void dfs(int u, int p){
    for (int v: g[u]) if (v != p) {
        jump[0][v] = u;
        L(i, 1, K) {
            if (jump[i - 1][v] != -1) {
                jump[i][v] = jump[i - 1][jump[i - 1][v]];
            }
        }    
        depth[v] = depth[u] + 1;
        dfs(v, u);
    }
}
int LCA(int u, int v){
    if (depth[u] < depth[v]) swap(u, v); // Make u the deepest
    for (int i= K-1; i>=0; i--){ // make them same depth
        if (jump[i][u] != -1 && depth[jump[i][u]] >= depth[v]){ 
            u = jump[i][u];
        }
    }
    if (u == v) return u; // u is parent of v
    for (int i= K-1; i>=0; i--){
        if (jump[i][u] != jump[i][v] && jump[i][u] != -1 && jump[i][v] != -1){
            u = jump[i][u];
            v = jump[i][v];
        }
    }
    return jump[0][u];
}