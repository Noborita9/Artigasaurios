/**
 * Author: Joaquin Bonora
 * Date: 2026-08-26
 * License: CC0
 * Source: folklore (geeksforgeeks, adapted)
 * Description: Computes a "longest prefix-suffix" array for a pattern. WARNING:
 * on a mismatch this resets len to 0 without falling back through lps[len-1]
 * (the standard KMP failure-function backtrack), so the result differs from
 * the textbook prefix function on patterns with overlapping repeats and is
 * unsafe to feed into a KMP search. Known bug, ported as-is.
 * Time: O(N)
 * Status: untested
 */
#pragma once
vec<int> getLps(string pat){ //geek4geeks implementatio with some changes
  vec<int> lps(pat.length(), 0);
  int len = 0;
  int i = 1;
  lps[0] = 0;
  while(i < pat.length()){
    if(pat[i] == pat[len]){
      len++;
      lps[i] = len;
      i++;
    }
    else //pat[i] != pat[len] 
    {
      lps[i] = 0;
      i++;
    }
  }
  return lps;
}
