/**
 * Author: Artigasaurios
 * Date: 2026-08-27
 * License: CC0
 * Source: folklore
 * Description: Binary exponentiation modulo m, and the modular inverse via
 * Fermat's little theorem. mInv requires m to be prime and a not divisible
 * by m; for a composite modulus use the extended Euclid snippet instead.
 * Note the products are plain 64-bit, so this overflows once m exceeds about
 * 3e9 - use \_\_int128 for the multiply above that.
 * Time: O(\log b)
 * Status: untested
 */
#pragma once
ll bPow(ll a, ll b, ll m) { // a^b mod m
    ll res = 1; a %= m;
    while (b > 0) {
        if (b & 1) res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}
ll mInv(ll a, ll m) { return bPow(a, m - 2, m); } // m prime
