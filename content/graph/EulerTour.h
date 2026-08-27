/**
 * Author: Joaquin Bonora
 * Date: 2026-08-26
 * License: CC0
 * Source: folklore
 * Description: Hierholzer's algorithm for an Eulerian path/circuit in a directed graph, given via add\_edge into global adjacency list g. get\_path(x) returns the path starting at x, assuming one exists. Uncomment the marked lines to switch to the undirected version. TODO (from predecessor notebook): test implementation.
 * Time: O(V + E)
 * Status: untested
 */
#pragma once
// --- deps (drop what your solution already defines) ---
const int N = 2e5 + 5;
// ------------------------------------------------------
// Directed version (uncomment commented code for undirected)
struct edge {
    int y;
//    list<edge>::iterator rev;
    edge(int y):y(y){}
};
list<edge> g[N];
void add_edge(int a, int b){
    g[a].push_front(edge(b));//auto ia=g[a].begin();
//    g[b].push_front(edge(a));auto ib=g[b].begin();
//    ia->rev=ib;ib->rev=ia;
}
vec<int> p;
void go(int x){
    while(g[x].size()){
        int y=g[x].front().y;
        //g[y].erase(g[x].front().rev);
        g[x].pop_front();
        go(y);
    }
    p.push_back(x);
}
vec<int> get_path(int x){ // get a path that begins in x
// check that a path exists from x before calling to get_path!
    p.clear();go(x);reverse(p.begin(),p.end());
    return p;
}