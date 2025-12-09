#ifndef _APP_H_
#define _APP_H_

#include <stdio.h>
#include <stdint.h>
#include "Book.h"
#include "Utils.h"

typedef struct MenuList
{
    eBookAcType id;
    const char *msg;
} sMenuListType;

static const sMenuListType sMenuList[] = {
    {AC_EXIT_APP,               "Exit"},
    {AC_ADD_BOOK,               "Add a book into library"},
    {AC_DEL_BOOK,               "Delete a book from library"},
    {AC_PRINT_BOOK_INFO,        "Print all books"}
};

/**
 * @brief  the main func to management the library
 */
void libManagement(void);

/**
 * @brief  print guide to use application
 */
void printAppInfo(void);

#endif /* _APP_H_ */