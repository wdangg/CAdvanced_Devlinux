#ifndef _UTILS_H_
#define _UTILS_H_

#include "Book.h"

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

#endif /* _UTILS_H_ */