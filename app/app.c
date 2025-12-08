#include "app.h"

sBookDataType *pLibrary = NULL;

void printAppInfo(void)
{
    printf("-----------------------------------\n");
    printf("%d. Exit\n", AC_EXIT_APP);
    printf("%d. Add a book into library\n", AC_ADD_BOOK);
    printf("%d. Delete a book from library\n", AC_DEL_BOOK);
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
        /* code */
        if (AC_ADD_BOOK == inputUser)
        {
            printf("[ACTION] add a book into lib\n");
            tempBook = getBookInput();
            addBook(&pLibrary, tempBook);
            printfBookInfo(pLibrary);
        }
        else if (AC_DEL_BOOK == inputUser)
        {
            printf("[ACTION] delete a book into lib\n");
        }
        else if (AC_INVALID == inputUser)
        {
            printf("[INFO] There is no action you want in list, please chosse again: \n");
        }
        /* code */
    } while (AC_EXIT_APP != inputUser);

    /* printf("[INFO] App layer\n"); */
} /* libManagement func */
