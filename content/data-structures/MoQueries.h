/**
 * Author: Joaquin Bonora
 * Date: 2026-08-26
 * License: CC0
 * Source: folklore
 * Description: Mo's algorithm: offline square-root decomposition over queries. Sort queries by (block of l, r) with alternating direction per block to reduce cursor movement; hilbertorder() is an alternative sort key for the more efficient Hilbert-curve variant. add()/rem() and the state/answer extraction are meant to be filled in per problem.
 * Time: O((N+Q)\sqrt N) amortized.
 * Status: untested
 */
#pragma once
const int BLOCK_SIZE = 450; using U64 = uint64_t;
struct query {int l, r, id;U64 order;
bool operator<(const query& o) const {
    if (l / BLOCK_SIZE != o.l / BLOCK_SIZE) return l < o.l;
    return (l / BLOCK_SIZE & 1) ? r < o.r : r > o.r;
} // If short implementation needed
};
U64 hilbertorder(U64 x, U64 y) { // If Efficient impl needed
    const U64 logn = 21;
    const U64 maxn = (1ull << logn) - 1;
    U64 res = 0;
    for (U64 s = 1ull << (logn - 1); s; s >>= 1) {
        bool rx = x & s, ry = y & s;
        res = (res << 2) | (rx ? ry ? 2 : 1 : ry ? 3 : 0);
        if (!rx) {
            if (ry) x ^= maxn, y ^= maxn;
            swap(x, y);
        }
    }
    return res;
} // sort by this order
void mo(vec<query> &qs, vec<ll> &ans) { // fill add/rem/answer per problem
    auto add = [&](int ix) { /* Add A[ix] to state*/};
    auto rem = [&](int ix) { /* Remove A[ix] from state*/};
    int c_l = 0, c_r = -1; // Cursors [0,-1] so r add 0 on first q
    for(const auto &qr: qs){
        while(c_l > qr.l) add(--c_l);
        while(c_r < qr.r) add(++c_r);
        while(c_l < qr.l) rem(c_l++);
        while (c_r > qr.r) rem(c_r--);
        ans[qr.id] = 0; // State.Answer()
    }
}
