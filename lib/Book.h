#ifndef _BOOK_H_
#define _BOOK_H_

#include <stdio.h>
#include <stdint.h>
#define TITLE_SIZE 50
#define AUTHOR_SIZE 50
#define BOOK_SIZE 4

typedef enum
{
    AC_EXIT_APP,
    AC_ADD_BOOK,
    AC_DEL_BOOK,
    AC_INVALID
} eBookAcType;

typedef enum
{
    BOOK_STATUS_AVAILABLE,
    BOOK_STATUS_NOTAVAILABLE
} eBookStatusType;

typedef struct Book
{
    /* data */
    uint32_t id;
    uint8_t title[TITLE_SIZE];
    uint8_t author[AUTHOR_SIZE];
    eBookStatusType status;
} sBookDataType;

/**
 * @brief  get user choice from keyboard
 */
eBookAcType getUserChoice(void);

/**
 * @brief  get user choice from keyboard
 */
void addBook(sBookDataType *pBook);

#endif /* _BOOK_H_ */
