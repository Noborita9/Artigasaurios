/**
 * Author: Joaquin Bonora
 * Date: 2026-08-26
 * License: CC0
 * Source: folklore
 * Description: 2-SAT solver over n boolean variables. add\_disj(a, na, b, nb) adds the clause (a = !na) OR (b = !nb). solve() returns whether the formula is satisfiable and, if so, fills assign with a satisfying assignment. Uses SCC via two explicit DFS passes on g and its transpose g\_t.
 * Time: O(V + E)
 * Status: untested
 */
#pragma once
struct TwoSat {
    int n, v_n;
    vec<bool> vis, assign;
    vec<int> order, comp;
    vec<vec<int>> g, g_t;
    TwoSat(int n_): n(n_), v_n(2 * n_), vis(v_n) , assign(n_),  comp(v_n, - 1), g(v_n), g_t(v_n) {
        order.reserve(v_n);
    }
    void add_disj(int a, bool na, int b, bool nb) { // negated_a, negated_b
        a = 2 * a ^ na;
        b = 2 * b ^ nb;
        int neg_a = a ^ 1;
        int neg_b = b ^ 1;
        g[neg_a].pb(b);
        g[neg_b].pb(a);
        g_t[a].pb(neg_b);
        g_t[b].pb(neg_a);
    }
    void dfs1(int u){
        vis[u] = 1;
        for (int v: g[u]) if (!vis[v]) dfs1(v);
        order.pb(u);
    }   
    void dfs2(int u, int cc) {
        comp[u] = cc;
        for (int v: g_t[u]) if (comp[v] == -1) dfs2(v, cc);
    }
    bool solve() {
        order.clear();
        vis.assign(v_n, 0);
        L(i,0, v_n) if (!vis[i]) dfs1(i);
        comp.assign(v_n, - 1);
        int cc = 0;
        L(i, 0, v_n) {
            int v = order[v_n - 1 - i];
            if (comp[v] == -1) dfs2(v, cc ++);
        }
        assign.assign(n, false);
        for (int i = 0;i < v_n; i += 2) {
            if (comp[i] == comp[i+1]) return false;
            assign[i / 2] = comp[i] > comp[i + 1];
        }
        return true;
    }
};