/**
 * Author: Joaquin Bonora
 * Date: 2026-08-26
 * License: CC0
 * Source: folklore
 * Description: Extended Euclidean algorithm: computes $g=\gcd(a,b)$ along
 * with Bezout coefficients $x,y$ such that $ax+by=g$. findSolutionWithConstraints
 * finds an integer solution to $ax+by=c$ with $x\ge x\_min$ and $y\ge y\_min$
 * by shifting along the family of solutions parametrized by $b/g$ and $a/g$.
 * Time: O(\log(\min(a,b)))
 * Status: untested
 */
#pragma once
ll extendedGCD(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll x1, y1;
    ll gcd = extendedGCD(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return gcd;
}

bool findSolutionWithConstraints(ll a, ll b, ll c, ll x_min, ll y_min, ll &x, ll &y) {
    ll g = extendedGCD(a, b, x, y);

    if (c % g != 0) return false;

    x *= c / g;
    y *= c / g;

    // Ajustamos las variables a/g y b/g para mover las soluciones
    a /= g;
    b /= g;

    if (x < x_min) {
        ll k = (x_min - x + b - 1) / b;  // Redondeo hacia arriba
        x += k * b;
        y -= k * a;
    } else if (x > x_min) {
        ll k = (x - x_min) / b;
        x -= k * b;
        y += k * a;
    }

    if (y < y_min) {
        ll k = (y_min - y + a - 1) / a;  // Redondeo hacia arriba
        x += k * b;
        y -= k * a;
    } else if (y > y_min) {
        ll k = (y - y_min) / a;
        x -= k * b;
        y += k * a;
    }

    return x >= x_min && y >= y_min;
}
