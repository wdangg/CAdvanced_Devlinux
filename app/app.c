#include "app.h"

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

    printAppInfo();
    inputUser = (eBookAcType)getUserChoice();

    do
    {
        /* code */
        if (AC_ADD_BOOK == inputUser)
        {
            printf("[ACTION] add a book into lib\n");
        }
        else if (AC_DEL_BOOK == inputUser)
        {
            printf("[ACTION] delete a book into lib\n");
        }
        else if (AC_INVALID == inputUser)
        {
            printf("[INFO] There is no action you want in list, please chosse angain\n");
        }
        /* update input user choice from keyboard */
        inputUser = (eBookAcType)getUserChoice();
    } while (AC_EXIT_APP != inputUser);

    printf("[INFO] Exit app\n");
    /* printf("[INFO] App layer\n"); */
} /* libManagement func */
