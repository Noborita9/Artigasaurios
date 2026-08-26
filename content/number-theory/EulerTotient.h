/**
 * Author: Joaquin Bonora
 * Date: 2026-08-26
 * License: CC0
 * Source: folklore
 * Description: Computes Euler's totient function $\varphi(i)$ for every
 * $i \in [0,n]$ with a sieve: each prime $i$ found (still untouched, i.e.
 * $\varphi(i)=i$) propagates the factor $(i-1)/i$ to all of its multiples.
 * Time: O(N \log\log N)
 * Status: untested
 */
#pragma once
vector<ll> compute_totients(ll n) {
    vector<ll> phi(n + 1);
    for (ll i = 0; i <= n; i++) phi[i] = i;
    for (ll i = 2; i <= n; i++) {
        if (phi[i]!=i) continue;
        for (ll j = i; j <= n; j += i)
            phi[j] = phi[j] * (i - 1) / i;
    }
    return phi;
}
