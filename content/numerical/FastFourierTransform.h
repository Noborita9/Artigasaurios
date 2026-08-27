/**
 * Author: Joaquin Bonora, Juan Manuel Duarte
 * Date: 2026-08-26
 * License: CC0
 * Source: folklore (KACTL-style packed FFT)
 * Description: Fast Fourier Transform over complex doubles, plus multiply()
 * for convolving two integer sequences. Packs both operands into one complex
 * transform (real and imaginary parts) so only two FFTs are needed instead of
 * three. Result is rounded to the nearest integer, so precision limits the
 * usable magnitude of the inputs.
 * Time: O(N \log N)
 * Status: untested
 */
#pragma once
typedef long long ll;
typedef complex<double> C;
typedef vec<double> vd;
typedef vec<ll> vll;
const double PI = acos(-1);

void fft(vec<C>& a) {
    int n = SZ(a), L = 31 - __builtin_clz(n);
    static vec<C> R(2, 1);
    static vec<C> rt(2, 1);
    for (static int k = 2; k < n; k *= 2) {
        R.resize(n); rt.resize(n);
        auto x = polar(1.0, PI / k);
        L(i, k, (2 * k))
            rt[i] = R[i] = i & 1 ? R[i / 2] * x : R[i / 2];
    }
    vec<int> rev(n);
    L(i, 0, n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
    L(i, 0, n) if (i < rev[i]) swap(a[i], a[rev[i]]);
    for (int k = 1; k < n; k *= 2)
        for (int i = 0; i < n; i += 2 * k) L(j, 0, k) {
            auto x = (double*)&rt[j + k], y = (double*)&a[i + j + k];
            C z(x[0] * y[0] - x[1] * y[1], x[0] * y[1] + x[1] * y[0]);
            a[i + j + k] = a[i + j] - z;
            a[i + j] += z;
        }
}

vll multiply(const vll& a, const vll& b) {
    if (a.empty() || b.empty()) return {};
    vd fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int L = 32 - __builtin_clz(SZ(fa) + SZ(fb) - 1), n = 1 << L;
    vec<C> in(n), out(n);

    L(i, 0, SZ(a)) in[i] = C(fa[i], 0);
    L(i, 0, SZ(b)) in[i].imag(fb[i]);

    fft(in);
    for (C& x : in) x *= x;
    L(i, 0, n) out[i] = in[-i & (n - 1)] - conj(in[i]);  // Corregido aqui
    fft(out);

    vll res(SZ(a) + SZ(b) - 1);
    L(i, 0, SZ(res)) {
        res[i] = llround(imag(out[i]) / (4 * n));
    }
    return res;
}
