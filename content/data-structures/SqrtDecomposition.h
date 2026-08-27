/**
 * Author: Joaquin Bonora
 * Date: 2026-08-26
 * License: CC0
 * Source: folklore
 * Description: Sqrt decomposition over a static-size array split into blocks of size BLOCK\_SIZE (~= sqrt N). Point update and range-sum query. Favors update-heavy workloads over query-heavy ones.
 * Time: O(N) construction, O(1) per update, O(\sqrt N) per query.
 * Status: untested
 */
#pragma once
const int BLOCK_SIZE = 450; // ~= sqrt N
struct SQRTDecomp {
    vec<int> B, Bs, Bid; int n;// DEFINE BLOCK_SIZE ~= sqrt N
    SQRTDecomp(int n_): B(n_), Bid(n_), n(n_), Bs((n_ + BLOCK_SIZE - 1)/BLOCK_SIZE) { 
        L(i,1,n) Bid[i] = Bid[i - 1] + (i % BLOCK_SIZE == 0);
    } // useful if many updates not many queries, may be better than st
    void upd(int ix, int w) { B[ix] += w; Bs[Bid[ix]] += w;} // O(1)
    int query(int l, int r){ // O(BLOCK_SIZE) // [l, r)
        int ans = 0;
        for (int i = l; i < r;) {
            if (i + BLOCK_SIZE >= r || (i % BLOCK_SIZE) != 0) ans += B[i ++];
            else { ans += Bs[Bid[i]]; i += BLOCK_SIZE;}
        }
        return ans;
    }
};