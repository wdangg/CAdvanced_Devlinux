#include "app.h"

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
    
    do
    {
        printAppInfo();
        inputUser = getUserChoice();

        if (LIB_BOOK_INFO_MANA == inputUser)
        {
            /* printf("[LIB_MANA] Library management\n"); */
            midBookMana();
        }
        else if (LIB_USER_MANA == inputUser)
        {
            /* printf("[LIB_MANA] User management\n"); */
            midUserMana();
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
            midPrintBooks();
        }
        else if (LIB_EXIT == inputUser)
        {
            printf("[EXIT] Exit the program\n");
        }
    } while (LIB_EXIT != inputUser);

    /* printf("[INFO] App layer\n"); */
} /* libManagement func */
