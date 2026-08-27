/**
 * Author: Joaquin Bonora
 * Date: 2026-08-26
 * License: CC0
 * Source: folklore
 * Description: Palindromic tree (eertree) over lowercase letters, tracking
 * per-node occurrence count (cnt) and a "heat" weight. init(s) clears only
 * the sz+2 previously-used nodes, then feeds every character through
 * add\_char.
 * Time: intended O(N \cdot \Sigma) (dominated by the next[][] clearing loop
 * in init; add\_char itself is amortized O(1) per character via the link
 * chain).
 * Status: untested
 */
#pragma once
const int MAXN = 100005;
struct PalindromicTree {
    int next[MAXN][26], len[MAXN], link[MAXN]; 
    ll cnt[MAXN], heat[MAXN]; 
    int sz, last;             
    string s;           
    //  you MUST clear only the used part of the arrays:
    void init(const string& s_) {
        s = s_;
        for(int i = 0; i < sz + 2; ++i) {
            for(int j = 0; j < 26; ++j) next[i][j] = 0;
            cnt[i] = heat[i] = 0;
        }
        len[0] = 0; link[0] = 1; heat[0] = 0;
        len[1] = -1; link[1] = 1; heat[1] = 0;
        sz = 2; last = 0;
        L(i, 0, SZ(s)) add_char(i);
    }
    void add_char(int pos) {
        int c = s[pos] - 'a', cur = last;
        while (pos - 1 - len[cur] < 0 || s[pos - 1 - len[cur]] != s[pos])
            cur = link[cur];
        if (next[cur][c]) {
            last = next[cur][c];
            cnt[last]++;
            return;
        }
        int now = sz++;
        len[now] = len[cur] + 2;
        if (cur == 1) heat[now] = (c + 1); // root
        else heat[now] = heat[cur] + 2LL * (c + 1);
        int link_curr = link[cur];
        while (pos - 1 - len[link_curr] < 0 || s[pos - 1 - len[link_curr]] != s[pos])
            link_curr = link[link_curr];
        link[now] = next[link_curr][c];
        next[cur][c] = last = now;
        cnt[last]++;
    }
};