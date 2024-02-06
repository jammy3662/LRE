#ifndef TRIE_DOT_H
#define TRIE_DOT_H

#pragma pack (push, 1)

template <typename KeyT, KeyT END, typename ValT, ValT NUL>
struct Trie
{
	KeyT key;
	ValT val;
	
	Trie* next;
	Trie* match;
	
	// TODO: write a trie "compress" function that
	// groups sequential characters into a single node
	
	void insert (const KeyT* key, ValT val);
	ValT find (const KeyT* key);
	
	Trie();
};

#include "trie.cc.h"

#pragma pack (pop)

#endif
