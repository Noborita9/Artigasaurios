/**
 * Author: Joaquin Bonora
 * Date: 2026-09-16
 * License: CC0
 * Source: folklore
 * Description: Node for a persistent segment tree over sums, allocated from a
 * preallocated pool via operator new, so nodes are made with \texttt{new Vertex(...)}
 * as usual. Keep the versions in a \texttt{vector<Vertex*>} of roots.
 * Time: O(\log N) per update/query, each creating O(\log N) nodes.
 * Status: untested
 */
#pragma once
const int N = 2e5;
const int STP_N = N * 30;
struct Vertex {
    static Vertex pool[STP_N];
    static int pCnt;
    void* operator new(size_t) { return &pool[pCnt++]; }
    void operator delete(void*) {} // <- The fix!
    ll x = 0;
    Vertex *l = nullptr, *r = nullptr;
    Vertex() = default;
    Vertex(ll x_): x(x_) {}
    Vertex(Vertex *l_, Vertex *r_): l(l_), r(r_) {
        if (l) x += l->x;
        if (r) x += r->x;
    }
};
Vertex Vertex::pool[STP_N];
int Vertex::pCnt = 0;
