#ifndef BYTES_DOT_H
#define BYTES_DOT_H

/*________________________________________________________________
|
| Platform-related byte manipulation for compatibility.
|________________________________________________________________*/

#include <stdint.h>

namespace bytes
{
	// tests endianness at runtime of current platform
	int8_t testendian ();

	// byte swap - reversing byte order
	int16_t bswap (int16_t s);
	int32_t bswap (int32_t i);
	int64_t bswap (int64_t l);
	float   bswap (float f);
	double  bswap (double d);
}

#endif
