#include "Book.h"

void clearStdinBuff(void)
{
    int c;
    while ('\n' != (c = getchar()) && EOF != c)
    {
        /* do nothing untill the left buff was clean */
    }
}

eBookAcType getUserChoice(void)
{
    eBookAcType userChoice = 0;
    int32_t tempChoice = 0;

    tempChoice = getchar();
    tempChoice = CHAR_TO_NUM(tempChoice);
    /* printf("tempChoice = %d\n", tempChoice); */

    getchar(); /* clear stdin, there is a newline character still here */

    if ((INVALID_CHOICE == tempChoice) || ((int32_t)AC_INVALID < tempChoice))
    {
        userChoice = AC_INVALID;
    }
    else
    {
        userChoice = (eBookAcType)tempChoice;
    }

    /* printf("userChoice = %d\n", userChoice);  */
    return userChoice;
}

void printfBookInfo(sBookDataType *pBook)
{
    sBookDataType *tempBook;

    tempBook = pBook;

    if (NULL != tempBook)
    {
        while (NULL != tempBook)
        {
            /* code */
            printf("====================BOOK_INFO===================\n");
            printf("ID = %d\n", tempBook->id);
            printf("Title: %s\n", tempBook->title);
            printf("Author: %s\n", tempBook->author);
            if (BOOK_STATUS_AVAILABLE == tempBook->status)
            {
                printf("Status: Available\n");
            }
            else
            {
                printf("Status: Borrowed\n");
            }
            printf("================================================\n");
            tempBook = tempBook->pNextBook;
        }
    }
    else
    {
        printf("There is no book in library\n");
    }
}

void formatBook(sBookDataType *pBook)
{
    uint8_t temp = 0;

    if (NULL != pBook)
    {
        pBook->id = 0xFFFFu;
        for (temp = 0; temp < TITLE_SIZE; temp++)
        {
            pBook->title[temp] = 0;
        }
        for (temp = 0; temp < AUTHOR_SIZE; temp++)
        {
            pBook->author[temp] = 0;
        }
        pBook->status = BOOK_STATUS_EMPTY;
    }
}

void addBook(sBookDataType **pBook, sBookDataType sampleBook)
{
    sBookDataType *tempBook;
    sBookDataType *curBookTail;
    uint8_t temp;

    if (NULL != *pBook)
    {
        curBookTail = (*pBook);
        while (NULL != (curBookTail->pNextBook))
        {
            curBookTail = curBookTail->pNextBook;
            /* code */
        }
    }

    tempBook = (sBookDataType *)malloc(sizeof(sBookDataType));
    /* printf("tempBook = %p\n", *tempBook); */

    *tempBook = sampleBook;

    if (NULL == *pBook)
    {
        *pBook = tempBook;
        tempBook->id = 0u;
    }
    else
    {
        tempBook->id = ((curBookTail->id) + 1u);
        curBookTail->pNextBook = tempBook;
    }

    tempBook->status = BOOK_STATUS_AVAILABLE;
    tempBook->pNextBook = NULL;
    // printfBookInfo(tempBook);
}
