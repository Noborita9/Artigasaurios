/**
 * Author: Joaquin Bonora
 * Date: 2026-08-26
 * License: CC0
 * Source: folklore
 * Description: Tarjan's algorithm for strongly connected components of a directed graph, given by global adjacency list G. After dfs(u) is called on every unvisited vertex, numSCC holds the SCC count and dfs\_low[u] == dfs\_num[u] marks SCC roots.
 * Usage: Define: const int N; vec<int> G[N].
 * Time: O(V + E)
 * Status: untested
 */
#pragma once
// --- deps (drop what your solution already defines) --- // exclude-line
const int N = 2e5 + 5; // exclude-line
vec<int> G[N]; // exclude-line
// ------------------------------------------------------ // exclude-line
vec<int> dfs_num(N, -1), dfs_low(N, -1), in_stack(N);
int dfs_count = 0;
int numSCC = 0;
stack<int> st;
void dfs(int u){
  dfs_low[u]=dfs_num[u]=dfs_count++;
  st.push(u);
  in_stack[u] = 1;
  for(int v: G[u]) {
    if (dfs_num[v] == -1) dfs(v);
    if (in_stack[v]) dfs_low[u] = min(dfs_low[u], dfs_low[v]);
  }
  if (dfs_num[u] == dfs_low[u]){
    numSCC ++;
    while(1){
      int v = st.top(); st.pop();
      in_stack[v] = 0;
      if (u == v) break;
    }
  }
}
