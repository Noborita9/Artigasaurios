/**
 * Author: Joaquin Bonora, Juan Manuel Duarte
 * Date: 2026-08-26
 * License: CC0
 * Source: folklore
 * Description: Builds the sorted list of every divisor of $n$ from its prime
 * factorization $f$ (e.g. as produced by PollardRho's fact), by repeatedly
 * extending the divisor list with each prime's powers $p^0,\dots,p^e$.
 * Time: O(D) to build and O(D \log D) to sort, where D is the number of
 * divisors of n.
 * Status: untested
 */
#pragma once
vector<ll> getDivisors(const map<ll, int>& f) {
    vector<ll> divisors = { 1 };
    for (auto [p, e] : f) {
        vector<ll> next;
        ll pe = 1;
        for (int i = 0; i <= e; i++) {
            for (ll d : divisors)next.pb(d * pe);
            pe *= p;
        }
        divisors.swap(next);
    }
    sort(ALL(divisors));
    return divisors;
}
