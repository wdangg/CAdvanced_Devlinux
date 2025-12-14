#include "User.h"

sUserData_t *pUser = NULL;

void printUserlAcc()
{
    printf("----------------------------------------------------------------\n");
    for (uint8_t i = 0; i < sizeof(sUserSelAcc)/sizeof(sUserSelAcc[0]); i++)
    {
        printf("\t%d. %s\n", sUserSelAcc[i].id, sUserSelAcc[i].msg);
    }
    printf("----------------------------------------------------------------\n");
    LOG_INFO("Please choose the action you want:");
}

eUserSelAcc_t userSelectAcc()
{
    eUserSelAcc_t eRet;
    uint32_t tempChoice;

    tempChoice = getchar();
    tempChoice = USER_CHAR_TO_NUM(tempChoice);
    /* LOG_PRINT("tempChoice = %d\n", tempChoice); */

    getchar(); /* clear stdin, there is a newline character still here */

    if ((uint32_t)USER_INVALID_ACC < tempChoice)
    {
        eRet = USER_INVALID_ACC;
    }
    else
    {
        eRet = (eUserSelAcc_t)tempChoice;
    }
    /* LOG_PRINT("eRet = %d\n", eRet);  */
    return eRet;
}

void printUserInfo()
{
    sUserData_t *tempUser = pUser;
    uint32_t totalBookBorrowed;

    if (NULL == tempUser)
    {
        LOG_ERROR("There is no user in library.");
    }
    else
    {
        printf("====================================================================================\n");
        printf("| %-2s | %-25s | %-45s |\n",
               "ID", "NAME", "BORROWED_BOOKS");
        printf("------------------------------------------------------------------------------------\n");
    
        while (NULL != tempUser)
        {
            totalBookBorrowed = countBookBorrowed(tempUser);

            /* build comma separated list of borrowed titles */
            char bookList[200] = {0};
            size_t pos = 0;
            for (uint8_t j = 0; j < USER_MAX_BOOK_CAN_BORROW; j++)
            {
                sBookData_t *b = tempUser->pBookBorrowed[j];
                if (NULL != b)
                {
                    int n = snprintf(bookList + pos, sizeof(bookList) - pos, "%s, ", (char *)b->title);
                    if (n > 0)
                    {
                        pos += (size_t)n;
                        if (pos >= sizeof(bookList))
                        {
                            pos = sizeof(bookList) - 1;
                            break;
                        }
                    }
                }
            }
            /* remove trailing comma+space */
            if (pos >= 2)
            {
                if (bookList[pos - 2] == ',' && bookList[pos - 1] == ' ')
                {
                    bookList[pos - 2] = '\0';
                }
            }

            if (0u == totalBookBorrowed)
            {
                strcpy(bookList, "-");
            }

            printf("| %-2d | %-25s | %-45s |\n",
                   tempUser->id,
                   tempUser->name,
                   bookList);
            tempUser = tempUser->pNextUser;
        }
    
        printf("====================================================================================\n");
    }
}

void addUser(sUserData_t sampleUser)
{
    sUserData_t *tempUser;
    sUserData_t *curUserTail = pUser;
    sUserData_t *checker = pUser;

    bool isExist = false;

    /* Check if user already exist */
    isExist = isUserInSys(sampleUser);

    if (true == isExist)
    {
        LOG_ERROR("User '%s' already exists. Cannot add this\n",
               sampleUser.name);
    }
    else
    {
        /* Find tail */
        if (NULL != curUserTail)
        {
            while (NULL != curUserTail->pNextUser)
            {
                curUserTail = curUserTail->pNextUser;
            }
        }

        /* Allocate new node */
        tempUser = (sUserData_t *)malloc(sizeof(sUserData_t));
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

        LOG_INFO("User '%s' added successfully.", sampleUser.name);
    }
}


void formatUser(sUserData_t *pSample)
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

uint32_t countBookBorrowed(sUserData_t *sampleUser)
{
    uint32_t retVal = 0u;

    if (NULL != sampleUser)
    {
        for (uint8_t i = 0; i < USER_MAX_BOOK_CAN_BORROW; i++)
        {
            if (NULL != sampleUser->pBookBorrowed[i])
            {
                retVal++;
            }
        }
    }
    else
    {
        LOG_ERROR("countBookBorrowed() function: sampleUser is NULL");
    }

    return retVal;
}

