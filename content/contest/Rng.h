/**
 * Author: Joaquin Bonora
 * Date: 2026-08-26
 * License: CC0
 * Source: folklore
 * Description: Seeded 64-bit Mersenne Twister with a helper for uniform
 * integers in a range. Use instead of rand() to avoid anti-hash tests.
 * Time: O(1) per draw.
 * Status: untested
 */
#pragma once
using my_clock = chrono::steady_clock;
struct Random {
	mt19937_64 engine;
	Random(): engine(my_clock::now().time_since_epoch().count()) {}
	template<class Int>Int integer(Int n) {return integer<Int>(0, n);} // `[0,n)`
	template<class Int>Int integer(Int l, Int r)
		{return uniform_int_distribution{l, r-1}(engine);} // `[l,r)`
	double real() {return uniform_real_distribution{}(engine);} // `[0,1)`
} rng;
