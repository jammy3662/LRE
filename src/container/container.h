#ifndef CONTAINER_DOT_H
#define CONTAINER_DOT_H

#pragma pack (push, 1)

#include <stdint.h>

template <typename T>
struct arr
{
	uint32_t count, available;
	
	T* buf;
	
	uint32_t append (T& next); // returns # of new elements allocated
	void allocate (uint32_t num);
	uint32_t expand (); // allocate 50% more space (returns # new elements)
	uint32_t shrink (); // deallocate all unused elements (returns # unused elements)
	void clear (); // deallocate all memory
	
	T& operator [] (uint32_t idx) {return buf[idx];};
	operator T* () {return buf;}
};

#include "container.cc.h"

#pragma pack (pop)

#endif