uint32_t printUsersWithBorrowedBooks(void)
{
    sUserData_t *tempUser = pUser;
    uint32_t printed = 0u;

    if (NULL == tempUser)
    {
        LOG_ERROR("There is no user in library.");
    }
    else
    {
        printf("====================================================================================\n");
        printf("| %-2s | %-25s | %-45s |\n",
               "ID", "NAME", "BORROWED_BOOKS");
        printf("------------------------------------------------------------------------------------\n");
    
        while (NULL != tempUser)
        {
            if (countBookBorrowed(tempUser) > 0u)
            {
                /* build comma separated list of borrowed titles */
                char bookList[200] = {0};
                size_t pos = 0;
                for (uint8_t j = 0; j < USER_MAX_BOOK_CAN_BORROW; j++)
                {
                    sBookData_t *b = tempUser->pBookBorrowed[j];
                    if (NULL != b)
                    {
                        int n = snprintf(bookList + pos, sizeof(bookList) - pos, "%s, ", (char *)b->title);
                        if (n > 0)
                        {
                            pos += (size_t)n;
                            if (pos >= sizeof(bookList))
                            {
                                pos = sizeof(bookList) - 1;
                                break;
                            }
                        }
                    }
                }
                /* remove trailing comma+space */
                if (pos >= 2)
                {
                    if (bookList[pos - 2] == ',' && bookList[pos - 1] == ' ')
                    {
                        bookList[pos - 2] = '\0';
                    }
                }

                printf("| %-2d | %-25s | %-45s |\n",
                       tempUser->id,
                       tempUser->name,
                       bookList);
                printed++;
            }
            tempUser = tempUser->pNextUser;
        }
    
        printf("====================================================================================\n");
    
        if (0u == printed)
        {
            LOG_INFO("There is no user who has borrowed books.");
        }
    }

    return printed;
}

uint32_t printBooksBorrowedByUser(sUserData_t *sampleUser)
{
    uint32_t printed = 0u;

    if (NULL == sampleUser)
    {
        LOG_ERROR("printBooksBorrowedByUser, invalid user pointer");
    }
    else
    {
        printf("====================================================================================\n");
        printf("| %-2s | %-25s | %-25s | %-10s |\n",
               "ID", "TITLE", "AUTHOR", "STATUS");
        printf("------------------------------------------------------------------------------------\n");
    
        for (uint8_t i = 0; i < USER_MAX_BOOK_CAN_BORROW; i++)
        {
            sBookData_t *b = sampleUser->pBookBorrowed[i];
            if (NULL != b)
            {
                printf("| %-2d | %-25s | %-25s | %-10s |\n",
                       b->id,
                       b->title,
                       b->author,
                       (b->status == BOOK_STATUS_AVAILABLE) ? "Available" : "Borrowed");
                printed++;
            }
        }
    
        printf("====================================================================================\n");
    
        if (0u == printed)
        {
            LOG_INFO("This user has not borrowed any book.");
        }
    }

    return printed;
}

void delUser()
{
    sUserData_t *tempUser;
    sUserData_t *prevUser = NULL;
    bool found = false;
    uint32_t id;
    uint8_t delBuff[USER_NAME_SIZE];

    if (NULL == pUser)
    {
        LOG_ERROR("There is no book to delete");
    }
    else
    {
        LOG_PRINT("[BOOK] Enter the book id you wanna delete:");
        id = getIdInput();

        if (true == isUserIdInList(id, &tempUser, &prevUser))
        {
            if (NULL == prevUser)
            {
                pUser = tempUser->pNextUser;
                strcpy((char*)delBuff, (char*)tempUser->name);
                freeUser(&tempUser);
                LOG_INFO("Deleted user '%s' successfuly!\n", delBuff);
            }
            else
            {
                if (NULL == tempUser->pNextUser)
                {
                    prevUser->pNextUser = NULL;
                }
                else
                {
                    prevUser->pNextUser = tempUser->pNextUser;
                }
                strcpy((char*)delBuff, (char*)tempUser->name);
                freeUser(&tempUser);
                LOG_INFO("Deleted user: %s\n", delBuff);
            }

        }
        else
        {
            LOG_ERROR("Invalid id");
        }
    }
}

