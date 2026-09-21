/**
 * Author: Joaquin Bonora
 * Date: 2026-08-26
 * License: CC0
 * Source: folklore
 * Description: Minimum spanning arborescence rooted at r (Chu-Liu/Edmonds via
 * lazy skew heaps and a rollback DSU). Returns {-1, {}} if r cannot reach every
 * node, else the total weight and each node's parent. Needs UnionFind.h.
 * Time: O(E \log V)
 * Status: stress-tested against brute force
 */
#pragma once
#include "../data-structures/UnionFind.h"
struct Edge { int a, b; ll w; };
struct Node { /// lazy skew heap node
	Edge key;
	Node *l, *r;
	ll delta;
	void prop() {
		key.w += delta;
		if (l) l->delta += delta;
		if (r) r->delta += delta;
		delta = 0;
	}
	Edge top() { prop(); return key; }
};
Node *merge(Node *a, Node *b) {
	if (!a || !b) return a ?: b;
	a->prop(), b->prop();
	if (a->key.w > b->key.w) swap(a, b);
	swap(a->l, (a->r = merge(b, a->r)));
	return a;
}
void pop(Node*& a) { a->prop(); a = merge(a->l, a->r); }
pair<ll, vec<int>> dmst(int n, int r, vec<Edge>& g) {
	DSURollback uf(n);
	vec<Node*> heap(n);
	for (Edge e : g) heap[e.b] = merge(heap[e.b], new Node{e});
	ll res = 0;
	vec<int> seen(n, -1), path(n), par(n);
	seen[r] = r;
	vec<Edge> Q(n), in(n, {-1,-1}), comp;
	deque<tuple<int, int, vec<Edge>>> cycs;
	L(s,0,n) {
		int u = s, qi = 0, w;
		while (seen[u] < 0) {
			if (!heap[u]) return {-1,{}};
			Edge e = heap[u]->top();
			heap[u]->delta -= e.w, pop(heap[u]);
			Q[qi] = e, path[qi++] = u, seen[u] = s;
			res += e.w, u = uf.find(e.a);
			if (seen[u] == s) { /// found cycle, contract
				Node* cyc = 0;
				int end = qi, time = uf.time();
				do cyc = merge(cyc, heap[w = path[--qi]]);
				while (uf.join(u, w));
				u = uf.find(u), heap[u] = cyc, seen[u] = -1;
				cycs.push_front({u, time, {&Q[qi], &Q[end]}});
			}
		}
		L(i,0,qi) in[uf.find(Q[i].b)] = Q[i];
	}
	for (auto& [u,t,comp] : cycs) { // restore sol (optional)
		uf.rollback(t);
		Edge inEdge = in[u];
		for (auto& e : comp) in[uf.find(e.b)] = e;
		in[uf.find(inEdge.b)] = inEdge;
	}
	L(i,0,n) par[i] = in[i].a;
	return {res, par};
}