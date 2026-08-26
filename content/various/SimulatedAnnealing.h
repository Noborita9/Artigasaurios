/**
 * Author: Joaquin Bonora
 * Date: 2026-08-26
 * License: CC0
 * Source: folklore
 * Description: Time-boxed simulated annealing. Timer wraps a monotonic clock;
 * Annealing takes a see() returning the candidate energy and an upd() that
 * commits a move, then simulate(s) runs for s seconds, accepting worsening
 * moves with probability exp(delta/temp) as the temperature falls linearly.
 * Note - WARNING: this references my\_clock and rng, neither declared here
 * nor in the team template, so it does not compile as written; supply both.
 * Ported as-is.
 * Time: unknown - bounded by wall-clock seconds, not input size.
 * Status: untested
 */
#pragma once
struct Timer {
	using time = my_clock::time_point;
	time start = my_clock::now();
	double elapsed() { // Segundos desde el inicio.
		time now = my_clock::now();
		return chrono::duration<double>(now - start).count();
	}
} timer;
template<class See,class Upd>struct Annealing {
	using energy = invoke_result_t<See>;
	energy curr, low;
	See see;
	Upd upd;
	Annealing(See _see, Upd _upd): see{_see}, upd{_upd}
		{curr = low = see(), upd();}
	void simulate(double s, double mult=1) { // Simula por `s` segundos.
		double t0 = timer.elapsed();
		for (double t = t0; t-t0 < s; t = timer.elapsed()) {
			energy near = see();
			auto delta = double(curr - near);
			if (delta >= 0) upd(), curr = near, low = min(low, curr);
			else {
				double temp = mult * (1 - (t-t0)/s);
				if (exp(delta/temp) > rng.real()) upd(), curr = near;
			}
		}
	}
};
auto see = [&] -> double {
    l = rng.integer(gsz);r = rng.integer(gsz);
    swap(groups[l], groups[r]);
    int ans = 0, rem =0;
    L(i,0,gsz){
        if (groups[i] > rem) {
            rem = x;
            ans ++;
        }
        rem -= groups[i];
    }
    swap(groups[l], groups[r]);
    return ans;
};
auto upd = [&] {swap(groups[l], groups[r]);};