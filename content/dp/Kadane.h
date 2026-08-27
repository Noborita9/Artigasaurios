/**
 * Author: Joaquin Bonora
 * Date: 2026-08-26
 * License: CC0
 * Source: folklore
 * Description: Kadane's algorithm. Finds the maximum-sum contiguous subarray of a non-empty array, along with the start and end indices achieving it.
 * Time: O(N)
 * Status: untested
 */
#pragma once
pair<int, pair<int,int>> kadane(vec<int>& arr) {
    int maxSoFar = arr[0], maxEndingHere = arr[0];
    int start = 0, end = 0, s = 0;
    for(int i = 1; i < arr.size(); i++) {
        if(maxEndingHere + arr[i] < arr[i]) {
            maxEndingHere = arr[i];
            s = i;
        } else {
            maxEndingHere += arr[i];
        }
        if(maxEndingHere > maxSoFar) {
            maxSoFar = maxEndingHere;
            start = s;
            end = i;
        }
    }
    return {maxSoFar, {start, end}}; // max, l, r
}
