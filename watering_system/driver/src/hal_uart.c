#include "hal_uart.h"

void HAL_UartInit(void)
{
    printf("[UART_SIMULATION] UART has been initialized successfully!\n");
}

void HAL_UartSendChar(char c)
{
    printf("[UART_SIMULATION] %c\n", c);
}

void HAL_UartSendString(const char *s)
{
    printf("[UART_SIMULATION] %s\n", s);
}
