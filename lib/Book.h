#ifndef _BOOK_H_
#define _BOOK_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define TITLE_SIZE 50
#define AUTHOR_SIZE 50
#define BOOK_SIZE 4
#define INVALID_CHOICE (-1)
#define CHAR_TO_NUM(x) (((x) >= '0' && (x) <= '9') ? ((x) - '0') : INVALID_CHOICE)

typedef enum
{
    AC_EXIT_APP = 0,
    AC_ADD_BOOK,
    AC_DEL_BOOK,
    AC_INVALID
} eBookAcType;

typedef enum
{
    BOOK_STATUS_AVAILABLE = 0,
    BOOK_STATUS_BORROWED,
    BOOK_STATUS_EMPTY
} eBookStatusType;

typedef struct Book
{
    /* data */
    uint32_t id;
    uint8_t title[TITLE_SIZE];
    uint8_t author[AUTHOR_SIZE];
    eBookStatusType status;
    struct Book *pNextBook;
} sBookDataType;

/**
 * @brief  clear all stdin for the next process
 */
void clearStdinBuff(void);

/**
 * @brief  get user choice from keyboard
 */
eBookAcType getUserChoice(void);

/**
 * @brief  get user choice from keyboard
 */
void printfBookInfo(sBookDataType *pBook);

/**
 * @brief  get user choice from keyboard
 */
void formatBook(sBookDataType *pBook);

/**
 * @brief  get user choice from keyboard
 */
void addBook(sBookDataType **pBook, sBookDataType sampleBook);

#endif /* _BOOK_H_ */
