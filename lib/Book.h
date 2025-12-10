#ifndef _BOOK_H_
#define _BOOK_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TITLE_SIZE 50
#define AUTHOR_SIZE 50
#define BOOK_SIZE 4

#define BOOK_CHAR_TO_NUM(x) (((x) >= '0' && (x) <= '9') ? ((x) - '0') : BOOK_INVALID_SEL)

typedef enum eBookSelAcc
{
    BOOK_ADD,
    BOOK_DEL,
    BOOK_MODIFY_INFO,
    BOOK_INVALID_SEL,
} eBookSelAccType;

typedef struct sBookSelAcc
{
    eBookSelAccType id;
    const char *msg;
} sBookSelAccType;

static const sBookSelAccType sBookSellAcc[] = {
    {BOOK_ADD,          "Add a book"},
    {BOOK_DEL,          "Delete a book"},
    {BOOK_MODIFY_INFO,  "Modify book infomation"},
};

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
void printfBookInfo();

/**
 * @brief  get user choice from keyboard
 */
void formatBook(sBookDataType *pBook);

/**
 * @brief  get user choice from keyboard
 */
void addBook(sBookDataType sampleBook);

/**
 * @brief  get user choice from keyboard
 */
void delBook();

/**
 * @brief  get user choice from keyboard
 */
void modifyBook();

/**
 * @brief  get user choice from keyboard
 */
void editBookInfo(sBookDataType *pBook);

/**
 * @brief  get user choice from keyboard
 */
eBookSelAccType bookSelectAcc();

/**
 * @brief  get user choice from keyboard
 */
void printBookSelAcc();

/**
 * @brief  get user choice from keyboard
 */
bool isBookIdInList(const uint32_t id);

/**
 * @brief  get user choice from keyboard
 */
uint32_t getIdInput();

/**
 * @brief  get user choice from keyboard
 */
sBookDataType *getBookAdd();

#endif /* _BOOK_H_ */
