#include "Book.h"

static sBookData_t *pLibrary = NULL;

void clearStdinBuff(void)
{
    int c;
    while ('\n' != (c = getchar()) && EOF != c)
    {
        /* do nothing untill the left buff was clean */
    }
}

void printfBookInfo()
{
    sBookData_t *tempBook = pLibrary;

    if (tempBook == NULL)
    {
        LOG_PRINT("There is no book in library.");
    }
    else
    {
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
}

void formatBook(sBookData_t *pBook)
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

void addBook(sBookData_t sampleBook)
{
    sBookData_t *tempBook;
    sBookData_t *curBookTail;
    uint8_t temp;
    bool isBookExist = false;

    isBookExist = isBookInLib(sampleBook);

    if (false == isBookExist)
    {
        if (NULL != pLibrary)
        {
            curBookTail = pLibrary;
            while (NULL != (curBookTail->pNextBook))
            {
                curBookTail = curBookTail->pNextBook;
            }
        }
    
        tempBook = (sBookData_t *)malloc(sizeof(sBookData_t));
        /* LOG_PRINT("tempBook = %p\n", *tempBook); */
    
        *tempBook = sampleBook;
    
        if (NULL == pLibrary)
        {
            pLibrary = tempBook;
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
}

void delBook()
{
    sBookData_t *tempBook;
    sBookData_t *prevBook = NULL;
    bool found = false;
    uint32_t id;

    if (pLibrary == NULL)
    {
        LOG_ERROR("There is no book to delete");
    }
    else
    {
        LOG_PRINT("[BOOK] Enter the book id you wanna delete:");
        id = getIdInput();
        tempBook = pLibrary;
        if (true == isBookIdInList(id))
        {
            if (id == (tempBook->id))
            {
                pLibrary = tempBook->pNextBook;
                freeBook(&tempBook);
                LOG_PRINT("found book id, can deleteeeeeeeeee");
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
                freeBook(&tempBook);
            }
        }
        else
        {
            LOG_ERROR("Invalid id");
        }
    }
}

bool isBookIdInList(const uint32_t id)
{
    sBookData_t *tempBook = pLibrary;
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
        LOG_ERROR("isBookIdInList");
    }
    return bRet;
}

bool isBookInLib(sBookData_t sampleBook)
{
    bool retVal = false;
    sBookData_t *tempBook = pLibrary;

    if (NULL != pLibrary)
    {
        while (NULL != tempBook)
        {
            if (0u == strcmp(sampleBook.title, tempBook->title))
            {
                retVal = true;
                /* set tempBook to exit while loop, dont use break */
                tempBook = NULL;
            }
            else
            {
                tempBook = tempBook->pNextBook;
            }
        }
    }

    return retVal;
}

void editBookInfo(sBookData_t *pBook)
{
    uint8_t buff[0xFF];

    LOG_PRINT("=== EDIT BOOK INFO ===");
    LOG_PRINT("Current title : %s\n", pBook->title);
    LOG_PRINT("Current author: %s\n", pBook->author);

    /* -------- Edit Title -------- */
    LOG_PRINT("Enter new title (Enter to skip): ");
    fgets((char *)buff, sizeof(buff), stdin);

    buff[strcspn((char *)buff, "\n")] = 0;

    bool skipTitle = false;

    if (strlen((char *)buff) == 0)
    {
        skipTitle = true;
    }
    else
    {
        strcpy((char *)pBook->title, (char *)buff);
    }

    /* -------- Edit Author -------- */
    LOG_PRINT("Enter new author (Enter to skip):");

    fgets((char *)buff, sizeof(buff), stdin);
    buff[strcspn((char *)buff, "\n")] = 0;

    if (strlen((char *)buff) == 0)
    {
        if (skipTitle)
        {
            LOG_INFO("No changes were made");
            return;
        }
        LOG_INFO("Only title was updated.");
    }
    else
    {
        strcpy((char *)pBook->author, (char *)buff);
        LOG_INFO("Both title and author updated.");
    }
}

void modifyBook()
{
    sBookData_t *tempBook;
    uint32_t id;

    if (NULL == pLibrary)
    {
        LOG_ERROR("There is no book, cannot modify");
    }
    else
    {
        LOG_PRINT("[BOOK] Enter the book id you wanna modify:");
        id = getIdInput();
        tempBook = pLibrary;
        if (true == isBookIdInList(id))
        {
            /* LOG_PRINT("found book id, can modify"); */
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
            LOG_ERROR("Invalid book id");
        }
    }
}

void printBookSelAcc()
{
    printf("----------------------------------------------------------------\n");
    for (uint8_t i = 0; i < sizeof(sBookSellAcc) / sizeof(sBookSellAcc[0]); i++)
    {
        printf("\t%d. %s\n", sBookSellAcc[i].id, sBookSellAcc[i].msg);
    }
    printf("----------------------------------------------------------------\n");
    printf("Please choose the action you want:");
}

eBookSelAcc_t bookSelectAcc()
{
    eBookSelAcc_t eRet;
    uint32_t tempChoice;

    tempChoice = getchar();
    tempChoice = BOOK_CHAR_TO_NUM(tempChoice);
    /* LOG_PRINT("tempChoice = %d\n", tempChoice); */

    getchar(); /* clear stdin, there is a newline character still here */

    if ((uint32_t)BOOK_INVALID_SEL < tempChoice)
    {
        eRet = BOOK_INVALID_SEL;
    }
    else
    {
        eRet = (eBookSelAcc_t)tempChoice;
    }
    /* LOG_PRINT("eRet = %d\n", eRet); */
    return eRet;
}

sBookData_t *getBookAdd()
{
    return (sBookData_t *)pLibrary;
}

void freeBook(sBookData_t **pBook)
{
    if (NULL != *pBook)
    {
        free(*pBook);
        *pBook = NULL;
    }
}

void initLibraryForTest(void)
{
    sBookData_t sampleBook;

    /* BOOK 1 */
    /* sampleBook.id = 1; */
    strcpy((char *)sampleBook.title, "De Men Phieu Luu Ky");
    strcpy((char *)sampleBook.author, "To Hoai");
    /* sampleBook.status = BOOK_STATUS_AVAILABLE;
    sampleBook.pNextBook = NULL; */
    addBook(sampleBook);

    /* BOOK 2 */
    /* sampleBook.id = 2; */
    strcpy((char *)sampleBook.title, "Tat Den");
    strcpy((char *)sampleBook.author, "Ngo Tat To");
    /* sampleBook.status = BOOK_STATUS_AVAILABLE;
    sampleBook.pNextBook = NULL; */
    addBook(sampleBook);

    /* BOOK 3  */
    /* sampleBook.id = 3; */
    strcpy((char *)sampleBook.title, "Lao Hac");
    strcpy((char *)sampleBook.author, "Nam Cao");
    /* sampleBook.status = BOOK_STATUS_BORROWED;
    sampleBook.pNextBook = NULL; */
    addBook(sampleBook);

    /* BOOK 4  */
    /* sampleBook.id = 4; */
    strcpy((char *)sampleBook.title, "Vo Nhat");
    strcpy((char *)sampleBook.author, "Kim Lan");
    /* sampleBook.status = BOOK_STATUS_AVAILABLE;
    sampleBook.pNextBook = NULL; */
    addBook(sampleBook);

    /*  BOOK 5  */
    /* sampleBook.id = 5; */
    strcpy((char *)sampleBook.title, "Truyen Kieu");
    strcpy((char *)sampleBook.author, "Nguyen Du");
    /* sampleBook.status = BOOK_STATUS_AVAILABLE;
    sampleBook.pNextBook = NULL; */
    addBook(sampleBook);

}
