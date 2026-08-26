/**
 * Author: Joaquin Bonora
 * Date: 2026-08-26
 * License: CC0
 * Source: folklore
 * Description: Map-based trie. insert(word) walks/creates nodes and marks the
 * final node as a word end (eee).
 * Time: O(L \log \Sigma) per insertion (each of the L characters does a
 * std::map lookup/insert over the alphabet Sigma).
 * Status: untested
 */
#pragma once
struct Trie {
    map<char, int> ch;
    bool eee;
    Trie(): eee(0) {} 
};
vec<Trie> t;
void initTrie(){t.clear();t.pb(Trie());}
void insert(string &word) {
    int v = 0;
    for(char c : word) {
        if(!t[v].ch[c]) {
            t[v].ch[c] = SZ(t);
            t.pb(Trie());
        }
        v = t[v].ch[c];
    }
    t[v].eee = 1;
}