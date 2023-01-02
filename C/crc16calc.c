
// Marcel Timm, RhinoDevel, 2023jan02.
//
// * Based on source code from Sven Reifegerste, see:
//
//   http://www.zorc.breitbandkatze.de/crc.html

#include <stdint.h>
#include <stdbool.h>

#include "crc16calc.h"

static uint8_t get_reversed_byte(uint8_t const byte)
{
    uint8_t ret_val = byte;

    ret_val = ((ret_val & 0xAA) >> 1) | ((ret_val & 0x55) << 1);
    ret_val = ((ret_val & 0xCC) >> 2) | ((ret_val & 0x33) << 2);
    ret_val = (ret_val >> 4) | (ret_val << 4);

    return ret_val;
}

static uint16_t get_reversed_word(uint16_t const word)
{
    return (get_reversed_byte(word & 0x00FF) << 8) // Rev. low byte as high b.
        | get_reversed_byte(word >> 8); // Reverse high byte as low byte.
}

uint16_t const crc16calc_get(
	uint16_t const polynomial,
	uint16_t const init_val,
	uint16_t const final_xor,
	bool const reverse_in,
	bool const reverse_out,
	uint8_t const* const bytes,
	int const bytes_cnt)
{
    uint16_t ret_val = init_val;

    for(int i = 0;i < bytes_cnt;++i)
    {
        uint8_t b = bytes[i];
        bool do_calc = false;

        if (reverse_in) // Reverse in.
        {
            b = get_reversed_byte(b);
        }

        for(int j = 0;j < 8;++j) // (j is used as counter, only)
        {
            do_calc = (ret_val & 0x8000) != 0; // Is CRC's highest bit set?
            if((b & 0x80) != 0) // Is cur. data byte's highest bit set?
            {
                do_calc = !do_calc;
            }
            //
            // => Calculate, if either the CRC's OR the current data
            //    byte's highest bit is set (but not, if both are set).

            ret_val <<= 1; // Left shift CRC word.
            ret_val &= 0xFFFF; // Should not be necessary in C.

            if (do_calc)
            {
                ret_val ^= polynomial;
            }

            b <<= 1; // Left shifts current byte.
        }
    }

    if(reverse_out) // Reverse out.
    {
        ret_val = get_reversed_word(ret_val);
    }

    ret_val ^= final_xor; // (Final) XOR.

    return ret_val;
}
