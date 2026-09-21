/**
 * Author: Joaquin Bonora
 * Date: 2026-09-20
 * License: CC0
 * Source: folklore
 * Description: Comparator capturing external data, for heaps, sets and sort.
 * Pass the lambda to the constructor and name its type with decltype. Mind
 * the direction: the predicate that gives a min-heap sorts descending, since
 * priority\_queue pops its largest element first.
 * Time: O(1) per comparison.
 * Status: untested
 */
#pragma once
void comparators(vec<int> &val, vec<int> &idx) { // external data
	auto cmp = [&](int a, int b){return val[a] > val[b];}; // `>` gives min-heap
	priority_queue<int, vec<int>, decltype(cmp)> pq(cmp); // top() = smallest
	set<int, decltype(cmp)> s(cmp); // sorts descending
	sort(ALL(idx), cmp); // same, descending
}
// Keep the lambda inside a function: one with captures can't be global.
// If the type must be named (member, parameter), use a struct:
// struct Cmp { const vec<int> &val; // captured by reference
//   bool operator()(int a, int b) const {return val[a] > val[b];} };
