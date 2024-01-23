#include "trie.h"

template <size_t N>
void Trie::insert (Key keys [N])
{
	for (Key key : keys)
	{
		insert (key.key, key.value);
	}
}

template <typename val_t, typename leaf_t>
void Trie::insert (const val_t* str, leaf_t result)
{
	Trie <val_t,leaf_t>* tree = this;
	Trie <val_t,leaf_t>* parent = 0;
	
	for (; *str; ++str)
	{
		if (tree->value == -1)
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
				*tree->next = {.value = *str, .next = 0x0, .match = 0x0, .result = 0};
			}
		}
		
		if (!tree->match)
		{
			tree->match = (Trie*) malloc (sizeof (Trie));
			*tree->match = {.value = -1, .next = 0x0, .match = 0x0, .result = 0};
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

Tok Trie::find (const char* key)
{
	Trie* tree = this;
	
	unsigned char result = 0;
	
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
