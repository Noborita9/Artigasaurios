/**
 * Author: Joaquin Bonora
 * Date: 2026-09-03
 * License: CC0
 * Source: folklore
 * Description: A number mod MOD, for hashing. Products go through
 * \_\_int128, so MOD may be up to 62 bits -- unlike plain 64-bit modular code,
 * which overflows past about 3e9. (62, not 63: + and - work before reducing,
 * so 2*MOD must still fit in an ll.) The default is the Mersenne prime
 * $2^{61}-1$, big enough that a single hash needs no second modulus. raw
 * skips the reduction for a value already in range, which is what makes the
 * branches worth having; the public constructor normalizes anything, negatives
 * included. The value is the field h; compare hashes with a.h == b.h.
 * HashInterval precomputes prefix hashes and base powers of a string, then
 * hashInterval(a, b) is the polynomial hash of s[a, b) in O(1). Equal
 * substrings always hash equal; unequal ones collide with probability about
 * len/MOD per comparison, so one modulus this size needs no second one.
 * hashString is the whole-string hash on its own, with no vectors built,
 * for when there is nothing to query -- comparing two strings, or keying a
 * map by one. It agrees with hashInterval(0, n) on the same string.
 * Usage: Define: const ll MOD, prime. HashInterval hi(s); hi.hashInterval(a, b).
 * Time: O(1) per H operation, O(N) to build HashInterval
 * Status: stress-tested against \_\_int128 arithmetic and brute-force hashes
 */
#pragma once
// --- deps (drop what your solution already defines) --- // exclude-line
const ll MOD = (1LL << 61) - 1; // exclude-line
// ------------------------------------------------------ // exclude-line
struct H {
    ll h;
    H(): h(0) {}
    H(ll x): h(((x % MOD) + MOD) % MOD) {}
    static H raw(ll x) { H r; r.h = x; return r; }
    H operator+(const H& rhs) const {
        ll nh = h + rhs.h;
        return raw(nh >= MOD ? nh - MOD : nh);
    }
    H operator-(const H& rhs) const {
        ll nh = h - rhs.h;
        return raw(nh < 0 ? nh + MOD : nh);
    }
    H operator*(const H& rhs) const {
        return raw((ll)(__int128(h) * rhs.h % MOD));
    }
    H& operator+=(const H& rhs) { return *this = *this + rhs; }
    H& operator-=(const H& rhs) { return *this = *this - rhs; }
    H& operator*=(const H& rhs) { return *this = *this * rhs; }
};
const H C = (ll)1e11 + 3; // base; any large random value
struct HashInterval {
    vec<H> ha, pw;
    HashInterval(const string& str) : ha(SZ(str)+1), pw(ha) {
        pw[0] = 1;
        L(i, 0, SZ(str))
            ha[i+1] = ha[i] * C + str[i],
            pw[i+1] = pw[i] * C;
    }
    H hashInterval(int a, int b) const { // hash [a, b)
        return ha[b] - ha[a] * pw[b - a];
    }
};
H hashString(const string& s) { // whole-string hash, no vecs
    H h{}; for (char c : s) h = h*C + c; return h;
}
