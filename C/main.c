
// Marcel Timm, RhinoDevel, 2023jan02.

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include "crc16calc.h"

// CRC-16 parameters (hard-coded for CCITT / X.25):
//
#define MT_POLYNOMIAL 0x1021
#define MT_INITVAL 0xFFFF
#define MT_FINALXOR 0xFFFF
#define MT_REVERSEIN true
#define MT_REVERSEOUT true

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		printf("Error: Exactly one argument is expected!\n");
		return 1;
	}

	uint16_t const crc = crc16calc_get(
		MT_POLYNOMIAL,
		MT_INITVAL,
		MT_FINALXOR,
		MT_REVERSEIN,
		MT_REVERSEOUT,
		(uint8_t const *)argv[1],
		(int)strlen(argv[1]));

	printf("CRC (hex.): %04X\n", crc);
	return 0;
}
