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
    clearStdinBuff();

    if ((INVALID_CHOICE == tempChoice) || ((int32_t)AC_INVALID < tempChoice))
    {
        userChoice = AC_INVALID;
    }
    else
    {
        userChoice = (eBookAcType)tempChoice;
    }

    /* printf("userChoice = %d\n", userChoice); */
    return userChoice;
}

void printfBookInfo(sBookDataType *pBook)
{
    if (NULL != pBook)
    {
        printf("====================BOOK_INFO===================\n");
        printf("ID = %d\n", pBook->id);
        printf("Title: %s\n", pBook->title);
        printf("Author: %s\n", pBook->author);
        if (BOOK_STATUS_AVAILABLE == pBook->status)
        {
            printf("Status: Available\n");
        }
        else
        {
            printf("Status: Borrowed\n");
        }
        printf("================================================\n");
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

    /* if the lib has not book, init the lib */
    if (NULL != *pBook)
    {
        tempBook = (*pBook);
        do
        {
            curBookTail = tempBook;
            tempBook = tempBook->pNextBook;
            /* code */
        } while (NULL != tempBook);
    }

    tempBook = (sBookDataType *)malloc(sizeof(sBookDataType));
    /* printf("tempBook = %p\n", *tempBook); */
    if (NULL == pBook)
    {
        *pBook = tempBook;
    }

    *tempBook = sampleBook;
    curBookTail->pNextBook = tempBook;
    tempBook->id = 0U;
    tempBook->status = BOOK_STATUS_AVAILABLE;
    tempBook->pNextBook = NULL;
    // printfBookInfo(tempBook);
}
