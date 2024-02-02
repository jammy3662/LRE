#ifndef TRIE_DOT_H_IMPL
#define TRIE_DOT_H_IMPL

#include "trie.h"

#include <stdlib.h>
#include <string.h>

template <typename val, typename leaf, val END>
void Trie <val,leaf,END>::insert (const val* key, leaf result)
{
	Trie <val,leaf,END>* tree = this;
	leaf* last = &tree->result;
	
	while (*key != END)
	{
		if (tree->value == END)
			tree->value = *key;
		
		while (*key != tree->value)
		{
			if (!tree->next)
			{
				tree->next = (Trie*) malloc (sizeof *this);
				memset (tree->next, 0, sizeof *this);
				tree->next->value = *key;
			}
			
			tree = tree->next;
		}
		
		last = &tree->result;
		
		if (!tree->match)
		{
			tree->match = (Trie*) malloc (sizeof *this);
			memset (tree->match, 0, sizeof *this);
			tree->match->value = END;
		}
		tree = tree->match;
		
		key++;
	}
	
	//free (tree);
	*last = result;
}

template <typename val, typename leaf, val END>
leaf Trie <val,leaf,END>::find (const val* key)
{
	Trie <val,leaf,END>* tree = this;
	
	leaf result = 0;
	
	while (*key != END)
	{
		// try to match the character at this level
		while (*key != tree->value)
		{
			// no more characters to test against
			if (!tree->next) return 0;
			
			tree = tree->next;
		}
		
		result = tree->result;
		
		if (tree->match) tree = tree->match;
		key++;
	}
	
	return result;
}

#endif
