/**
 * Author: Joaquin Bonora, Juan Manuel Duarte
 * Date: 2026-08-26
 * License: CC0
 * Source: folklore (shoelace formula)
 * Description: Shoelace area of a simple polygon given as a vertex list.
 * signed\_polygon\_area keeps the sign, so it is positive for
 * counter-clockwise vertex order and negative for clockwise, which doubles
 * as an orientation test; polygon\_area returns the absolute value.
 * Requires Point.h.
 * Time: O(N)
 * Status: untested
 */
#pragma once
#include "Point.h"
double signed_polygon_area(vec<pt>& polygon) {
    double area = 0;
    int n = SZ(polygon);
    L(i, 0, n) {
        int j = (i + 1) % n;
        area += polygon[i] % polygon[j];
    }
    return area / 2.0;
}

double polygon_area(vec<pt>& polygon) {
    return abs(signed_polygon_area(polygon));
}