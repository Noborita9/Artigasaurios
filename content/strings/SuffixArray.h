/**
 * Author: Joaquin Bonora
 * Date: 2026-09-21
 * License: Unknown
 * Source: KACTL (Chinese IOI team paper, 2009)
 * Description: Suffix array by prefix doubling with counting sort, plus
 * Kasai's LCP in the same constructor. A nul sentinel is appended, so sa
 * has size |s|+1 and sa[0] = |s|. lcp[i] is the longest common prefix of
 * sa[i-1] and sa[i], with lcp[0] = 0. The input must be nul-free ASCII.
 * Time: O(N \log N)
 * Status: stress-tested against a naive suffix sort
 */
#pragma once
struct SuffixArray {
	vec<int> sa, lcp;
	SuffixArray(string s, int lim=256) { // lim = alphabet size
		s.pb(0); int n = SZ(s), k = 0, a, b; // sentinel sorts first
		vec<int> x(ALL(s)), y(n), ws(max(n, lim)); // x: rank of each suffix
		sa = lcp = y, iota(ALL(sa), 0);
		for (int j = 0, p = 0; p < n; j = max(1, j*2), lim = p) {
			p = j, iota(ALL(y), n-j); // y: suffixes by rank of 2nd half,
			L(i,0,n) if (sa[i] >= j) y[p++] = sa[i] - j; // shorter ones first
			fill(ALL(ws), 0); // stable counting sort of y by 1st half
			L(i,0,n) ws[x[i]]++;
			L(i,1,lim) ws[i] += ws[i-1];
			for (int i = n; i--;) sa[--ws[x[y[i]]]] = y[i];
			swap(x, y), p = 1, x[sa[0]] = 0; // y holds the old ranks now
			L(i,1,n) a = sa[i-1], b = sa[i], x[b] = // equal halves share
				(y[a] == y[b] and y[a+j] == y[b+j]) ? p-1 : p++; // a rank
		} // loop ends when p == n, i.e. every suffix has its own rank
		for (int i = 0, j; i < n-1; lcp[x[i++]] = k) // Kasai: x is the rank
			for (k and k--, j = sa[x[i]-1]; s[i+k] == s[j+k]; k++); // of i
	}
};