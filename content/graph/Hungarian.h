/**
 * Author: Joaquin Bonora
 * Date: 2026-08-26
 * License: CC0
 * Source: folklore
 * Description: Hungarian algorithm (Jonker-Volgenant style) for minimum-cost perfect assignment in an N x M bipartite graph. Unset entries default to cost INF; for maximum assignment set INF to 0 and negate costs. assign() returns the total cost and appends the chosen edges to the global ans vector.
 * Time: O(N^3)
 * Status: untested
 */
#pragma once
using vi = vec<int>;
using vd = vec<ld>;
const ld INF = 1e100;	   // Para max asignacion, INF = 0, y negar costos
bool zero(ld x) {return fabs(x) < 1e-9;}	// Para int/ll: return x==0;
vec<pii> ans; // Guarda las aristas usadas en el matching: [0..n)x[0..m)
struct Hungarian{
	int n; vec<vd> cs; vi vL, vR;
	Hungarian(int N, int M) : n(max(N,M)), cs(n,vd(n)), vL(n), vR(n){
		L(x, 0, N) L(y, 0, M) cs[x][y] = INF;
	}
	void set(int x, int y, ld c) { cs[x][y] = c; }
	ld assign(){
		int mat = 0; vd ds(n), u(n), v(n); vi dad(n), sn(n);
		L(i, 0, n) u[i] = *min_element(ALL(cs[i]));
		L(j, 0, n){
			v[j] = cs[0][j]-u[0];
			L(i, 1, n) v[j] = min(v[j], cs[i][j] - u[i]);
		}
		vL = vR = vi(n, -1);
		L(i,0, n) L(j, 0, n) if(vR[j] == -1 and zero(cs[i][j] - u[i] - v[j])){
			vL[i] = j; vR[j] = i; mat++; break;
		}
		for(; mat < n; mat ++){
			int s = 0, j = 0, i;
			while(vL[s] != -1) s++;
			fill(ALL(dad), -1); fill(ALL(sn), 0);
			L(k, 0, n) ds[k] = cs[s][k]-u[s]-v[k];
			while(true){
				j = -1;
				L(k, 0, n) if(!sn[k] and (j == -1 or ds[k] < ds[j])) j = k;
				sn[j] = 1; i = vR[j];
				if(i == -1) break;
				L(k, 0, n) if(!sn[k]){
					auto new_ds = ds[j] + cs[i][k] - u[i]-v[k];
					if(ds[k] > new_ds) ds[k]=new_ds, dad[k]=j;
				}
			}
			L(k, 0, n) if(k!=j and sn[k]){
				auto w = ds[k]-ds[j]; v[k] += w, u[vR[k]] -= w;
			}			
			u[s] += ds[j];
			while(dad[j] >= 0){ int d = dad[j]; vR[j] = vR[d]; vL[vR[j]] = j; j = d; }
			vR[j] = s; vL[s] = j;
		}
		ld value = 0; L(i, 0, n) value += cs[i][vL[i]], ans.pb({i, vL[i]});
		return value;
	}
};