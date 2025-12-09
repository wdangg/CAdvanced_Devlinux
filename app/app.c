#include "app.h"

sBookDataType *pLibrary = NULL;

void printAppInfo(void)
{
    printf("-----------------------------------\n");
    for (int i = 0; i < sizeof(sMenuList)/sizeof(sMenuList[0]); i++)
    {
        printf("%d. %s\n", sMenuList[i].id, sMenuList[i].msg);
    }
    printf("-----------------------------------\n");
    printf("Please choose the action you want:\n");
}

void libManagement(void)
{
    eBookAcType inputUser = 0;
    sBookDataType tempBook;

    do
    {
        printAppInfo();
        inputUser = getUserChoice();

        if (AC_ADD_BOOK == inputUser)
        {
            printf("[ACTION] add a book into lib\n");
            tempBook = getBookInput();
            addBook(&pLibrary, tempBook);
        }
        else if (AC_DEL_BOOK == inputUser)
        {
            printf("[ACTION] delete a book into lib\n");
        }
        else if (AC_PRINT_BOOK_INFO == inputUser)
        {
            printfBookInfo(pLibrary);
        }
        else if (AC_INVALID == inputUser)
        {
            printf("[INFO] There is no action you want in list, please chosse again: \n");
        }
        else if (AC_EXIT_APP == inputUser)
        {
            printf("[EXIT] Exit the program\n");
        }
    } while (AC_EXIT_APP != inputUser);

    /* printf("[INFO] App layer\n"); */
} /* libManagement func */
