/**
 * Author: Joaquin Bonora
 * Date: 2026-08-26
 * License: CC0
 * Source: folklore
 * Description: Suffix automaton (SAM), built online by repeated sa\_extend
 * calls. st[k].len is the longest string in state k's equivalence class,
 * st[k].link its suffix link, st[k].next its transition map. Relies on an
 * local constant N sizing the state array (2 * N states).
 * Time: O(L \log \Sigma) amortized to build over a string of length L
 * (transitions are a std::map, hence the log Sigma factor).
 * Status: untested
 */
#pragma once
const int N = 100005;
struct state {int len,link;map<char,int> next;}; //clear next!!
state st[2 * N]; // Important 2 * n
int sz,last;
void sa_init(){
	last=st[0].len=0;sz=1;
	st[0].link=-1;
}
void sa_extend(char c){
	int k=sz++,p;
	st[k].len=st[last].len+1;
	for(p=last;p!=-1&&!st[p].next.count(c);p=st[p].link)st[p].next[c]=k;
	if(p==-1)st[k].link=0;
	else {
		int q=st[p].next[c];
		if(st[p].len+1==st[q].len)st[k].link=q;
		else {
			int w=sz++; // Is clone should not be counted!!!
			st[w].len=st[p].len+1;
			st[w].next=st[q].next;st[w].link=st[q].link;
			for(;p!=-1&&st[p].next[c]==q;p=st[p].link)st[p].next[c]=w;
			st[q].link=st[k].link=w;
		}
	}
	last=k;
}