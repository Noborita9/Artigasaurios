/**
 * Author: Joaquin Bonora
 * Date: 2026-08-26
 * License: CC0
 * Source: folklore
 * Description: Single-source shortest paths on a graph with non-negative edge weights, using a binary-heap priority queue. Uses global adjacency list G and vertex count N.
 * Time: O((V + E) \log V)
 * Status: untested
 */
#pragma once
vector<pll> G[N];
vec<ll> dijk(ll s) { // Need more data, ask vectors by argument
    vec<ll> dist(N, oo);
    dist[s] = 0;
    priority_queue<pll, vector<pll>, greater<pll>> pq;
    pq.push({0ll, s});
    while(!q.empty()){
        auto [d, u] = pq.top();pq.pop(); 
        if (d != dist[u]) continue;
        for (auto [v, w] : G[u]){
            if (dist[v] > d + w){
                dist[v] = d + w;
                pq.push({dist[v],v});
            }            
        }
    }
    return dist;
}