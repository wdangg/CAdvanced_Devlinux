#include "Book.h"

eBookAcType getUserChoice(void)
{
    eBookAcType userChoice = 0;
    int tempChoice = 0;

    scanf("%d", &tempChoice);
    /* printf("tempChoice = %d\n", tempChoice); */
    userChoice = (eBookAcType)tempChoice;

    if (AC_INVALID <= userChoice)
    {
        userChoice = AC_INVALID;
    }
    /* printf("userChoice = %d\n", userChoice); */
    return userChoice;
}

void addBook(sBookDataType *pBook)
{
    sBookDataType tempBook = *pBook;
}
