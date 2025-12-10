#ifndef _UTILS_H_
#define _UTILS_H_

#include "Book.h"
#include "User.h"

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
sBookDataType getBookInput(void);

/**
 * @brief  remove the newline char when using fgets
 *
 */
void trimNewline(char *str);

/**
 * @brief  remove the newline char when using fgets
 *
 */
void midBookMana();

/**
 * @brief  remove the newline char when using fgets
 *
 */
void midUserMana();

/**
 * @brief  remove the newline char when using fgets
 *
 */
void midBorrMana();

/**
 * @brief  remove the newline char when using fgets
 *
 */
void midPrintBooks();

/**
 * @brief  get user choice from keyboard
 */
sUserDataType midGetUserInput();

#endif /* _UTILS_H_ */