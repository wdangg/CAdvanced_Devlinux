#ifndef _USER_H_
#define _USER_H_

#include "Book.h"
#include "Log.h"

#define USER_MAX_BOOK_CAN_BORROW 3u

#define USER_CHAR_TO_NUM(x) (((x) >= '0' && (x) <= '9') ? ((x) - '0') : USER_INVALID_ACC)

typedef enum eUser
{
    USER_ADD,
    USER_DEL,
    USER_MODIFY,
    USER_INVALID_ACC
} eUserSelAcc_t;

typedef struct sUser
{
    eUserSelAcc_t id;
    const char *msg;
} sUserSelAcc_t;

static const sUserSelAcc_t sUserSelAcc[] = {
    {USER_ADD,          "Add an user"},
    {BOOK_DEL,          "Delete an user"},
    {BOOK_MODIFY_INFO,  "Modify user infomation"},
};

typedef struct sUserInfo
{
    /* data */
    uint32_t id;
    uint8_t name[USER_NAME_SIZE];
    sBookData_t *pBookBorrowed[USER_MAX_BOOK_CAN_BORROW];
    struct sUserInfo *pNextUser;
} sUserData_t;

/**
 * @brief  Print user menu.
 */
void printUserlAcc();

/**
 * @brief  Read user menu selection.
 */
eUserSelAcc_t userSelectAcc();

/**
 * @brief  Print all users and their borrowed books.
 */
void printUserInfo();

/**
 * @brief  Add a new user.
 */
void addUser(sUserData_t sampleUser);

/**
 * @brief  Delete a user by id.
 */
void delUser();

/**
 * @brief  Modify a user's information.
 */
void modifyUser();

/**
 * @brief  Initialize a user structure with defaults.
 */
void formatUser(sUserData_t *sampleUser);

/**
 * @brief  Count books borrowed by a user.
 * @param  sampleUser  The user to inspect.
 * @return number of books borrowed.
 */
uint32_t countBookBorrowed(sUserData_t *sampleUser);

/**
 * @brief  Find a user node by id.
 * @param  id        User id to find.
 * @param  tempUser  Output pointer set to found node (if any).
 * @param  prevUser  Output pointer set to previous node (if any).
 * @return true if found, false otherwise.
 */
bool isUserIdInList(const uint32_t id, sUserData_t **tempUser, sUserData_t **prevUser);

/**
 * @brief  Edit user fields interactively.
 * @param  sampleUser  Pointer to the user to edit.
 */
void editUserInfo(sUserData_t *sampleUser);

/**
 * @brief  Get pointer to user list head.
 * @return pointer to first user in list.
 */
sUserData_t *getUserAdd();

/**
 * @brief  Free a user node.
 * @param  sampleUser  Pointer to pointer to user node to free.
 */
void freeUser(sUserData_t **sampleUser);

/**
 * @brief  Populate users with sample data for testing.
 */
void initUserForTest();

/**
 * @brief  Check if a user name exists.
 */
bool isUserInSys(sUserData_t sampleUser);

/**
 * @brief  Print users who have borrowed books.
 * @return number of users printed
 */
uint32_t printUsersWithBorrowedBooks(void);

/**
 * @brief  Print books borrowed by the specified user.
 * @return number of books printed
 */
uint32_t printBooksBorrowedByUser(sUserData_t *sampleUser);

#endif /* _USER_H_ */
