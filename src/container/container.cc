#include "container.h"

#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static int roundNearest (float f)
{
	return (int) (f + 0.5);
}

template <typename T>
void arr<T>::allocate (int16_t n)
{
	used = 0;
	available = n;
	buf = realloc (buf, n * sizeof(T));
}

template <typename T>
int16_t arr<T>::expand ()
{
	int16_t prev = available;
	// add 50% size of the current used elements
	available = roundNearest ((float)available * 1.5);
	
	buf = (T*) realloc (buf, available * sizeof(T));
	
	return available - prev;
}

template <typename T>
int16_t arr<T>::append (T& next)
{
	int16_t added;
	
	if (used >= available)
		added = expand ();
	
	buf [used] = next;
	
	used++;
	return added;
}

template <typename T>
int16_t arr<T>::shrink ()
{
	int16_t unused = available - used;
	buf = realloc (buf, used * sizeof(T));
	available = used;
	return unused;
}
