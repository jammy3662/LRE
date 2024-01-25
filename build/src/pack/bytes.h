#ifndef BYTES_DOT_H
#define BYTES_DOT_H

/*________________________________________________________________
|
| Platform-related byte manipulation for compatibility.
|________________________________________________________________*/

#include <stdint.h>

namespace bytes
{
	// tests endianness at runtime for each platform
	extern int8_t testendian ();

	// byte swap - reversing byte order
	extern int16_t bswap (int16_t s);
	extern int32_t bswap (int32_t i);
	extern int64_t bswap (int64_t l);
	extern float   bswap (float f);
	extern double  bswap (double d);
}

#endif
