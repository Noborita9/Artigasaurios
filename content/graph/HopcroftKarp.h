/**
 * Author: Joaquin Bonora
 * Date: 2026-08-26
 * License: CC0
 * Source: folklore
 * Description: Bipartite maximum matching via the Hopcroft-Karp algorithm (BFS layering plus DFS augmenting paths), for a bipartite graph with n left vertices and m right vertices. konig() computes a minimum vertex cover into cover[0]/cover[1] after matching() has run.
 * Time: O(E \sqrt V)
 * Status: untested
 */
#pragma once
mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());
struct hopcroft_karp {
	int n, m; // n is Left Partition Size, m is Right Partition Size
	vec<vec<int>> g;
	vec<int> dist, nxt, ma, mb;
	hopcroft_karp(int n_, int m_) : n(n_), m(m_), g(n),
		dist(n), nxt(n), ma(n, -1), mb(m, -1) {}
	void add(int a, int b) { g[a].pb(b); }
	bool dfs(int i) {
		for (int &id = nxt[i]; id < SZ(g[i]); id++) {
			int j = g[i][id];
			if (mb[j] == -1 or (dist[mb[j]] == dist[i]+1 and dfs(mb[j]))) {
				ma[i] = j, mb[j] = i;
				return true;
			}
		}
		return false;
	}
	bool bfs() {
		L(i,0,n) dist[i] = n;
		queue<int> q;
		L(i,0,n) if(ma[i]==-1) {
			dist[i] = 0; q.push(i);
		}
		bool rep = 0;
		while (SZ(q)) {
			int i = q.front(); q.pop();
			for (int j : g[i]) {
				if (mb[j] == -1) rep = 1;
				else if (dist[mb[j]] > dist[i] + 1) {
					dist[mb[j]] = dist[i] + 1;
					q.push(mb[j]);
				}
			}
		}
		return rep;
	}
	int matching() {
		int ret = 0;
		for (auto& i : g) shuffle(ALL(i), rng);
		while (bfs()) {
			L(i,0,n) nxt[i]=0;
			L(i,0,n) if (ma[i]==-1 and dfs(i)) ret++;
		}
		return ret;
	}
	vec<int> cover[2]; // if cover[i][j] = 1 -> node i, j is part of cover
	void konig() {
		cover[0].assign(n,1); // n left size
		cover[1].assign(m,0); // m right size
		auto go = [&](auto&& me, int u) -> void {
			cover[0][u] = false;
			for (auto v : g[u]) if (!cover[1][v]) {
				cover[1][v] = true;
				me(me,mb[v]);
			}
		};
		L(u,0,n) if (ma[u] < 0) go(go,u);
	}
};