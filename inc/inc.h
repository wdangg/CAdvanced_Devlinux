#ifndef _INCLUDE_H_
#define _INCLUDE_H_

#include <stdio.h>
#include <stdio.h>
#include <stdint.h>
#include "Book.h"
#include "User.h"
#include "Utils.h"

#define LIB_CHAR_TO_NUM(x) (((x) >= '0' && (x) <= '9') ? ((x) - '0') : LIB_INVALID_CHOICE)

typedef enum LibMana
{
    LIB_EXIT,
    LIB_BOOK_INFO_MANA,
    LIB_USER_MANA,
    LIB_BORR_RET_MANA,
    LIB_FIND_BOOK,
    LIB_PRINT_BOOKS,
    LIB_INVALID_CHOICE
} eLibMana_t;

typedef struct MenuList
{
    eLibMana_t id;
    const char *msg;
} sMenuList_t;

static const sMenuList_t sMenuList[] = {
    {LIB_EXIT,                   "Exit"},
    {LIB_BOOK_INFO_MANA,         "Book infomation management"},
    {LIB_USER_MANA,              "User management"},
    {LIB_BORR_RET_MANA,          "Book borrow management"},
    {LIB_FIND_BOOK,              "Find a book"},
    {LIB_PRINT_BOOKS,            "Print all books"}
};

/**
 * @brief  the main func to management the library
 */
void libManagement(void);

/**
 * @brief  print guide to use application
 */
void printAppInfo(void);

/**
 * @brief  get user choice from keyboard
 */
eLibMana_t getUserChoice(void);

#endif /* _INCLUDE_H_ */
