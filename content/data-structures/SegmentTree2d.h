/**
 * Author: Bruno Maletta
 * Date: 2026-09-25
 * License: CC0
 * Source: https://github.com/brunomaletta/Biblioteca
 * Description: 0-indexed iterative 2D segment tree on an $N \times N$ grid. Set initial values in $seg[x+n][y+n]$ then call $build()$, or use $update()$. $query(x1, y1, x2, y2)$ returns rectangle sum $[x_1, x_2] \times [y_1, y_2]$ inclusive. For min/max, drop the if's in query and do all 4 ops. For Manhattan dist $\le d$: $nx = x+y, ny = x-y$.
 * Time: O(N^2) build, O(\log^2 N) update/query
 * Status: stress-tested
 */
#pragma once
// --- deps (drop what your solution already defines) --- // exclude-line
const int MAX = 1005; // exclude-line
// ------------------------------------------------------ // exclude-line
int seg[2*MAX][2*MAX], n;

void build() {
	for (int x = 2*n; x; x--) for (int y = 2*n; y; y--) {
		if (x < n) seg[x][y] = seg[2*x][y] + seg[2*x+1][y];
		if (y < n) seg[x][y] = seg[x][2*y] + seg[x][2*y+1];
	}
}

int query(int x1, int y1, int x2, int y2) {
	int ret = 0, y3 = y1 + n, y4 = y2 + n;
	for (x1 += n, x2 += n; x1 <= x2; ++x1 /= 2, --x2 /= 2)
		for (y1 = y3, y2 = y4; y1 <= y2; ++y1 /= 2, --y2 /= 2) {
			if (x1%2 == 1 and y1%2 == 1) ret += seg[x1][y1];
			if (x1%2 == 1 and y2%2 == 0) ret += seg[x1][y2];
			if (x2%2 == 0 and y1%2 == 1) ret += seg[x2][y1];
			if (x2%2 == 0 and y2%2 == 0) ret += seg[x2][y2];
		}
	return ret;
}

void update(int x, int y, int val) {
	int y2 = y += n;
	for (x += n; x; x /= 2, y = y2) {
		if (x >= n) seg[x][y] = val;
		else seg[x][y] = seg[2*x][y] + seg[2*x+1][y];
		while (y /= 2) seg[x][y] = seg[x][2*y] + seg[x][2*y+1];
	}
}
