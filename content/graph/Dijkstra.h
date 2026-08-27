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
// --- deps (drop what your solution already defines) ---
const int N = 2e5 + 5;
const ll oo = 1e18;
// ------------------------------------------------------
vec<pair<ll, ll>> G[N];
vec<ll> dijk(ll s) { // Need more data, ask vectors by argument
    vec<ll> dist(N, oo);
    dist[s] = 0;
    priority_queue<pair<ll, ll>, vec<pair<ll, ll>>, greater<pair<ll, ll>>> pq;
    pq.push({0ll, s});
    while(!pq.empty()){
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