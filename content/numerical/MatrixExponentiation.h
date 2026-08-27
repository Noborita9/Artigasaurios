/**
 * Author: Juan Manuel Duarte
 * Date: 2026-08-26
 * License: CC0
 * Source: folklore
 * Description: Binary exponentiation of a square matrix. mult(a, b) updates
 * a in place with a * b (mod MOD). Use to evaluate a linear recurrence: build
 * the companion matrix, call expbinmat, and read off the answer from row 0.
 * Time: O(K^3 \log b) for a K by K matrix.
 * Status: untested
 */
#pragma once
// --- deps (drop what your solution already defines) ---
const ll MOD = 1e9 + 7;
// ------------------------------------------------------
void mult(vec<vec<ll>>& a, vec<vec<ll>>& b) {
    int n = SZ(a);
    vec<vec<ll>> res(n, vec<ll>(n, 0));
    L(i, 0, n) L(k, 0, n) if (a[i][k]) L(j, 0, n)
        res[i][j] = (res[i][j] + a[i][k] * b[k][j]) % MOD;
    a = res;
}
vec<vec<ll>> expbinmat(vec<vec<ll>> mat, ll b) {

    ll n = SZ(mat);

    vec<vec<ll>> resp(n, vec<ll>(n, 0));
    L(i, 0, n) {
        resp[i][i] = 1;
    }
    while (b > 0) {
        if (b % 2 == 1) {
            mult(resp, mat);
        }
        mult(mat, mat);
        b /= 2;

    }
    return resp;
}