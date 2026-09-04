/**
 * Author: Juan Manuel Duarte
 * Date: 2026-09-04
 * License: CC0
 * Source: folklore
 * Description: Memory-optimized Sum Over Subsets DP. For every mask x,
 * computes the sum of a[s] over all submasks s of x. Since layer i + 1 only
 * depends on layer i, the same array can be updated in place.
 * Usage: a must have size $2^n$. Call sos\_dp\_optimized(a, n).
 * Time: O(n 2^n), O(2^n) memory
 * Status: untested
 */
#pragma once
vec<ll> sos_dp_optimized(const vec<ll>& a, int n) {
    vec<ll> sos = a;
    L(i, 0, n) {
        L(x, 0, 1 << n) {
            if (x & (1 << i))
                sos[x] += sos[x ^ (1 << i)];
        }
    }
    return sos;
}
