/**
 * Author: Joaquin Bonora
 * Date: 2026-08-26
 * License: CC0
 * Source: folklore
 * Description: Aho-Corasick over lowercase patterns, as a trie with full DFA
 * transitions: ch = trie edges, next = failure-resolved transitions, link =
 * suffix link. add\_string inserts a pattern and records its index at the end
 * node; build\_aho runs the BFS that fills next[] and link[].
 * Time: O(L) to insert all patterns (total length L); O(26 \cdot L) to build
 * the automaton.
 * Status: untested
 */
#pragma once
const int oo = 1e9;
struct node {
    int ch[26], next[26]; // Full DFA Transitions
    int link = 0, minx = oo; // Suffix Link
    vec<int> ixs; // Indices of patterns ending here
    node() { memset(ch, -1, sizeof(ch));}
};
vec<node> t; vec<int> bfs_order; // easy traverse from short to longer words
void init_aho() {t.clear();t.pb(node());bfs_order.clear();}
void add_string(const string &s, const int ix) {
    int v = 0;
    for (char c_raw : s) {
        int c = c_raw - 'a';
        if (t[v].ch[c] == -1) {
            t[v].ch[c] = SZ(t);
            t.pb(node());
        }
        v = t[v].ch[c];
    }
    t[v].ixs.pb(ix);
}
void build_aho() {
    bfs_order.pb(0); // Root is first
	L(c,0,26){
        if (t[0].ch[c] != -1) {
            t[0].next[c] = t[0].ch[c];
            bfs_order.pb(t[0].ch[c]);
        } else t[0].next[c] = 0;
    }
    L(q, 1, SZ(bfs_order)){ // warn: 1 not 0!
        int u = bfs_order[q];
		L(c,0,26){
            if (t[u].ch[c] != -1) {
                int v = t[u].ch[c];
                t[u].next[c] = v;
                t[v].link = t[t[u].link].next[c];
                bfs_order.pb(v);
            } else t[u].next[c] = t[t[u].link].next[c];
        }
    }
}