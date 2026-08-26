/**
 * Author: Joaquin Bonora
 * Date: 2026-08-26
 * License: CC0
 * Source: folklore
 * Description: Two ways to get the Mobius function $\mu$: compute\_mobius
 * sieves $\mu(i)$ for every $i\in[0,n]$ by flipping the sign at each prime
 * and zeroing multiples of $p^2$; mobius computes $\mu(x)$ for a single $x$
 * by trial division, returning 0 as soon as a squared factor is found.
 * Time: compute\_mobius: O(N \log\log N). mobius: O(\sqrt{x}) per query.
 * Status: untested
 */
#pragma once
vector<ll> compute_mobius(ll n) {
    vector<ll> mu(n + 1, 1);
    vector<bool> is_prime(n + 1, true);
    for (ll i = 2; i <= n; i++) {
        if (is_prime[i]) { // i es un primo
            for (ll j = i; j <= n; j += i) {
                mu[j] *= -1; // Multiplicamos por -1 para cada primo
                is_prime[j] = false;
            }
            for (ll j = i * i; j <= n; j += i * i) {
                mu[j] = 0; // Si tiene un cuadrado de un primo, se pone en 0
            }
        }
    }
    return mu;
}
ll mobius(ll x) {
    ll count = 0;
    for (ll i = 2; i * i <= x; i++) {
        if (x % (i * i) == 0)
            return 0;
        if (x % i == 0) {
            count++;
            x /= i;
        }
    }
    if (x > 1) count++;
    return (count % 2 == 0) ? 1 : -1;
}
