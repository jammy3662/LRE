#ifndef TRIE_DOT_H_IMPL
#define TRIE_DOT_H_IMPL

#include "trie.h"

#include <stdlib.h>
#include <string.h>

#define TrieC Trie<KeyT,END,ValT,NUL>

template <typename KeyT, KeyT END, typename ValT, ValT NUL>
void TrieC::insert (const KeyT* key, ValT val)
{
	TrieC* tree = this;
	ValT* last = &tree->val;
	
	while (*key != END)
	{
		if (tree->key == END)
			tree->key = *key;
		
		while (*key != tree->key)
		{
			if (!tree->next)
			{
				tree->next = (Trie*) malloc (sizeof *this);
				memset (tree->next, 0, sizeof *this);
				tree->next->key = *key;
			}
			
			tree = tree->next;
		}
		
		last = &tree->val;
		
		if (!tree->match)
		{
			tree->match = (Trie*) malloc (sizeof *this);
			memset (tree->match, 0, sizeof *this);
			tree->match->key = END;
		}
		tree = tree->match;
		
		key++;
	}
	
	*last = val;
}

template <typename KeyT, KeyT END, typename ValT, ValT NUL>
ValT TrieC::find (const KeyT* key)
{
	TrieC* tree = this;
	
	ValT ret = NUL;
	
	while (*key != END)
	{
		// try to match the character at this level
		while (*key != tree->key)
		{
			// no more characters to test against
			if (!tree->next) return NUL;
			
			tree = tree->next;
		}
		
		ret = tree->val;
		
		if (tree->match) tree = tree->match;
		key++;
	}
	
	return ret;
}

#endif
