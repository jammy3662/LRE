// ________________________________________________________________
//    Portability / endianness (byte order)
// \______________________________________________________________/

#include "bytes.h"
#include "brief.h"

// tests endianness at runtime for each platform
int8 bytes::testendian ()
{
	int32 n = 1;
	
	// if it's big endian, '0' will be in byte 1, leaving the '1' in byte 4
	if (( (int8*) &n )[0]) return 'l';
	if (( (int8*) &n )[3]) return 'b';
	
	return '?';
	
}

int16 bytes::bswap (int16 s)
{
	return (s << 8 | s >> 8);
}

int32 bytes::bswap (int32 i)
{
	// cast a 4-byte int to an array of 4 bytes
	// (and vice versa)
	int8* src = (int8*) &i;
	
	int8 dst [] = {src[3], src[2], src[1], src[0]};
	
	return *(int32*) dst;
}

int64 bytes::bswap (int64 l)
{
	// same logic as 32 bit swap func
	int8* src = (int8*) &l;
	
	int8 dst [] = {src[7], src[6], src[5], src[4],
								 src[3], src[2], src[1], src[0]};
	
	return *(int64*) dst;
}

float bytes::bswap (float f) {	return bswap (*(int32*)&f); }
double bytes::bswap (double d) { return bswap (*(int64*)&d); }
