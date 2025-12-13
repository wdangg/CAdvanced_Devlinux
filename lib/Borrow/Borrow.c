#include "Borrow.h"

void printBorrRetlAcc()
{
    printf("----------------------------------------------------------------\n");
    for (uint8_t i = 0; i < sizeof(sBorrRetSelAcc)/sizeof(sBorrRetSelAcc[0]); i++)
    {
        printf("\t%d. %s\n", sBorrRetSelAcc[i].id, sBorrRetSelAcc[i].msg);
    }
    printf("----------------------------------------------------------------\n");
    printf("Please choose the action you want:");
}

eBorrRetSelAcc_t borrRetSelectAcc()
{
    eBorrRetSelAcc_t eRet;
    uint32_t tempChoice;

    tempChoice = getchar();
    tempChoice = BORR_RET_CHAR_TO_NUM(tempChoice);
    /* LOG_PRINT("tempChoice = %d\n", tempChoice); */

    getchar(); /* clear stdin, there is a newline character still here */

    if ((uint32_t)BORR_RET_INVALID_ACC < tempChoice)
    {
        eRet = BORR_RET_INVALID_ACC;
    }
    else
    {
        eRet = (eBorrRetSelAcc_t)tempChoice;
    }
    /* LOG_PRINT("eRet = %d\n", eRet); */
    return eRet;
}

void borrRetBook()
{
    sUserData_t *tempUser;
    sBookData_t *tempBook;

    initLibraryForTest();

    tempUser = getUserAdd();

    /* the user must sign up before borrow book */
    if (NULL == tempUser)
    {
        LOG_ERROR("There is no user information, please sign up to borrow");
    }
    else
    {
        tempBook = getBookAdd();
        if (NULL == tempBook)
        {
            LOG_ERROR("There is no book in library, cannot borrow");
        }
        else
        {
            printUserInfo();

        }
    }
}
