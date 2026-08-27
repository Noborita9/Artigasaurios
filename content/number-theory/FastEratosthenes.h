/**
 * Author: Jakob Kogler, chilli, pajenegod
 * Date: 2026-08-26
 * License: CC0
 * Source: KACTL (kth-competitive-programming/kactl)
 * Description: Segmented prime sieve. eratosthenes() returns every prime below
 * LIM and fills the isPrime bitset. Skips even numbers and sieves in
 * cache-sized blocks, which beats both bitset and linear sieves in practice
 * because of its low memory traffic. Raise LIM to suit the problem.
 * Time: O(N \log \log N); LIM = 1e9 takes roughly 1.5s.
 * Status: untested
 */
#pragma once
// --- deps (drop what your solution already defines) ---
#define rep(i, a, b) for (int i = (a); i < (b); ++i)
using vi = vec<int>;
using pii = pair<int, int>;
template<class T> int sz(const T &x) { return (int)x.size(); }
// ------------------------------------------------------
const int LIM = 1e6;
bitset<LIM> isPrime;
vi eratosthenes() {
	const int S = (int)round(sqrt(LIM)), R = LIM / 2;
	vi pr = {2}, sieve(S+1); pr.reserve(int(LIM/log(LIM)*1.1));
	vector<pii> cp;
	for (int i = 3; i <= S; i += 2) if (!sieve[i]) {
		cp.push_back({i, i * i / 2});
		for (int j = i * i; j <= S; j += 2 * i) sieve[j] = 1;
	}
	for (int L = 1; L <= R; L += S) {
		vec<bool> block(S);
		for (auto &[p, idx] : cp)
			for (int i=idx; i < S+L; idx = (i+=p)) block[i-L] = 1;
		rep(i,0,min(S, R - L))
			if (!block[i]) pr.push_back((L + i) * 2 + 1);
	}
	for (int i : pr) isPrime[i] = 1;
	return pr;
}
