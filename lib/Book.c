#include "Book.h"

void clearStdinBuff(void)
{
    int c;
    while ('\n' != (c = getchar()) && EOF != c)
    {
        /* do nothing untill the left buff was clean */
    }
}

void printfBookInfo(sBookDataType *pBook)
{
    sBookDataType *tempBook = pBook;

    if (tempBook == NULL)
    {
        printf("There is no book in library.\n");
        return;
    }

    printf("====================================================================================\n");
    printf("| %-2s | %-25s | %-25s | %-10s |\n",
           "ID", "TITLE", "AUTHOR", "STATUS");
    printf("------------------------------------------------------------------------------------\n");

    while (tempBook != NULL)
    {
        printf("| %-2d | %-25s | %-25s | %-10s |\n",
               tempBook->id,
               tempBook->title,
               tempBook->author,
               (tempBook->status == BOOK_STATUS_AVAILABLE) ? "Available" : "Borrowed");

        tempBook = tempBook->pNextBook;
    }

    printf("====================================================================================\n");
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
    /* printfBookInfo(tempBook); */
}

uint32_t getIdInput(void)
{
    uint32_t retVal = 0;
    uint8_t buff[0xFF];

    if (fgets((char*)buff, sizeof(buff), stdin) != NULL)
    {
        retVal = (uint32_t)strtoul((char*)buff, NULL, 10);
    }

    return retVal;
}


void delBook(sBookDataType **pBook)
{
    sBookDataType *tempBook;
    sBookDataType *prevBook = NULL;
    bool found = false;
    uint32_t id;

    if (*pBook == NULL)
    {
        printf("[ERROR] There is no book to delete\n");
    }
    else
    {
        printf("[BOOK] Enter the book id you wanna delete:\n");
        id = getIdInput();
        tempBook = *pBook;
        if (true == isIdInList(tempBook, id))
        {
            /* printf("found book id, can deleteeeeeeeeee\n"); */
            if (id == (tempBook->id))
            {
                *pBook = tempBook->pNextBook;
                free(tempBook);
            }
            else
            {
                while (id != tempBook->id)
                {
                    prevBook = tempBook;
                    tempBook = tempBook->pNextBook;
                }

                if (NULL == tempBook->pNextBook)
                {
                    prevBook->pNextBook = NULL;
                }
                else
                {
                    prevBook->pNextBook = tempBook->pNextBook;
                }
                free(tempBook);
            }
        }
        else
        {
            printf("[ERROR] Invalid id\n");
        }
    }
}

bool isIdInList(sBookDataType *pBook, const uint32_t id)
{
    sBookDataType *tempBook = pBook;
    bool bRet = false;

    if (NULL != tempBook)
    {
        while (NULL != tempBook)
        {
            if (id == tempBook->id)
            {
                bRet = true;
            }
            tempBook = tempBook->pNextBook;
        }
    }
    else
    {
        printf("[ERROR] isIdInList\n");
    }
    return bRet;
}

void editBookInfo(sBookDataType *pBook)
{
    uint8_t buff[0xFF];

    printf("=== EDIT BOOK INFO ===\n");
    printf("Current title : %s\n", pBook->title);
    printf("Current author: %s\n", pBook->author);

    /* -------- Edit Title -------- */
    printf("Enter new title (Enter to skip): ");
    fgets((char*)buff, sizeof(buff), stdin);

    buff[strcspn((char*)buff, "\n")] = 0;

    bool skipTitle = false;

    if (strlen((char*)buff) == 0)
    {
        skipTitle = true;
    }
    else
    {
        strcpy((char*)pBook->title, (char*)buff);
    }

    /* -------- Edit Author -------- */
    printf("Enter new author (Enter to skip):");

    fgets((char*)buff, sizeof(buff), stdin);
    buff[strcspn((char*)buff, "\n")] = 0;

    if (strlen((char*)buff) == 0)
    {
        if (skipTitle)
        {
            printf("No changes were made.\n");
            return;
        }
        printf("Only title was updated.\n");
    }
    else
    {
        strcpy((char*)pBook->author, (char*)buff);
        printf("Both title and author updated.\n");
    }
}

void modifyBook(sBookDataType **pBook)
{
    sBookDataType *tempBook;
    uint32_t id;


    if (*pBook == NULL)
    {
        printf("[ERROR] There is no book, cannot modify\n");
    }
    else
    {
        printf("[BOOK] Enter the book id you wanna modify:\n");
        id = getIdInput();
        tempBook = *pBook;
        if (true == isIdInList(tempBook, id))
        {
            /* printf("found book id, can modify\n"); */
            if (id != (tempBook->id))
            {
                while (id != tempBook->id)
                {
                    tempBook = tempBook->pNextBook;
                }
            }
            editBookInfo(tempBook);
        }
        else
        {
            printf("[ERROR] Invalid id\n");
        }
    }
}

void printBookSelAcc()
{
    printf("----------------------------------------------------------------\n");
    for (uint8_t i = 0; i < sizeof(sBookSellAcc)/sizeof(sBookSellAcc[0]); i++)
    {
        printf("\t%d. %s\n", sBookSellAcc[i].id, sBookSellAcc[i].msg);
    }
    printf("----------------------------------------------------------------\n");
    printf("Please choose the action you want:\n");
}

eBookSelAccType bookSelectAcc()
{
    eBookSelAccType eRet;
    uint32_t tempChoice;

    tempChoice = getchar();
    tempChoice = BOOK_CHAR_TO_NUM(tempChoice);
    /* printf("tempChoice = %d\n", tempChoice); */

    getchar(); /* clear stdin, there is a newline character still here */

    if ((uint32_t)BOOK_INVALID_SEL < tempChoice)
    {
        eRet = BOOK_INVALID_SEL;
    }
    else
    {
        eRet = (eBookSelAccType)tempChoice;
    }
    /* printf("eRet = %d\n", eRet); */
    return eRet;
}
