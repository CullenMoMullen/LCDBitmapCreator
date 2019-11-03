#include "types.h"
#include "components/runtime/runtime.h"

void  rt_halfwordset(uint16_t * pPtr, uint16_t u16Data, uint16_t u16Count)
{
	while (u16Count--)
	{
		*pPtr++ = u16Data;
	}
}


void  rt_24bitset(void* pPtr, uint32_t u32Data, uint16_t u16Count)
{
	uint8_t* pu8 = (uint8_t*)pPtr;
	uint8_t u8r = (u32Data) & 0xff;
	uint8_t u8g = (u32Data >> 8) & 0xff;
	uint8_t u8b = (u32Data >> 16) & 0xff;
	while (u16Count--)
	{
		*pu8++ = u8r;
		*pu8++ = u8g;
		*pu8++ = u8b;
	}
}