#ifndef CONTAINER_DOT_H
#define CONTAINER_DOT_H

#pragma pack (push, 1)

#include <stdint.h>

template <typename T>
struct arr
{
	int16_t available;
	int16_t used;
	
	T* buf;
	
	int16_t append (T& next); // returns # of new elements allocated
	void allocate (int16_t num);
	int16_t expand (); // allocate 50% more space (returns # new elements)
	int16_t shrink (); // deallocate all unused elements (returns # unused elements)
	
	T& operator [] (int16_t idx) {return buf[idx];};
	operator T* () {return buf;}
};

#pragma pack (pop)

#endif
