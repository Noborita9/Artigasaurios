/**
 * Author: Joaquin Bonora
 * Date: 2026-08-26
 * License: CC0
 * Source: folklore
 * Description: Double polynomial rolling hash (two moduli, base $b=5\cdot 10^8$)
 * with decreasing exponents, packed into one 64-bit value. Precomputes prefix
 * hashes and base powers once, then answers any substring hash in O(1).
 * Time: O(N) construction, O(1) per query.
 * Status: untested
 */
#pragma once
static constexpr ll ms[] = {1'000'000'007, 1'000'000'403};
static constexpr ll b = 500'000'000;
struct StrHash { // Hash polinomial con exponentes decrecientes.
	vec<ll> hs[2], bs[2];
	StrHash(string const& s) {
		int n = SZ(s);
		L(k, 0, 2) {
			hs[k].resize(n+1), bs[k].resize(n+1, 1);
			L(i, 0, n) {
				hs[k][i+1] = (hs[k][i] * b + s[i]) % ms[k];
				bs[k][i+1] =  bs[k][i] * b         % ms[k];
			}
		}
	}
	ll get(int idx, int len) const { // Hashes en `s[idx, idx+len)`.
		ll h[2];
		L(k, 0, 2) {
			h[k] = hs[k][idx+len] - hs[k][idx] * bs[k][len] % ms[k];
			if (h[k] < 0) h[k] += ms[k];
		}
		return (h[0] << 32) | h[1];
	}
};