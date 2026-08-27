/**
 * Author: Johan Sannemo
 * Date: 2026-08-26
 * License: CC0
 * Source: KACTL (kth-competitive-programming/kactl)
 * Description: Indices of the smallest set of intervals I covering the target
 * interval G. Intervals are [inclusive, exclusive); to allow [inclusive,
 * inclusive] add || R.empty() to the marked loop condition. Returns an empty
 * set when G cannot be covered, and also when G is empty.
 * Time: O(N \log N)
 * Status: untested
 */
#pragma once
template<class T>
vec<int> cover(pair<T, T> G, vec<pair<T, T>> I) {
	vec<int> S(SZ(I)), R;
	iota(ALL(S), 0);
	sort(ALL(S), [&](int a, int b) { return I[a] < I[b]; });
	T cur = G.first;
	int at = 0;
	while (cur < G.second) { // (A) add || R.empty() for closed intervals
		pair<T, int> mx = make_pair(cur, -1);
		while (at < SZ(I) && I[S[at]].first <= cur) {
			mx = max(mx, make_pair(I[S[at]].second, S[at]));
			at++;
		}
		if (mx.second == -1) return {};
		cur = mx.first;
		R.pb(mx.second);
	}
	return R;
}
