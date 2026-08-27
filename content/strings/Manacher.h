/**
 * Author: Joaquin Bonora
 * Date: 2026-08-26
 * License: CC0
 * Source: folklore
 * Description: Manacher's algorithm. Finds, for every center in a
 * character-interleaved transform of s (length 2n+1), the radius of the
 * longest palindrome centered there. odd(i)/even(i) recover the longest
 * palindrome centered on s[i], resp. between s[i-1] and s[i], as {start, length}.
 * Time: O(N)
 * Status: untested
 */
#pragma once
struct Manacher {
	vec<int> p;
	Manacher(string const& s) {
		int n = SZ(s), m = 2*n+1, l = -1, r = 1;
		vec<char> t(m); L(i, 0, n) t[2*i+1] = s[i];
		p.resize(m); L(i, 1, m) {
			if (i < r) p[i] = min(r-i, p[l+r-i]);
			while (p[i] <= i && i < m-p[i] && t[i-p[i]] == t[i+p[i]]) ++p[i];
			if (i+p[i] > r) l = i-p[i], r = i+p[i];
		}
	} // Retorna palindromos de la forma {comienzo, largo}.
	pair<int,int> at(int i) const {int k = p[i]-1; return pair{i/2-k/2, k};}
	pair<int,int> odd(int i) const {return at(2*i+1);} // Mayor centrado en s[i].
	pair<int,int> even(int i) const {return at(2*i);} // Mayor centrado en s[i-1,i].
};