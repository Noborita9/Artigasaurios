/**
 * Author: Joaquin Bonora
 * Date: 2026-08-26
 * License: CC0
 * Source: folklore
 * Description: Josephus problem: position of the survivor when every k-th
 * person is eliminated from a circle of n, returned 0-indexed. Three
 * variants: an iterative recurrence, the same recurrence recursively, and a
 * closed form for the k=2 case using the largest power of two below n.
 * Time: O(N) iterative and recursive; O(\log N) for the k=2 closed form.
 * Status: untested
 */
#pragma once
ll josephus_iterative(ll n, ll k) {
    ll result = 0; 
    for (ll i = 2; i <= n; ++i)
        result = (result + k) % i;
    return result;
}
ll josephus_recursive(ll n, ll k) {
    if (n == 1) return 0;
    return (josephus_recursive(n - 1, k) + k) % n;
}
ll josephus_power_of_2(ll n) {
    ll power = 1;
    while (power <= n)power <<= 1;
    power >>= 1;
    return 2 * (n - power);
}