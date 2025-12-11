#include "Common.h"

uint32_t getIdInput(void)
{
    uint32_t retVal = 0;
    uint8_t buff[0xFF];

    if (fgets((char*)buff, sizeof(buff), stdin) != NULL)
    {
        retVal = (uint32_t)strtoul((char*)buff, NULL, 10);
    }

    return retVal;
}
