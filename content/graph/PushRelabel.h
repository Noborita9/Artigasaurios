/**
 * Author: Joaquin Bonora
 * Date: 2026-09-20
 * License: CC0
 * Source: KACTL
 * Description: Maximum flow by highest-label push-relabel with the gap
 * heuristic. Faster than Dinic on dense graphs and on large capacities;
 * use Dinic for unit capacities and bipartite matching. addEdge takes an
 * optional reverse capacity, so an undirected edge is one call.
 * Time: O(V^2 \sqrt E)
 * Status: stress-tested against Dinic
 */
#pragma once
struct PushRelabel {
	struct Edge { int dest, back; ll f, c; }; // back: index of the twin edge
	vec<vec<Edge>> g;
	vec<ll> ec; // ec[v] = excess: flow into v not yet pushed out
	vec<Edge*> cur; // next edge to try out of v, so a scan is not restarted
	vec<vec<int>> hs; vec<int> H; // hs[h] = active vertices at height h
	PushRelabel(int n) : g(n), ec(n), cur(n), hs(2*n), H(n) {}
	void addEdge(int s, int t, ll cap, ll rcap=0) { // rcap>0: undirected
		if (s == t) return;
		g[s].pb({t, SZ(g[t]), 0, cap});
		g[t].pb({s, SZ(g[s])-1, 0, rcap});
	}
	void addFlow(Edge& e, ll f) {
		Edge &back = g[e.dest][e.back];
		if (!ec[e.dest] and f) hs[H[e.dest]].pb(e.dest); // just became active
		e.f += f; e.c -= f; ec[e.dest] += f;
		back.f -= f; back.c += f; ec[back.dest] -= f;
	}
	ll calc(int s, int t) {
		int v = SZ(g); H[s] = v; ec[t] = 1; // ec[t]=1 keeps t out of hs
		vec<int> co(2*v); co[0] = v-1; // co[h] = how many vertices at height h
		L(i, 0, v) cur[i] = g[i].data();
		for (Edge& e : g[s]) addFlow(e, e.c); // saturate every edge out of s
		for (int hi = 0;;) { // hi = highest height with an active vertex
			while (hs[hi].empty()) if (!hi--) return -ec[s]; // done: ec[s] <= 0
			int u = hs[hi].back(); hs[hi].pop_back();
			while (ec[u] > 0) // discharge u
				if (cur[u] == g[u].data() + SZ(g[u])) { // scanned every edge
					H[u] = 1e9; // relabel u to just above its lowest neighbour
					for (Edge& e : g[u]) if (e.c and H[u] > H[e.dest]+1)
						H[u] = H[e.dest]+1, cur[u] = &e;
					if (++co[H[u]], !--co[hi] and hi < v) // gap at height hi:
						L(i, 0, v) if (hi < H[i] and H[i] < v) // nothing above
							--co[H[i]], H[i] = v + 1; // it can reach t again
					hi = H[u];
				} else if (cur[u]->c and H[u] == H[cur[u]->dest]+1)
					addFlow(*cur[u], min(ec[u], cur[u]->c)); // push downhill
				else ++cur[u];
		}
	}
	bool leftOfMinCut(int a) { return H[a] >= SZ(g); } // after calc()
};
