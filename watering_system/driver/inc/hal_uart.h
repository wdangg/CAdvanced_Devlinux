#ifndef _HAL_UART_H_
#define _HAL_UART_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/**
 * @brief  Borrow a book for the selected user.
 */
void HAL_UartInit(void);

/**
 * @brief  Borrow a book for the selected user.
 */
void HAL_UartSendChar(char c);

/**
 * @brief  Borrow a book for the selected user.
 */
void HAL_UartSendString(const char *s);

#endif /* _HAL_UART_H_ */