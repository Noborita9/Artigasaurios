/**
 * Author: Joaquin Bonora
 * Date: 2026-08-26
 * License: CC0
 * Source: folklore
 * Description: Bipartite maximum matching by repeated DFS augmenting paths, for a bipartite graph with n left vertices and m right vertices. recover(K) computes minimum vertex cover from the matching (via Konig's theorem), returning the cover vertices split by side.
 * Time: O(VE)
 * Status: untested
 */
#pragma once
mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());
struct kuhn {
	int n, m;
	vec<vec<int>> g;
	vec<int> vis, ma, mb;
	kuhn(int n_, int m_) : n(n_), m(m_), g(n),
		vis(n+m), ma(n, -1), mb(m, -1) {}
	void add(int a, int b) { g[a].pb(b); }
	bool dfs(int i) {
		vis[i] = 1;
		for (int j : g[i]) if (!vis[n+j]) {
			vis[n+j] = 1;
			if (mb[j] == -1 or dfs(mb[j])) {
				ma[i] = j, mb[j] = i;
				return true;
			}
		}
		return false;
	}
	int matching() {
		int ret = 0, aum = 1;
		for (auto& i : g) shuffle(ALL(i), rng);
		while (aum) {
			aum = 0;
            L(j,0,m) vis[n+j] = 0;
            L(i,0,n) if (ma[i]==-1 and dfs(i)) ret++,aum=1;
		}
		return ret;
	}
};
pair<vec<int>, vec<int>> recover(kuhn& K) { // min cover
	K.matching(); 
	int n = K.n, m = K.m;
	L(i, 0, (n + m)) K.vis[i] = 0;
	L(i, 0, n) if (K.ma[i] == -1) K.dfs(i);
	vec<int> ca, cb; // flip vis check to max indep set
	L(i, 0, n) if (!K.vis[i]) ca.pb(i);
	L(i, 0, m) if (K.vis[n+i]) cb.pb(i);
	return {ca, cb};
}