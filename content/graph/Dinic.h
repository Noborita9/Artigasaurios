/**
 * Author: Joaquin Bonora
 * Date: 2026-08-26
 * License: CC0
 * Source: folklore
 * Description: Maximum flow via Dinic's algorithm (BFS level graph plus blocking-flow DFS), with an optional capacity-scaling mode (set scaling = true, and lim to the top scaling bound). get\_cut recovers a minimum s-t cut after max\_flow has run.
 * Time: O(V^2 E) in general; O(E \sqrt V) on unit-capacity graphs
 * Status: untested
 */
#pragma once
const int oo = (int)1e9;
struct Dinic {
	bool scaling = false; // com scaling -> O(nm log(MAXCAP)),
	int lim;                    // com constante alta
	struct edge {
		int to, cap, rev, flow;
		bool res;
		edge(int to_, int cap_, int rev_, bool res_)
			: to(to_), cap(cap_), rev(rev_), flow(0), res(res_) {}
	};
	vec<vec<edge>> g;
	vec<int> lev, beg;
	ll F;
	Dinic(int n) : g(n), F(0) {}
	void add(int a, int b, int c) {
		g[a].eb(b, c, g[b].size(), false);
		g[b].eb(a, 0, g[a].size()-1, true);
	}
	bool bfs(int s, int t) {
		lev = vec<int>(g.size(), -1); lev[s] = 0;
		beg = vec<int>(g.size(), 0);
		queue<int> q; q.push(s);
		while (q.size()) {
			int u = q.front(); q.pop();
			for (auto& i : g[u]) {
				if (lev[i.to] != -1 or (i.flow == i.cap)) continue;
				if (scaling and i.cap - i.flow < lim) continue;
				lev[i.to] = lev[u] + 1;
				q.push(i.to);
			}
		}
		return lev[t] != -1;
	}
	int dfs(int v, int s, int f = oo) {
		if (!f or v == s) return f;
		for (int& i = beg[v]; i < g[v].size(); i++) {
			auto& e = g[v][i];
			if (lev[e.to] != lev[v] + 1) continue;
			int foi = dfs(e.to, s, min(f, e.cap - e.flow));
			if (!foi) continue;
			e.flow += foi, g[e.to][e.rev].flow -= foi;
			return foi;
		}
		return 0;
	}
	ll max_flow(int s, int t) {
		for (lim = scaling ? (1<<30) : 1; lim; lim /= 2)
			while (bfs(s, t)) while (int ff = dfs(s, t)) F += ff;
		return F;
	}
};
vec<pair<int, int>> get_cut(Dinic& g, int s, int t) {
	g.max_flow(s, t);
	vec<pair<int, int>> cut;
	vec<int> vis(g.g.size(), 0), st = {s};
	vis[s] = 1;
	while (st.size()) {
		int u = st.back(); st.pop_back();
		for (auto e : g.g[u]) if (!vis[e.to] and e.flow < e.cap)
			vis[e.to] = 1, st.pb(e.to);
	}
	for (int i = 0; i < g.g.size(); i++) for (auto e : g.g[i])
		if (vis[i] and !vis[e.to] and !e.res) cut.eb(i, e.to);
	return cut;
}
