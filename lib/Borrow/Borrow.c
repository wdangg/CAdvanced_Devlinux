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
            LOG_INFO("Please choose user id you wanna borrow or return book: ");
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
            LOG_INFO("Please choose a book you wanna borrow");
            id = getIdInput();
            if (true == isBookIdInList(id, &tempBook, &prevBook))
            {
                printUserInfo();
                tempBook->status = BOOK_STATUS_BORROWED;
                strcpy((tempBook->userBorrow), ((*tempUser)->name));
                (*tempUser)->pBookBorrowed[index] = tempBook;
                /* LOG_INFO("break point"); */
                printUserInfo();
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
    sUserData_t *tempUser = NULL;
    sUserData_t *prevUser = NULL;
    sBookData_t *tempBook = NULL;
    sBookData_t *prevBook = NULL;
    uint32_t id;
    uint8_t index;
    bool isBookIdExist = false;

    tempUser = getUserAdd();

    if (NULL != tempUser)
    {
        bool proceed = true;
        uint32_t printedUsers = printUsersWithBorrowedBooks();
        if (0u == printedUsers)
        {
            LOG_ERROR("No users have borrowed books, cannot return");
            proceed = false;
        }

        if (proceed)
        {
            LOG_INFO("Please choose user id you wanna return book: ");
            id = getIdInput();

            if (isUserIdInList(id, &tempUser, &prevUser))
            {
                if (0u != countBookBorrowed(tempUser))
                {
                    uint32_t printedBooks = printBooksBorrowedByUser(tempUser);
                    if (0u == printedBooks)
                    {
                        LOG_ERROR("Selected user has no borrowed books, cannot return");
                        proceed = false;
                    }

                    if (proceed)
                    {
                        LOG_INFO("Please choose book id you wanna return: ");
                        id = getIdInput();
                        isBookIdExist = isBookIdInList(id, &tempBook, &prevBook);
                        if (true == isBookIdExist)
                        {
                            /* ensure the selected book belongs to this user */
                            bool found = false;
                            for (index = 0; index < USER_MAX_BOOK_CAN_BORROW && (false == found); index++)
                            {
                                if (tempBook == (tempUser->pBookBorrowed[index]))
                                {
                                    tempBook->status = BOOK_STATUS_AVAILABLE;
                                    memset(tempBook->userBorrow, 0, sizeof(tempBook->userBorrow));
                                    tempUser->pBookBorrowed[index] = NULL;
                                    found = true;
                                }
                            }

                            if (found)
                            {
                                printUserInfo();
                            }
                            else
                            {
                                LOG_ERROR("Selected book is not borrowed by chosen user");
                            }
                        }
                        else
                        {
                            LOG_ERROR("There is no book id in list, cannot process");
                        }
                    }
                }
                else
                {
                    LOG_ERROR("User has not borrowed any book, cannot return");
                }
            }
            else
            {
                LOG_ERROR("There is no user id in list, cannot process");
            }
        }
    }
    else
    {
        LOG_ERROR("There is no user information, cannot return book");
    }
}
