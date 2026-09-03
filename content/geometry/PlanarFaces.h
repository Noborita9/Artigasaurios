/**
 * Author: Juan Manuel Duarte
 * Date: 2026-08-26
 * License: CC0
 * Source: folklore
 * Description: The interior faces of a planar straight-line graph, each
 * returned as a loop of point COORDINATES, not vertex indices. The unbounded
 * outer face is dropped. Requires Point.h and PolygonArea.h (for
 * signed\_polygon\_area).
 * Time: O(V^2 + E \log E); the quadratic term is the dense position matrix.
 * Status: untested
 */
#pragma once
#include "Point.h"
#include "PolygonArea.h"
vec<vec<pt>> planar_faces(int n, vec<pt>& p, vec<pair<int, int>>& edges) {
    vec<vec<int>> adj(n);

    for (auto [a, b] : edges) {
        adj[a].pb(b);
        adj[b].pb(a);
    }

    L(v, 0, n) {
        sort(ALL(adj[v]), [&](int a, int b) {
            pt va = p[a] - p[v];
            pt vb = p[b] - p[v];

            ld anga = atan2(va.y, va.x);
            ld angb = atan2(vb.y, vb.x);

            return anga < angb;
            });
    }

    vec<vec<int>> pos(n, vec<int>(n, -1));

    L(v, 0, n) {
        L(i, 0, SZ(adj[v])) {
            pos[v][adj[v][i]] = i;
        }
    }

    vec<vec<char>> used(n, vec<char>(n, false));
    vec<vec<pt>> faces;

    L(startU, 0, n) {
        for (int startV : adj[startU]) {
            if (used[startU][startV]) continue;

            vec<int> faceIdx;

            int u = startU;
            int v = startV;

            while (!used[u][v]) {
                used[u][v] = true;
                faceIdx.pb(u);

                int id = pos[v][u];
                int deg = SZ(adj[v]);

                int w = adj[v][(id - 1 + deg) % deg];

                u = v;
                v = w;
            }

            if (SZ(faceIdx) >= 3) {
                vec<pt> face;

                for (int idx : faceIdx) {
                    face.pb(p[idx]);
                }

                if (signed_polygon_area(face) > EPS) {
                    faces.pb(face);
                }
            }
        }
    }

    return faces;
}