/**
 * Author: Joaquin Bonora, Juan Manuel Duarte
 * Date: 2026-08-26
 * License: CC0
 * Source: folklore (ray casting / crossing number)
 * Description: Point-in-polygon by ray casting: 0 outside, 1 inside, 2 on
 * the boundary, which it tests before counting crossings. The crossing test
 * puts a cross product in an ll while pt holds doubles, so it truncates --
 * safe for integral coordinates only. Requires Point.h.
 * Time: O(N)
 * Status: untested
 */
#pragma once
#include "Point.h"
int inPolygon(const vec<pt>& p, pt a) { // 0: Outside, 1: Inside, 2: Boundary
    int ans = 0; int n = SZ(p); 
    L(i,0,n) {
        pt p1 = p[i], p2 = p[(i + 1) % n];
        if ((p2 - p1) % (a - p1) == 0 && 
            min(p1.x, p2.x) <= a.x && a.x <= max(p1.x, p2.x) &&
            min(p1.y, p2.y) <= a.y && a.y <= max(p1.y, p2.y)) return 2;
        if ((p1.y > a.y) != (p2.y > a.y)) {
            ll cp = (p2 - p1) % (a - p1);
            if (p1.y < p2.y ? cp > 0 : cp < 0) ans = 1 - ans;
        }
    }
    return ans;
}