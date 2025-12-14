#ifndef _UTILS_H_
#define _UTILS_H_

#include "Common.h"
#include "Book.h"
#include "User.h"
#include "Borrow.h"

void initLibraryForTest();

/**
 * @brief  Prompt and read book data from stdin.
 * @return populated book structure.
 */
sBookData_t getBookInput(void);

/**
 * @brief  Trim trailing newline from string.
 * @param  str  String to trim (in-place).
 */
void trimNewline(char *str);

/**
 * @brief  Book management menu handler.
 */
void bookMana();

/**
 * @brief  User management menu handler.
 */
void userMana();

/**
 * @brief  Borrow/return menu handler.
 */
void borrRetMana();

/**
 * @brief  Print all books.
 */
void printBooks();

/**
 * @brief  Prompt and read user data from stdin.
 */
sUserData_t getUserInput();

#endif /* _UTILS_H_ */