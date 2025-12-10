#include "User.h"

sUserDataType *pUser = NULL;

void printUserlAcc()
{
    printf("----------------------------------------------------------------\n");
    for (uint8_t i = 0; i < sizeof(sUserSelAcc)/sizeof(sUserSelAcc[0]); i++)
    {
        printf("\t%d. %s\n", sUserSelAcc[i].id, sUserSelAcc[i].msg);
    }
    printf("----------------------------------------------------------------\n");
    printf("Please choose the action you want:\n");
}

eUserSelAccType userSelectAcc()
{
    eUserSelAccType eRet;
    uint32_t tempChoice;

    tempChoice = getchar();
    tempChoice = USER_CHAR_TO_NUM(tempChoice);
    /* printf("tempChoice = %d\n", tempChoice); */

    getchar(); /* clear stdin, there is a newline character still here */

    if ((uint32_t)USER_INVALID_ACC < tempChoice)
    {
        eRet = USER_INVALID_ACC;
    }
    else
    {
        eRet = (eUserSelAccType)tempChoice;
    }
    /* printf("eRet = %d\n", eRet);  */
    return eRet;
}

void printUserInfo()
{
    sUserDataType *tempUser = pUser;
    uint32_t totalBookBorrowed;

    if (tempUser == NULL)
    {
        printf("There is no user in library.\n");
    }
    else
    {
        printf("====================================================================================\n");
        printf("| %-2s | %-25s | %-25s |\n",
               "ID", "NAME", "BORROWED");
        printf("------------------------------------------------------------------------------------\n");
    
        while (tempUser != NULL)
        {
            totalBookBorrowed = countBookBorrowed(tempUser);
            printf("| %-2d | %-25s | %-25d |\n",
                   tempUser->id,
                   tempUser->name,
                   totalBookBorrowed);
    
            tempUser = tempUser->pNextUser;
        }
    
        printf("====================================================================================\n");
    }
}

sUserDataType *getUserAdd()
{
    return (sUserDataType *)pUser;
}

void addUser(sUserDataType sampleUser)
{
    sUserDataType *tempUser;
    sUserDataType *curUserTail;
    uint8_t temp;
    
    if (NULL != pUser)
    {
        curUserTail = pUser;
        while (NULL != (curUserTail->pNextUser))
        {
            curUserTail = curUserTail->pNextUser;
            /* code */
        }
    }

    tempUser = (sUserDataType *)malloc(sizeof(sUserDataType));
    /* printf("tempUser = %p\n", *tempUser); */

    *tempUser = sampleUser;

    if (NULL == pUser)
    {
        pUser = tempUser;
        tempUser->id = 0u;
    }
    else
    {
        tempUser->id = ((curUserTail->id) + 1u);
        curUserTail->pNextUser = tempUser;
    }

    for (uint8_t i = 0; i < USER_MAX_BOOK_CAN_BORROW; i++)
    {
        tempUser->pBookBorrowed[i] = NULL;
    }
    tempUser->pNextUser = NULL;
    /* printUserInfo(); */
}

void formatUser(sUserDataType *pSample)
{
    uint8_t temp = 0;

    if (NULL != pSample)
    {
        pSample->id = 0xFFFFu;
        for (temp = 0; temp < USER_NAME_SIZE; temp++)
        {
            pSample->name[temp] = 0;
        }
        memset(pSample->pBookBorrowed, NULL, sizeof(pSample->pBookBorrowed));
    }
}

uint32_t countBookBorrowed(sUserDataType *sampleUser)
{
    uint32_t retVal = 0u;

    for (uint8_t i = 0; i < USER_MAX_BOOK_CAN_BORROW; i++)
    {
        if (NULL != sampleUser->pBookBorrowed[i])
        {
            retVal++;
        }
    }

    return retVal;
}

void delUser()
{
    sUserDataType *tempUser;
    sUserDataType *prevUser = NULL;
    bool found = false;
    uint32_t id;

    if (pUser == NULL)
    {
        printf("[ERROR] There is no book to delete\n");
    }
    else
    {
        printf("[BOOK] Enter the book id you wanna delete:\n");
        id = getIdInput();
        tempUser = pUser;
        if (true == isUserIdInList(id))
        {
            if (id == (tempUser->id))
            {
                pUser = tempUser->pNextUser;
                free(tempUser);
                printf("found book id, can deleteeeeeeeeee\n");
            }
            else
            {
                while (id != tempUser->id)
                {
                    prevUser = tempUser;
                    tempUser = tempUser->pNextUser;
                }

                if (NULL == tempUser->pNextUser)
                {
                    prevUser->pNextUser = NULL;
                }
                else
                {
                    prevUser->pNextUser = tempUser->pNextUser;
                }
                free(tempUser);
            }
        }
        else
        {
            printf("[ERROR] Invalid id\n");
        }
    }
}

bool isUserIdInList(const uint32_t id)
{
    sUserDataType *tempUser = pUser;
    bool bRet = false;

    if (NULL != tempUser)
    {
        while (NULL != tempUser)
        {
            if (id == tempUser->id)
            {
                bRet = true;
            }
            tempUser = tempUser->pNextUser;
        }
    }
    else
    {
        printf("[ERROR] isUserIdInList\n");
    }
    return bRet;
}
