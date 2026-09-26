/**
 * Author: Joaquin Bonora
 * Date: 2026-09-24
 * License: CC0
 * Source: folklore
 * Description: Hungarian algorithm for minimum-cost assignment in an $N \times M$ bipartite graph with $N \le M$. Returns $\{min\_cost, match\}$, where $match[i]$ is the matched column (0-indexed) for task $i$.
 * Time: O(N^2 M)
 * Status: tested
 */
#pragma once
template<typename T> struct hungarian {
    int n, m; // n tasks (rows), m workers (cols), requires n <= m
    vector<vector<T>> a;
    vector<T> u, v, minv;
    vector<int> p, way;
    vector<char> used;
    T inf;
    hungarian(int n_, int m_) : n(n_), m(m_),
        u(n + 1, 0), v(m + 1, 0), minv(m + 1), p(m + 1, 0), way(m + 1, 0),
        used(m + 1) {
        a = vector<vector<T>>(n, vector<T>(m));
        inf = numeric_limits<T>::max() / 2; // Headroom to prevent potential overflow
    }
    // Returns: {min_cost, matching}
    // match[i] = matched column index (0-indexed) for task i (0-indexed)
    pair<T, vector<int>> assignment() {
        for (int i = 1; i <= n; i++) {
            p[0] = i;
            int j0 = 0;
            fill(minv.begin(), minv.end(), inf);
            fill(used.begin(), used.end(), 0);
            do {
                used[j0] = 1;
                int i0 = p[j0], j1 = -1;
                T delta = inf;
                const T* row = a[i0 - 1].data();
                T u_i0 = u[i0];
                for (int j = 1; j <= m; j++) {
                    if (!used[j]) {
                        T cur = row[j - 1] - u_i0 - v[j];
                        if (cur < minv[j]) minv[j] = cur, way[j] = j0;
                        if (minv[j] < delta) delta = minv[j], j1 = j;
                    }
                }
                for (int j = 0; j <= m; j++) {
                    if (used[j]) u[p[j]] += delta, v[j] -= delta;
                    else minv[j] -= delta;
                }
                j0 = j1;
            } while (p[j0] != 0);
            do {
                int j1 = way[j0];
                p[j0] = p[j1];
                j0 = j1;
            } while (j0);
        }
        vector<int> match(n);
        for (int j = 1; j <= m; j++) {
            if (p[j] > 0 && p[j] <= n) {
                match[p[j] - 1] = j - 1;
            }
        }
        return make_pair(-v[0], match);
    }
};
