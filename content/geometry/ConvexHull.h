/**
 * Author: Joaquin Bonora, Juan Manuel Duarte
 * Date: 2026-08-26
 * License: CC0
 * Source: folklore (monotone chain)
 * Description: Andrew monotone-chain convex hull over pt. Sorts and dedupes
 * the input in place, then builds the lower and upper chains, returning them
 * counter-clockwise. Note the turn test pops only on a strict right turn
 * (cross < -EPS), so collinear points on a hull edge are KEPT, not removed.
 * Requires Point.h.
 * Time: O(N \log N), dominated by the sort.
 * Status: untested
 */
#pragma once
double cross_product(pt O, pt A, pt B) {
    return (A - O) % (B - O);
}

vec<pt> convex_hull(vec<pt>& points) {
    sort(ALL(points));
    points.erase(unique(ALL(points)), points.end());
    vec<pt> hull;
    for (const auto& p : points) {
        while (SZ(hull) >= 2 && cross_product(hull[SZ(hull) - 2], hull[SZ(hull) - 1], p) < -EPS)
            hull.pop_back();

        if (hull.empty() || !(hull.back() == p))
            hull.pb(p);
    }
    int t = SZ(hull) + 1;
    for (int i = SZ(points) - 1; i >= 0; i--) {
        while (SZ(hull) >= t && cross_product(hull[SZ(hull) - 2], hull[SZ(hull) - 1], points[i]) < -EPS)
            hull.pop_back();

        if (hull.empty() || !(hull.back() == points[i]))
            hull.pb(points[i]);
    }
    hull.pop_back();
    return hull;
}