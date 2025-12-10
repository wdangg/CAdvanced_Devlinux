#include "Borrow.h"

void printBorrRetlAcc()
{
    printf("----------------------------------------------------------------\n");
    for (uint8_t i = 0; i < sizeof(sBorrRetSelAcc)/sizeof(sBorrRetSelAcc[0]); i++)
    {
        printf("\t%d. %s\n", sBorrRetSelAcc[i].id, sBorrRetSelAcc[i].msg);
    }
    printf("----------------------------------------------------------------\n");
    printf("Please choose the action you want:\n");
}

eBorrRetSelAccType borrRetSelectAcc()
{
    eBorrRetSelAccType eRet;
    uint32_t tempChoice;

    tempChoice = getchar();
    tempChoice = BORR_RET_CHAR_TO_NUM(tempChoice);
    /* printf("tempChoice = %d\n", tempChoice); */

    getchar(); /* clear stdin, there is a newline character still here */

    if ((uint32_t)BORR_RET_INVALID_ACC < tempChoice)
    {
        eRet = BORR_RET_INVALID_ACC;
    }
    else
    {
        eRet = (eBorrRetSelAccType)tempChoice;
    }
    printf("eRet = %d\n", eRet);
    return eRet;
}
