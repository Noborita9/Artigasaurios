/**
 * Author: Joaquin Bonora
 * Date: 2026-08-26
 * License: CC0
 * Source: folklore
 * Description: Persistent segment tree (functional/version-based) over sums, using a preallocated node pool. build() creates an initial all-zero version; update() creates a new version differing at one position sharing untouched subtrees with the previous version; query() answers a range-sum on the difference between two versions.
 * Time: O(N) build, O(\log N) per update/query.
 * Status: untested
 */
#pragma once
// --- deps (drop what your solution already defines) ---
#define MD(l, r) (((l) + (r)) >> 1)
// ------------------------------------------------------
struct Vertex{Vertex * l, *r;int sum;};
const int MVertex = 6000000; // ~= N * logN * 2
Vertex pool[MVertex]; // the idea is to keep versions on vec<Vertex*> roots; roots.pb(build(ST_L, ST_R)); 
int p_num = 0;        //
Vertex * init_leaf(int x) {
    pool[p_num].sum = x;
    pool[p_num].l = pool[p_num].r = NULL;
    return &pool[p_num++];
}
Vertex * init_node(Vertex * l, Vertex * r) {
    int sum = 0;
    if (l) sum += l->sum;
    if (r) sum += r->sum;
    pool[p_num].sum = sum; pool[p_num].l = l; pool[p_num].r = r;
    return &pool[p_num++];}
Vertex * build(int L, int R){
    if (L == R){return init_leaf(0);}
    int m = MD(L, R); return init_node(build(L, m), build(m + 1, R));}
Vertex * update(Vertex * v, int L, int R, int pos, int w){
    if (L == R)return init_leaf(v->sum + w);
    int m = MD(L, R);
    if (pos <= m) return init_node(update(v->l, L, m, pos, w), v->r);
    return init_node(v->l, update(v->r, m + 1, R, pos, w));}
int query(Vertex * vl, Vertex * vr, int L, int R, int ql, int qr) {
    if (!vl || !vr) return 0;
    if (ql > R || qr < L) return 0;
    if (ql == L && qr == R) {return vr->sum - vl->sum;}
    int m = MD(L, R);
    return query(vl->l, vr->l, L, m, ql, min(m, qr)) +
        query(vl->r, vr->r, m + 1, R, max(m + 1, ql), qr);}