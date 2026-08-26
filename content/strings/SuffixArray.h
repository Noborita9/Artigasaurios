/**
 * Author: Joaquin Bonora
 * Date: 2026-08-26
 * License: CC0
 * Source: folklore
 * Description: Suffix array construction by prefix doubling with counting
 * sort (csort) instead of comparison sort, plus Kasai's algorithm (compute\_lcp)
 * for the LCP array between lexicographically adjacent suffixes. compute\_sa
 * appends an implicit sentinel (n = |s|+1).
 * Time: O(N \log N) for compute\_sa (O(\log N) doubling rounds, O(N) counting
 * sort each); O(N) for compute\_lcp.
 * Status: untested
 */
#pragma once
#define RB(x) ((x) < n ? r[x] : 0)
void csort(vec<int>& sa, vec<int>& r, int k) {
	int n = SZ(sa);
	vec<int> f(max(255, n)), t(n);
	L(i,0, n) ++f[RB(i+k)];
	int sum = 0;
	L(i,0, max(255, n)) f[i] = (sum += f[i]) - f[i];
	L(i,0, n) t[f[RB(sa[i]+k)]++] = sa[i];
	sa = t;
}
vec<int> compute_sa(string& s){ // O(n*log2(n))
	int n = SZ(s) + 1, rank;
	vec<int> sa(n), r(n), t(n);
	iota(ALL(sa), 0);
	L(i,0, n) r[i] = s[i];
	for (int k = 1; k < n; k *= 2) {
		csort(sa, r, k), csort(sa, r, 0);
		t[sa[0]] = rank = 0;
		L(i, 1, n) {
			if(r[sa[i]] != r[sa[i-1]] || RB(sa[i]+k) != RB(sa[i-1]+k)) ++rank;
			t[sa[i]] = rank;
		}
		r = t;
		if (r[sa[n-1]] == n-1) break;
	}
	return sa; // sa[i] = i-th suffix of s in lexicographical order
}
vec<int> compute_lcp(string& s, vec<int>& sa){
	int n = SZ(s) + 1, K = 0;
	vec<int> lcp(n), plcp(n), phi(n);
	phi[sa[0]] = -1;
	L(i, 1, n) phi[sa[i]] = sa[i-1];
	L(i,0,n) {
		if (phi[i] < 0) { plcp[i] = 0; continue; }
		while(s[i+K] == s[phi[i]+K]) ++K;
		plcp[i] = K;
		K = max(K - 1, 0);
	}
	L(i,0, n) lcp[i] = plcp[sa[i]];
	return lcp; // lcp[i] = longest common prefix between sa[i-1] and sa[i]
}