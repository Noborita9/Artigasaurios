/**
 * Author: Stjepan Glavina
 * Date: 2026-08-26
 * License: Unlicense
 * Source: KACTL, from github.com/stjepang/snippets
 * Description: Index of the lexicographically smallest rotation of s. Rotate
 * into place with rotate(v.begin(), v.begin()+minRotation(v), v.end()).
 * Time: O(N)
 * Status: untested
 */
#pragma once
int minRotation(string s) {
	int a=0, N=SZ(s); s += s;
	L(b,0,N) L(k,0,N) {
		if (a+k == b || s[a+k] < s[b+k]) {b += max(0, k-1); break;}
		if (s[a+k] > s[b+k]) { a = b; break; }
	}
	return a;
}
