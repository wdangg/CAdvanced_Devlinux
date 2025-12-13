#include "Borrow.h"

void printBorrRetlAcc()
{
    printf("----------------------------------------------------------------\n");
    for (uint8_t i = 0; i < sizeof(sBorrRetSelAcc)/sizeof(sBorrRetSelAcc[0]); i++)
    {
        printf("\t%d. %s\n", sBorrRetSelAcc[i].id, sBorrRetSelAcc[i].msg);
    }
    printf("----------------------------------------------------------------\n");
    LOG_INFO("Please choose the action you want:");
}

eBorrRetSelAcc_t borrRetSelAcc()
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

void borrRetBook(eBorrRetSelAcc_t eBorrOrRet)
{
    sUserData_t *tempUser;
    sUserData_t *prevUser;
    sBookData_t *tempBook;
    uint32_t id;
    bool isUserIdExist = false;

    tempUser = getUserAdd();

    /* the user must sign up before borrow book */
    if (NULL != tempUser)
    {
        tempBook = getBookAdd();
        if (NULL != tempBook)
        {
            printUserInfo();
            LOG_INFO("Please chose user id you wanna borrow or return book: ");
            id = getIdInput();
            
            isUserIdExist = isUserIdInList(id, &tempUser, &prevUser);
            if (true == isUserIdExist)
            {
                if (BORR_RET_BORROW == eBorrOrRet)
                {
                    borrBook(&tempUser);
                }
                else if (BORR_RET_RETURN == eBorrOrRet)
                {
                    returnBook();
                }
                else
                {
                    LOG_ERROR("Invalid eBorrOrRet, please check input parameter");
                }
            }
            else
            {
                LOG_ERROR("There is no user id in list, cannot process");
            }
        }
        else
        {
            LOG_ERROR("There is no book in library, cannot borrow");
        }
    }
    else
    {
        LOG_ERROR("There is no user information, please sign up to borrow");
    }
}

void borrBook(sUserData_t **tempUser)
{
    sBookData_t *tempBook = NULL;
    sBookData_t *prevBook = NULL;
    uint32_t id;
    uint8_t index;
    bool canBorrow = false;

    if (NULL != *tempUser)
    {
        if (true == canBorrBook(*tempUser, &index))
        {
            printfBookInfo(BOOK_STATUS_AVAILABLE);
            LOG_INFO("Please chose a book you wanna borrow");
            id = getIdInput();
            if (true == isBookIdInList(id, &tempBook, &prevBook))
            {
                tempBook->status = BOOK_STATUS_BORROWED;
                strcpy((*tempUser)->name, tempBook->userBorrow);
                (*tempUser)->pBookBorrowed[index] = tempBook;
            }
        }
    }
    else
    {
        LOG_ERROR("borrBook, invalid **tempUser");
    }
}

bool canBorrBook(sUserData_t *tempUser, uint8_t *index)
{
    bool retVal = false;
    uint8_t count = 0u;

    if (NULL != tempUser)
    {
        while ((USER_MAX_BOOK_CAN_BORROW > count) && (true != retVal))
        {
            if (NULL == (tempUser->pBookBorrowed[count]))
            {
                retVal = true;
                *index = count;
            }
            count++;
        }
        if (false == retVal)
        {
            LOG_ERROR("User borrowed max book, cannot borrow anymore");
        }
    }
    else
    {
        LOG_ERROR("invalid user pointer input");
    }

    return retVal;
}

void returnBook()
{

}
