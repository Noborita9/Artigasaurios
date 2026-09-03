/**
 * Author: Joaquin Bonora
 * Date: 2026-09-03
 * License: CC0
 * Source: folklore
 * Description: A number mod MOD, for hashing. Products go through
 * \_\_int128, so MOD can be up to 62 bits -- not 63, as + and - work before
 * reducing. The default $2^{61}-1$ is wide enough to need no second modulus.
 * The constructor normalizes negatives, raw skips that when already in range.
 * HashInterval hashes any substring in O(1), hashString the whole string.
 * Usage: Define: const ll MOD, prime.
 * Time: O(1) per H operation, O(N) to build HashInterval
 * Status: stress-tested against brute force
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
