#ifndef CONTAINER_DOT_H
#define CONTAINER_DOT_H

template <class T>
struct arr
{
	int available;
	int used;
	
	T* buf;
	
	void append (T& next);
	void allocate (int num);
	void expand (); // allocate 50% more space
	void shrink (); // deallocate all unused elements
};

#endif
