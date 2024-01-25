#include "import.h"

enum format_t { t2D, t3D, tCUBEMAP };
enum order { RGB, GBR, BRG, RBG, GRB, BGR }; // alpha channel always last

enum
{
	type = 0b11000000, // 2D, 3D, or cubemap
	channels = 0b00111000, // rgba has 4 channels
	order = 0b00000111 // rgb | bgr | (etc...)
};

enum attrib_t
{
	CHAR = 1, SHORT = 2, INT = 4,
	LONG = 8, FLOAT = 4, DOUBLE = 8,
};
