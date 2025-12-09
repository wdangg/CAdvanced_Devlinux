#include "app.h"

sBookDataType *pLibrary = NULL;

eLibManaType getUserChoice(void)
{
    eLibManaType userChoice = 0;
    uint32_t tempChoice = 0;

    tempChoice = getchar();
    tempChoice = LIB_CHAR_TO_NUM(tempChoice);
    /* printf("tempChoice = %d\n", tempChoice); */

    getchar(); /* clear stdin, there is a newline character still here */

    if ((uint32_t)LIB_INVALID_CHOICE < tempChoice)
    {
        userChoice = LIB_INVALID_CHOICE;
    }
    else
    {
        userChoice = (eLibManaType)tempChoice;
    }

    /* printf("userChoice = %d\n", userChoice);  */
    return userChoice;
}

void printAppInfo(void)
{
    printf("----------------------------------------------------------------\n");
    for (int i = 0; i < sizeof(sMenuList)/sizeof(sMenuList[0]); i++)
    {
        printf("\t%d. %s\n", sMenuList[i].id, sMenuList[i].msg);
    }
    printf("----------------------------------------------------------------\n");
    printf("Please choose the action you want:\n");
}

void libManagement(void)
{
    eLibManaType inputUser = 0;
    sBookDataType tempBook;
    eBookSelAccType eBookSelAcc;

/*     sBookDataType sample_1 = {
        .id = 1,
        .title = "De Men Phieu Luu Ky",
        .author = "To Hoai",
        .status = BOOK_STATUS_AVAILABLE,
        .pNextBook = NULL
    };

    sBookDataType sample_2 = {
        .id = 2,
        .title = "Tat Den",
        .author = "Ngo Tat To",
        .status = BOOK_STATUS_AVAILABLE,
        .pNextBook = NULL
    };

    sBookDataType sample_3 = {
        .id = 3,
        .title = "Lao Hac",
        .author = "Nam Cao",
        .status = BOOK_STATUS_BORROWED,
        .pNextBook = NULL
    };

    sBookDataType sample_4 = {
        .id = 4,
        .title = "Vo Nhat",
        .author = "Kim Lan",
        .status = BOOK_STATUS_AVAILABLE,
        .pNextBook = NULL
    };

    sBookDataType sample_5 = {
        .id = 5,
        .title = "Tuyen Kieu",
        .author = "Nguyen Du",
        .status = BOOK_STATUS_AVAILABLE,
        .pNextBook = NULL
    };

    sample_1.pNextBook = &sample_2;
    sample_2.pNextBook = &sample_3;
    sample_3.pNextBook = &sample_4;
    sample_4.pNextBook = &sample_5;
    sample_5.pNextBook = NULL;

    pLibrary = &sample_1; */

    do
    {
        printAppInfo();
        inputUser = getUserChoice();

        if (LIB_BOOK_INFO_MANA == inputUser)
        {
            /* printf("[LIB_MANA] Library management\n"); */
            printBookSelAcc();
            eBookSelAcc = bookSelectAcc();
            if (BOOK_ADD == eBookSelAcc)
            {
                tempBook = getBookInput();
                addBook(&pLibrary, tempBook);
            }
            else if (BOOK_DEL == eBookSelAcc)
            {
                printfBookInfo(pLibrary);
                delBook(&pLibrary);
            }
        }
        else if (LIB_USER_MANA == inputUser)
        {
            printf("[LIB_MANA] User management\n");
        }
        else if (LIB_BORR_RET_MANA == inputUser)
        {
            printf("[LIB_MANA] Borrow - Return books management\n");
        }
        else if (LIB_FIND_BOOK == inputUser)
        {
            printf("[LIB_MANA] Find a book\n");
        }
        else if (LIB_PRINT_BOOKS == inputUser)
        {
            /* printf("[LIB_MANA] Prinf all books infomation\n"); */
            printfBookInfo(pLibrary);
        }
        else if (LIB_EXIT == inputUser)
        {
            printf("[EXIT] Exit the program\n");
        }
    } while (LIB_EXIT != inputUser);

    /* printf("[INFO] App layer\n"); */
} /* libManagement func */
