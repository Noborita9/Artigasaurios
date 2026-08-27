/**
 * Author: Joaquin Bonora
 * Date: 2026-08-26
 * License: CC0
 * Source: folklore
 * Description: All-pairs shortest paths on a dense graph given by its adjacency-matrix distances G. floyd(n) runs in place on a copy of the distance matrix; G[i][j] should be initialized to the direct edge weight (or infinity) before calling.
 * Time: O(V^3)
 * Status: untested
 */
#pragma once
const int N = 10;
int G[N][N]; // This Graph should be a copy, to de used as dintances
void floyd(int n) {
    L(k, 0, n)
        L(i, 0, n)
            L(j, 0, n)
                G[i][j] = min(G[i][j], G[i][k] + G[k][j]);
}