#include <inc.h>

int main(void)
{
    eLibMana_t inputUser = 0;

    /* init some book, users for test */
    initLibraryForTest();
    initUserForTest();

    LOG_INFO("Start the program");
    do
    {
        printAppInfo();
        inputUser = getUserChoice();

        if (LIB_BOOK_INFO_MANA == inputUser)
        {
            /* LOG_PRINT("[LIB_MANA] Library management"); */
            bookMana();
        }
        else if (LIB_USER_MANA == inputUser)
        {
            /* LOG_PRINT("[LIB_MANA] User management"); */
            userMana();
        }
        else if (LIB_BORR_RET_MANA == inputUser)
        {
            /* LOG_PRINT("[LIB_MANA] Borrow - Return books management"); */
            borrRetMana();
        }
        else if (LIB_FIND_BOOK == inputUser)
        {
            /* LOG_PRINT("[LIB_MANA] Find a book"); */

        }
        else if (LIB_PRINT_BOOKS == inputUser)
        {
            /* LOG_PRINT("[LIB_MANA] Prinf all books infomation"); */
            printBooks();
        }
        else if (LIB_PRINT_USERS == inputUser)
        {
            /* LOG_PRINT("[LIB_MANA] Prinf all users infomation"); */
            printUserInfo();
        }
        else if (LIB_EXIT == inputUser)
        {
            LOG_PRINT("[EXIT] Exit the program");
        }
    } while (LIB_EXIT != inputUser);

    /* LOG_INFO("App layer"); */
    LOG_INFO("Done");
}

eLibMana_t getUserChoice(void)
{
    eLibMana_t userChoice = 0;
    uint32_t tempChoice = 0;

    tempChoice = getchar();
    tempChoice = LIB_CHAR_TO_NUM(tempChoice);
    /* LOG_PRINT("tempChoice = %d\n", tempChoice); */

    getchar(); /* clear stdin, there is a newline character still here */

    if ((uint32_t)LIB_INVALID_CHOICE < tempChoice)
    {
        userChoice = LIB_INVALID_CHOICE;
    }
    else
    {
        userChoice = (eLibMana_t)tempChoice;
    }

    /* LOG_PRINT("userChoice = %d\n", userChoice);  */
    return userChoice;
}

void printAppInfo(void)
{
    printf("----------------------------------------------------------------\n");
    for (size_t i = 0; i < sizeof(sMenuList)/sizeof(sMenuList[0]); i++)
    {
        printf("\t%d. %s\n", sMenuList[i].id, sMenuList[i].msg);
    }
    printf("----------------------------------------------------------------\n");
    LOG_INFO("Please choose the action you want:");
}
