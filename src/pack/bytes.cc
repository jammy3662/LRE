// ________________________________________________________________
//    Portability / endianness (byte order)
// \______________________________________________________________/

#include "bytes.h"

// tests endianness at runtime for each platform
int8_t bytes::testendian ()
{
	int32_t n = 1;
	
	// if it's big endian, '0' will be in byte 1, leaving the '1' in byte 4
	if (( (int8_t*) &n )[0]) return 'l';
	if (( (int8_t*) &n )[3]) return 'b';
	
	return '?';
	
}

int16_t bytes::bswap (int16_t s)
{
	return (s << 8 | s >> 8);
}

int32_t bytes::bswap (int32_t i)
{
	// cast a 4-byte int to an array of 4 bytes
	// (and vice versa)
	int8_t* src = (int8_t*) &i;
	
	int8_t dst [] = {src[3], src[2], src[1], src[0]};
	
	return *(int32_t*) dst;
}

int64_t bytes::bswap (int64_t l)
{
	// same logic as 32 bit swap func
	int8_t* src = (int8_t*) &l;
	
	int8_t dst [] = {src[7], src[6], src[5], src[4],
								 src[3], src[2], src[1], src[0]};
	
	return *(int64_t*) dst;
}

float bytes::bswap (float f) {	return bswap (*(int32_t*)&f); }
double bytes::bswap (double d) { return bswap (*(int64_t*)&d); }
