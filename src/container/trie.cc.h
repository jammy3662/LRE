#ifndef TRIE_DOT_H_IMPL
#define TRIE_DOT_H_IMPL

#include "trie.h"

#include <stdlib.h>
#include <string.h>

#define TrieC Trie<KeyT,END,ValT,NUL>
#define TrieT <typename KeyT, KeyT END, typename ValT, ValT NUL>

template TrieT
TrieC::Trie ()
{
	key = END;
	val = NUL;
	next = 0;
	match = 0;
}

template TrieT
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
				tree->next = (Trie*) malloc (sizeof (TrieC));
				TrieC tmp; *tree->next = tmp;
				tree->next->key = *key;
			}
			
			tree = tree->next;
		}
		
		last = &tree->val;
		
		if (!tree->match)
		{
			tree->match = (Trie*) malloc (sizeof (TrieC));
			TrieC tmp; *tree->match = tmp;
			tree->match->key = END;
		}
		tree = tree->match;
		
		key++;
	}
	
	*last = val;
}

template TrieT
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
