/**
 * Author: Joaquin Bonora
 * Date: 2026-08-26
 * License: CC0
 * Source: folklore
 * Description: KMP automaton over a pattern of lowercase letters. Builds the
 * prefix-function array p, then an explicit DFA table so matching can advance
 * one transition per text character without ever backtracking. go(v, c) gives
 * the next automaton state from state v on character c.
 * Time: O(N) to build p, O(26N) to build the DFA table.
 * Status: untested
 */
#pragma once
struct KMP {
    string s; int n; vec<int> p; vec<vec<int>> dfa;
    KMP(string &s_): s(s_), n(SZ(s_)), p(SZ(s_) + 1), dfa(SZ(s_)+1, vec<int>(26)) {
        L(i,1,n) p[i + 1] = nxt(p[i], s[i]); // Calculate phi
    }
    int nxt(int i, char c) {for (;i;i=p[i])if(i<n&&c==s[i])return i+1; return s[0]==c;}
    void build_dfa(){
        dfa[0][s[0]-'a'] = 1; // WARN: check lower_case vs upper
        L(i,1,n+1)L(c,0,26) // If complicated char set use map
            if (i<n&&s[i]=='a'+c)dfa[i][c]=i+1;
            else dfa[i][c]=dfa[p[i]][c]; // fallar en i e ir al c
    }
    int go(int v, char c){return dfa[v][c-'a'];}
};