void modifyUser()
{
    sUserData_t *tempUser;
    sUserData_t *prevUser;
    uint32_t id;


    if (NULL == pUser)
    {
        LOG_ERROR("There is no user, cannot modify");
    }
    else
    {
        LOG_PRINT("[BOOK] Enter the user id you wanna modify:");
        id = getIdInput();

        if (true == isUserIdInList(id, &tempUser, &prevUser))
        {
            /* LOG_PRINT("found book id, can modify"); */
            editUserInfo(tempUser);
        }
        else
        {
            LOG_ERROR("Invalid user id");
        }
    }
}

bool isUserIdInList(const uint32_t id, sUserData_t **tempUser, sUserData_t **prevUser)
{
    sUserData_t *sampleUser = pUser;
    bool bRet = false;

    if (NULL != sampleUser)
    {
        while (NULL != sampleUser)
        {
            if (id == sampleUser->id)
            {
                *tempUser = sampleUser;
                bRet = true;
                /* set sampleUser = NULL to exit while loop */
                sampleUser = (sUserData_t *)NULL;
            }
            else
            {
                *prevUser = sampleUser;
                sampleUser = sampleUser->pNextUser;
            }
        }
    }
    else
    {
        LOG_ERROR("isUserIdInList");
    }
    return bRet;
}

void editUserInfo(sUserData_t *sampleUser)
{
    uint8_t buff[0xFF];

    LOG_PRINT("=== EDIT USER INFO ===");
    LOG_PRINT("Current name : %s\n", sampleUser->name);

    LOG_PRINT("Enter new name (Enter to skip): ");
    fgets((char*)buff, sizeof(buff), stdin);

    buff[strcspn((char*)buff, "\n")] = 0;

    if (0u == strlen((char*)buff))
    {
        LOG_INFO("No changes were made.");
        return;
    }

    strcpy((char*)sampleUser->name, (char*)buff);
    LOG_INFO("User name updated successfully!");
}

sUserData_t *getUserAdd()
{
    return (sUserData_t *)pUser;
}

void freeUser(sUserData_t **sampleUser)
{
    if (NULL != *sampleUser)
    {
        free(*sampleUser);
        *sampleUser = NULL;
    }
}

void initUserForTest(void)
{
    sUserData_t sampleUser;

    /* user 1 */
    /* sampleUser.id = 1; */
    strcpy(sampleUser.name, "Nguyen Van An");

    for (uint8_t i = 0; i < USER_MAX_BOOK_CAN_BORROW; i++)
    {
        sampleUser.pBookBorrowed[i] = NULL;
    }

    sampleUser.pNextUser = NULL;
    addUser(sampleUser);


    /* user 2 */
    /* sampleUser.id = 2; */
    strcpy(sampleUser.name, "Tran Thi Bich");

    for (uint8_t i = 0; i < USER_MAX_BOOK_CAN_BORROW; i++)
    {
        sampleUser.pBookBorrowed[i] = NULL;
    }

    sampleUser.pNextUser = NULL;
    addUser(sampleUser);


    /* user 3 */
    /* sampleUser.id = 3; */
    strcpy(sampleUser.name, "Le Van Cuong");

    for (uint8_t i = 0; i < USER_MAX_BOOK_CAN_BORROW; i++)
    {
        sampleUser.pBookBorrowed[i] = NULL;
    }

    sampleUser.pNextUser = NULL;
    addUser(sampleUser);
}

bool isUserInSys(sUserData_t sampleUser)
{
    bool retVal = false;
    sUserData_t *tempUser = pUser;

    if (NULL != tempUser)
    {
        while (NULL != tempUser)
        {
            if (0u == strcmp(sampleUser.name, tempUser->name))
            {
                retVal = true;
                /* set tempUser to exit while loop, dont use break */
                tempUser = NULL;
            }
            else
            {
                tempUser = tempUser->pNextUser;
            }
        }
    }

    return retVal;
}

