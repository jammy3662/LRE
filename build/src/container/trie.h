#ifndef TRIE_DOT_H
#define TRIE_DOT_H

template <typename val_t, typename leaf_t, val_t END_VAL>
struct Trie
{
	val_t value;
	leaf_t result;
	
	Trie* next;
	Trie* match;
	
	// TODO: write a trie "compress" function that
	// groups sequential characters into a single node
	
	void insert (const val_t* key, leaf_t result);
	leaf_t find (const val_t* key);
};

#endif
