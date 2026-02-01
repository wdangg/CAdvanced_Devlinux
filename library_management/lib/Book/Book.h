#ifndef _BOOK_H_
#define _BOOK_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Log.h"
#include "Common.h"

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
} eBookSelAcc_t;

typedef struct sBookSelAcc
{
    eBookSelAcc_t id;
    const char *msg;
} sBookSelAcc_t;

static const sBookSelAcc_t sBookSellAcc[] = {
    {BOOK_ADD,          "Add a book"},
    {BOOK_DEL,          "Delete a book"},
    {BOOK_MODIFY_INFO,  "Modify book infomation"},
};

typedef enum
{
    BOOK_STATUS_AVAILABLE = 0,
    BOOK_STATUS_BORROWED,
    BOOK_STATUS_ALL
} eBookStatus_t;

typedef struct Book
{
    /* data */
    uint32_t id;
    uint8_t title[TITLE_SIZE];
    uint8_t author[AUTHOR_SIZE];
    eBookStatus_t status;
    uint8_t userBorrow[USER_NAME_SIZE];
    struct Book *pNextBook;
} sBookData_t;

/**
 * @brief  clear all stdin for the next process
 */
void clearStdinBuff(void);

/**
 * @brief  Print books filtered by status.
 * @param  status  Filter to apply (available, borrowed, or all).
 */
void printfBookInfo(eBookStatus_t status);

/**
 * @brief  Initialize a book structure with defaults.
 * @param  pBook  Pointer to book structure to initialize.
 */
void formatBook(sBookData_t *pBook);

/**
 * @brief  Add a book to the library.
 * @param  sampleBook  Book data to add (by value).
 */
void addBook(sBookData_t sampleBook);

/**
 * @brief  Delete a book by id.
 */
void delBook();

/**
 * @brief  Modify an existing book.
 */
void modifyBook();

/**
 * @brief  Edit book fields interactively.
 */
void editBookInfo(sBookData_t *pBook);

/**
 * @brief  Read book menu selection.
 */
eBookSelAcc_t bookSelectAcc();

/**
 * @brief  Print book menu.
 */
void printBookSelAcc();

/**
 * @brief  Find a book node by id.
 * @param  id        Book id to find.
 * @param  tempBook  Output pointer set to found node (if any).
 * @param  prevBook  Output pointer set to previous node (if any).
 * @return true if found, false otherwise.
 */
bool isBookIdInList(const uint32_t id, sBookData_t **tempBook, sBookData_t **prevBook);

/**
 * @brief  Check if a book title exists in library.
 * @param  sampleBook  Book to check (title is used for comparison).
 * @return true if a book with same title exists, false otherwise.
 */
bool isBookInLib(sBookData_t sampleBook);

/**
 * @brief  Read an integer id from stdin.
 * @return entered id (uint32_t).
 */
uint32_t getIdInput();

/**
 * @brief  Get pointer to library head.
 * @return pointer to first book in library.
 */
sBookData_t *getBookAdd();

/**
 * @brief  Free a book node.
 */
void freeBook(sBookData_t **pBook);

/**
 * @brief  Populate library with sample books for testing.
 */
void initLibraryForTest(void);

#endif /* _BOOK_H_ */
