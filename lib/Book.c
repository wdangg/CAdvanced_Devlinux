#include "Book.h"

static sBookDataType *pLibrary = NULL;

static sBookDataType sample_1 = {
    .id = 1,
    .title = "De Men Phieu Luu Ky",
    .author = "To Hoai",
    .status = BOOK_STATUS_AVAILABLE,
    .pNextBook = NULL
};

static sBookDataType sample_2 = {
    .id = 2,
    .title = "Tat Den",
    .author = "Ngo Tat To",
    .status = BOOK_STATUS_AVAILABLE,
    .pNextBook = NULL
};

static sBookDataType sample_3 = {
    .id = 3,
    .title = "Lao Hac",
    .author = "Nam Cao",
    .status = BOOK_STATUS_BORROWED,
    .pNextBook = NULL
};

static sBookDataType sample_4 = {
    .id = 4,
    .title = "Vo Nhat",
    .author = "Kim Lan",
    .status = BOOK_STATUS_AVAILABLE,
    .pNextBook = NULL
};

static sBookDataType sample_5 = {
    .id = 5,
    .title = "Tuyen Kieu",
    .author = "Nguyen Du",
    .status = BOOK_STATUS_AVAILABLE,
    .pNextBook = NULL
};

void initLibraryForTest(void)
{
    sample_1.pNextBook = &sample_2;
    sample_2.pNextBook = &sample_3;
    sample_3.pNextBook = &sample_4;
    sample_4.pNextBook = &sample_5;
    sample_5.pNextBook = NULL;

    pLibrary = &sample_1;
}

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
    sBookDataType *tempBook = pLibrary;

    if (tempBook == NULL)
    {
        printf("There is no book in library.\n");
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

void addBook(sBookDataType sampleBook)
{
    sBookDataType *tempBook;
    sBookDataType *curBookTail;
    uint8_t temp;
    
    if (NULL != pLibrary)
    {
        curBookTail = pLibrary;
        while (NULL != (curBookTail->pNextBook))
        {
            curBookTail = curBookTail->pNextBook;
            /* code */
        }
    }

    tempBook = (sBookDataType *)malloc(sizeof(sBookDataType));
    /* printf("tempBook = %p\n", *tempBook); */

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


void delBook()
{
    sBookDataType *tempBook;
    sBookDataType *prevBook = NULL;
    bool found = false;
    uint32_t id;

    if (pLibrary == NULL)
    {
        printf("[ERROR] There is no book to delete\n");
    }
    else
    {
        printf("[BOOK] Enter the book id you wanna delete:\n");
        id = getIdInput();
        tempBook = pLibrary;
        if (true == isIdInList(id))
        {
            if (id == (tempBook->id))
            {
                pLibrary = tempBook->pNextBook;
                free(tempBook);
                printf("found book id, can deleteeeeeeeeee\n");
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

bool isIdInList(const uint32_t id)
{
    sBookDataType *tempBook = pLibrary;
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

void modifyBook()
{
    sBookDataType *tempBook;
    uint32_t id;


    if (pLibrary == NULL)
    {
        printf("[ERROR] There is no book, cannot modify\n");
    }
    else
    {
        printf("[BOOK] Enter the book id you wanna modify:\n");
        id = getIdInput();
        tempBook = pLibrary;
        if (true == isIdInList(id))
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

sBookDataType *getBookAdd()
{
    return (sBookDataType *)pLibrary;
}
