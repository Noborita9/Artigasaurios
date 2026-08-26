/**
 * Author: Joaquin Bonora
 * Date: 2026-08-26
 * License: CC0
 * Source: folklore
 * Description: GNU PBDS aliases: indexed\_set is an order-statistics tree (policy-based red-black tree) supporting find\_by\_order and order\_of\_key in addition to the usual ordered-set operations; htable is a hash-table-backed map/set alternative to unordered\_map/unordered\_set (faster, but lacks count()).
 * Time: O(\log N) per operation on indexed\_set; O(1) average per operation on htable.
 * Status: untested
 */
#pragma once
#include <ext/pb_ds/assoc_container.hpp> 
using namespace __gnu_pbds;
template<typename Key, typename Val=null_type>
using indexed_set = tree<Key, Val, less<Key>, rb_tree_tag,
                         tree_order_statistics_node_update>;
// indexed_set<char> s;
// char val = *s.find_by_order(0); // acceso por indice
// int idx = s.order_of_key('a'); // busca indice del valor
template<class Key,class Val=null_type>using htable=gp_hash_table<Key,Val>;
// como unordered_map (o unordered_set si Val es vacio), pero sin metodo count
