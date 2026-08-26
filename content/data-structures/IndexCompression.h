/**
 * Author: Joaquin Bonora
 * Date: 2026-08-26
 * License: CC0
 * Source: folklore
 * Description: Coordinate compression for values of type T. Sorts and
 * deduplicates the input; of(e) returns the compressed index of a value,
 * at(i) returns the original value at a compressed index.
 * Time: O(N \log N) construction, O(\log N) per of() query.
 * Status: untested
 */
#pragma once
template<class T>
struct Index{ // If only 1 use Don't need to copy T type
    vec<T> d; int sz;
    Index(const vec<T> &a): d(ALL(a)){
        sort(ALL(d)); // Sort
        d.erase(unique(ALL(d)), end(d)); // Erase continuous duplicates
        sz = SZ(d); }
    inline int of(T e) const{return lower_bound(ALL(d), e) - begin(d);} // get index
    inline T at(int i) const{return d[i];} // get value of index
};
