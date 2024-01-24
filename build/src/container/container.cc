#include "container.h"

#include <math.h>

template <class T>
void arr <T>::allocate (int num)
{
	buf = realloc (buf, num * sizeof (T));
	available = num;
}

template <class T>
void arr <T>::expand ()
{
	// double the current capacity
	// or allocate the first element
	int newsz = (available ? available : 1);
	newsz *= (int)ceil(1.5);
	available = newsz;
	
	buf = (T*) realloc (buf, newsz * sizeof (T));
}

template <class T>
void arr <T>::append (T& next)
{
	if (used >= available)
		expand ();
	
	buf [used] = next;
	next++;
}
