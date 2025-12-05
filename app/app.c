#include "app.h"

void printAppInfo(void)
{
    printf("-----------------------------------\n");
    printf("1. Add a book into library\n");
    printf("0. Exit\n");
    printf("-----------------------------------\n");
    printf("Please chose the action you want:\n");
}

void libManagement(void)
{
    uint8_t inputUser;
    printf("Your choice: ");
    scanf("%d", &inputUser);

    if (0 == inputUser)
    {
        printf("[00000000000000000]");
    }
    else
    {
        printf("[%d]\n", inputUser);
    }

    printf("[INFO] Exit app");
    /* printf("[INFO] App layer\n"); */
} /* libManagement func */
