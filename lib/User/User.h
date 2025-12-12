#ifndef _USER_H_
#define _USER_H_

#include "Book.h"

#define USER_NAME_SIZE 30u
#define USER_MAX_BOOK_CAN_BORROW 2u

#define USER_CHAR_TO_NUM(x) (((x) >= '0' && (x) <= '9') ? ((x) - '0') : USER_INVALID_ACC)

typedef enum eUser
{
    USER_ADD,
    USER_DEL,
    USER_MODIFY,
    USER_PRINT,
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
    {USER_PRINT,        "Print all users infomation"},
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
 * @brief  get user choice from keyboard
 */
void printUserlAcc();

/**
 * @brief  get user choice from keyboard
 */
eUserSelAcc_t userSelectAcc();

/**
 * @brief  get user choice from keyboard
 */
void printUserInfo();

/**
 * @brief  get user choice from keyboard
 */
void addUser(sUserData_t sampleUser);

/**
 * @brief  get user choice from keyboard
 */
void delUser();

/**
 * @brief  get user choice from keyboard
 */
void modifyUser();

/**
 * @brief  get user choice from keyboard
 */
void formatUser(sUserData_t *sampleUser);

/**
 * @brief  get user choice from keyboard
 */
uint32_t countBookBorrowed(sUserData_t *sampleUser);

/**
 * @brief  get user choice from keyboard
 */
bool isUserIdInList(const uint32_t id);

/**
 * @brief  get user choice from keyboard
 */
void editUserInfo(sUserData_t *sampleUser);

/**
 * @brief  get user choice from keyboard
 */
sUserData_t *getUserAdd();

/**
 * @brief  get user choice from keyboard
 */
void freeUser(sUserData_t **sampleUser);

/**
 * @brief  get user choice from keyboard
 */
void initUserForTest();

/**
 * @brief  get user choice from keyboard
 */
bool isUserInSys(sUserData_t sampleUser);

#endif /* _USER_H_ */
