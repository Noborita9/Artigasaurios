/**
 * Author: Juan Manuel Duarte
 * Date: 2026-09-29
 * License: CC0
 * Source: folklore
 * Description: EPS-tolerant point membership and intersections of lines and
 * closed segments (including endpoints and overlap). Lines are P+tR and
 * Q+uS, with nonzero direction vectors R and S. The output ans is assigned
 * only for a unique intersection. For point\_on\_line, a and b must differ.
 * Usage: Requires Point.h and ld from the contest template.
 * Time: O(1) per operation.
 * Status: untested
 */
#pragma once
#include "Point.h"

int sgn(ld x){
    if(fabsl(x) <= EPS) return 0;
    return x < 0 ? -1 : 1;
}
bool point_on_line(pt p, pt a, pt b){
    return sgn((b-a) % (p-a)) == 0;
}
bool point_on_segment(pt p, pt a, pt b){
    if(!point_on_line(p,a,b)) return false;
    return sgn((p-a) * (p-b)) <= 0;
}
// 0 -> no se intersectan
// 1 -> una única intersección
// 2 -> son la misma recta, infinitas intersecciones
int line_intersection(pt P, pt R, pt Q, pt S, pt &ans){
    ld cr = R % S;

    if(sgn(cr) == 0){
        if(sgn((Q-P) % R) == 0) return 2;
        return 0;
    }

    ld t = ((Q-P) % S) / cr;
    ans = P + R*t;

    return 1;
}
bool segments_intersect(pt a, pt b, pt c, pt d){
    int ab_c = sgn((b-a) % (c-a));
    int ab_d = sgn((b-a) % (d-a));
    int cd_a = sgn((d-c) % (a-c));
    int cd_b = sgn((d-c) % (b-c));

    if(ab_c == 0 && point_on_segment(c,a,b)) return true;
    if(ab_d == 0 && point_on_segment(d,a,b)) return true;
    if(cd_a == 0 && point_on_segment(a,c,d)) return true;
    if(cd_b == 0 && point_on_segment(b,c,d)) return true;

    return ab_c * ab_d < 0 && cd_a * cd_b < 0;
}
