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

void addUser(sUserDataType sampleUser)
{
    sUserDataType *tempUser;
    sUserDataType *curUserTail = pUser;
    sUserDataType *checker = pUser;

    bool isExist = false;

    /* ==========================
       Check if user already exist
       ========================== */
    while (NULL != checker)
    {
        if (0 == strcmp((char*)checker->name, (char*)sampleUser.name))
        {
            isExist = true;
        }
        if (NULL != checker->pNextUser)
        {
            checker = checker->pNextUser;
        }
        else
        {
            checker = NULL;
        }
    }

    if (true == isExist)
    {
        printf("[ERROR] User '%s' already exists. Cannot add this\n",
               sampleUser.name);
    }
    else
    {
        /* ==========================
                ADD NEW USER
           ========================== */

        /* Find tail */
        if (NULL != curUserTail)
        {
            while (NULL != curUserTail->pNextUser)
            {
                curUserTail = curUserTail->pNextUser;
            }
        }

        /* Allocate new node */
        tempUser = (sUserDataType *)malloc(sizeof(sUserDataType));
        *tempUser = sampleUser;

        /* Insert into list */
        if (NULL == pUser)
        {
            pUser = tempUser;
            tempUser->id = 0u;
        }
        else
        {
            tempUser->id = curUserTail->id + 1u;
            curUserTail->pNextUser = tempUser;
        }

        /* Initialize borrowed book list */
        for (uint8_t i = 0; i < USER_MAX_BOOK_CAN_BORROW; i++)
        {
            tempUser->pBookBorrowed[i] = NULL;
        }

        tempUser->pNextUser = NULL;

        printf("[INFO] User '%s' added successfully.\n", sampleUser.name);
    }
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
    uint8_t delBuff[USER_NAME_SIZE];


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
                strcpy((char*)delBuff, (char*)tempUser->name);
                free(tempUser);
                printf("[INFO] Deleted user '%s' successfuly!\n", delBuff);
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
                strcpy((char*)delBuff, (char*)tempUser->name);
                free(tempUser);
                printf("[INFO] Deleted user: %s\n", delBuff);
            }

        }
        else
        {
            printf("[ERROR] Invalid id\n");
        }
    }
}

void modifyUser()
{
    sUserDataType *tempUser;
    uint32_t id;


    if (NULL == pUser)
    {
        printf("[ERROR] There is no user, cannot modify\n");
    }
    else
    {
        printf("[BOOK] Enter the user id you wanna modify:\n");
        id = getIdInput();
        tempUser = pUser;
        if (true == isUserIdInList(id))
        {
            /* printf("found book id, can modify\n"); */
            if (id != (tempUser->id))
            {
                while (id != tempUser->id)
                {
                    tempUser = tempUser->pNextUser;
                }
            }
            editUserInfo(tempUser);
        }
        else
        {
            printf("[ERROR] Invalid user id\n");
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

void editUserInfo(sUserDataType *sampleUser)
{
    uint8_t buff[0xFF];

    printf("=== EDIT USER INFO ===\n");
    printf("Current name : %s\n", sampleUser->name);

    printf("Enter new name (Enter to skip): ");
    fgets((char*)buff, sizeof(buff), stdin);

    buff[strcspn((char*)buff, "\n")] = 0;

    if (strlen((char*)buff) == 0)
    {
        printf("No changes were made.\n");
        return;
    }

    strcpy((char*)sampleUser->name, (char*)buff);
    printf("User name updated successfully!\n");
}

sUserDataType *getUserAdd()
{
    return (sUserDataType *)pUser;
}