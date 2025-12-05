#ifndef _BOOK_H_
#define _BOOK_H_

#include <stdio.h>
#include <stdint.h>

typedef enum
{
    AC_EXIT_APP,
    AC_ADD_BOOK,
    AC_DEL_BOOK,
    AC_INVALID
} eBookAcType;

/**
 * @brief  get user choice from keyboard
 */
eBookAcType getUserChoice(void);

#endif /* _BOOK_H_ */
