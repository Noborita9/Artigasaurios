/**
 * Author: Joaquin Bonora
 * Date: 2026-08-26
 * License: CC0
 * Source: folklore
 * Description: Time-boxed simulated annealing. Timer wraps a monotonic clock;
 * Annealing takes a see() returning the candidate energy and an upd() that
 * commits a move, then simulate(s) runs for s seconds, accepting worsening
 * moves with probability exp(delta/temp) as the temperature falls linearly.
 * Requires my\_clock and rng (see Rng.h).
 * Usage: Define: my_clock and rng - the Rng snippet in the Contest chapter provides both.
 * Time: unknown - bounded by wall-clock seconds, not input size.
 * Status: untested
 */
#pragma once
// --- deps (drop what your solution already defines) --- // exclude-line
using my_clock = chrono::steady_clock; // exclude-line
struct Random { // exclude-line
	mt19937_64 engine; // exclude-line
	Random(): engine(my_clock::now().time_since_epoch().count()) {} // exclude-line
	template<class Int>Int integer(Int n) {return integer<Int>(0, n);} // `[0,n)` // exclude-line
	template<class Int>Int integer(Int l, Int r) // exclude-line
		{return uniform_int_distribution{l, r-1}(engine);} // `[l,r)` // exclude-line
	double real() {return uniform_real_distribution{}(engine);} // `[0,1)` // exclude-line
} rng; // exclude-line
// ------------------------------------------------------ // exclude-line
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