#include "trie.h"

#include <stdlib.h>

template <typename val_t, typename leaf_t, val_t END>
void Trie <val_t,leaf_t,END>::insert (const val_t* str, leaf_t result)
{
	Trie <val_t,leaf_t,END>* tree = this;
	Trie <val_t,leaf_t,END>* parent = 0;
	
	for (; *str != END; ++str)
	{
		if (tree->value == END)
		{
			// populate the first node at this level
			tree->value = *str;
		}
		
		// try to match the character at this level
		for (; *str != tree->value; tree = tree->next)
		{
			if (!tree->next)
			{
				// if not there, add it to the end
				tree->next = (Trie*) malloc (sizeof (Trie));
				Trie <val_t,leaf_t,END> next = {0};
				next.value = *str;
				*tree->next = next;
			}
		}
		
		if (!tree->match)
		{
			tree->match = (Trie*) malloc (sizeof (Trie));
			Trie <val_t,leaf_t,END> match = {0};
			match.value = *str;
			*tree->match = match;
		}
		parent = tree;
		tree = tree->match;
	}
	
	// null character can be left out;
	// store result in last character of key
	free (tree);
	tree = parent;
	tree->match = 0x0;
	tree->result = result;
}

template <typename val_t, typename leaf_t, val_t END>
leaf_t Trie <val_t,leaf_t,END>::find (const val_t* key)
{
	Trie <val_t,leaf_t,END>* tree = this;
	
	leaf_t result = 0;
	
	for (; *key; ++key)
	{
		result = tree->result;
		
		// try to match the character at this level
		for (; tree->value != *key; tree = tree->next)
		{
			// no more characters to test against
			if (!tree->next) return 0;
		}
		
		if (tree->match) tree = tree->match;
	}
	
	return result;
}
