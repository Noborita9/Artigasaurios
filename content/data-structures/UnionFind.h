/**
 * Author: Joaquin Bonora
 * Date: 2026-08-26
 * License: CC0
 * Source: folklore
 * Description: Disjoint-set union, union by size. DSU adds path compression;
 * DSURollback drops it so join() can be undone -- time() marks a point and
 * rollback(t) returns to it. Negated e[root] is the component size.
 * Time: O(\alpha(N)) amortized per DSU op, O(\log N) per DSURollback op.
 * Status: stress-tested against brute force
 */
#pragma once
struct DSU {
    vec<int> e;
    DSU(int n): e(n, -1) {}
    int find(int x){return e[x] < 0 ? x : e[x] = find(e[x]);}
    void join(int a, int b){
        a = find(a); b = find(b);
        if (a==b)return;
        if (e[a]>e[b])swap(a,b);
        e[a]+=e[b]; e[b] = a;
    }
};

struct DSURollback { // union by size only, no path compression
	struct H {int a, b;};
	vec<int> e; vec<H> st;
	DSURollback(int n) : e(n, -1) {}
	int size(int x) { return -e[find(x)]; }
	int find(int x) { return e[x] < 0 ? x : find(e[x]); }
	int time() { return SZ(st); }
	void rollback(int t) {
		for (int i = time(); i --> t;)
			e[st[i].a] = st[i].b;
		st.resize(t);
	}
	bool join(int a, int b) { // false if already together
		a = find(a), b = find(b);
		if (a == b) return false;
		if (e[a] > e[b]) swap(a, b);
		st.pb({a, e[a]}); st.pb({b, e[b]});
		e[a] += e[b]; e[b] = a;
		return true;
	}
};