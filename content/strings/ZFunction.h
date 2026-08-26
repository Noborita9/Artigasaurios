/**
 * Author: Joaquin Bonora
 * Date: 2026-08-26
 * License: CC0
 * Source: folklore
 * Description: Z-function of a string. z[i] is the length of the longest
 * common prefix between w and the suffix of w starting at i (z[0] = n).
 * Time: O(N)
 * Status: untested
 */
#pragma once
vec<int> zfun(const string &w){
	int n = SZ(w), l = 0, r = 0; vec<int> z(n);
  	z[0] = n;
	L(i, 1, n) {
		if (i <= r) {z[i] = min(r - i + 1, z[i - l]);}
		while (i + z[i] < n && w[z[i]] == w[i + z[i]]) {++z[i];}
		if (i + z[i] - 1 > r) {l = i, r = i + z[i] - 1;}
	}
	return z;
}