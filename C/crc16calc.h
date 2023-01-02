
// Marcel Timm, RhinoDevel, 2023jan02.

#ifndef MT_CRC16CALC
#define MT_CRC16CALC

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

uint16_t const crc16calc_get(
	uint16_t const polynomial,
	uint16_t const init_val,
	uint16_t const final_xor,
	bool const reverse_in,
	bool const reverse_out,
	uint8_t const* const bytes,
	int const bytes_cnt);

#ifdef __cplusplus
}
#endif

#endif //MT_CRC16CALC