#ifndef _UTILS_H_
#define _UTILS_H_

#include "Common.h"
#include "Book.h"
#include "User.h"
#include "Borrow.h"

void initLibraryForTest();

/**
 * @brief  Deletes a book from the list.
 *
 * Returns BOOK_SUCCESS_DELETE on success,
 * BOOK_DELETE_FAILED_NOT_FOUND if the book is missing,
 * or BOOK_DELETE_FAILED_BORROWED if the book is currently borrowed.
 *
 * @param books   Array of all books.
 * @param n       Pointer to the number of books.
 *
 * @return BookRetCode_t  Status code of the delete operation.
 */
sBookData_t getBookInput(void);

/**
 * @brief  remove the newline char when using fgets
 *
 */
void trimNewline(char *str);

/**
 * @brief  remove the newline char when using fgets
 *
 */
void BookMana();

/**
 * @brief  remove the newline char when using fgets
 *
 */
void UserMana();

/**
 * @brief  remove the newline char when using fgets
 *
 */
void BorrRetMana();

/**
 * @brief  remove the newline char when using fgets
 *
 */
void PrintBooks();

/**
 * @brief  get user choice from keyboard
 */
sUserData_t getUserInput();

#endif /* _UTILS_H_ */