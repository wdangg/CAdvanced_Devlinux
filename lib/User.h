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
} eUserSelAccType;

typedef struct sUser
{
    eUserSelAccType id;
    const char *msg;
} sUserSelAccType;

static const sUserSelAccType sUserSelAcc[] = {
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
    sBookDataType *pBookBorrowed[USER_MAX_BOOK_CAN_BORROW];
    struct sUserInfo *pNextUser;
} sUserDataType;

/**
 * @brief  get user choice from keyboard
 */
void printUserlAcc();

/**
 * @brief  get user choice from keyboard
 */
eUserSelAccType userSelectAcc();

/**
 * @brief  get user choice from keyboard
 */
void printUserInfo();

/**
 * @brief  get user choice from keyboard
 */
sUserDataType *getUserAdd();

/**
 * @brief  get user choice from keyboard
 */
void addUser(sUserDataType sampleUser);

/**
 * @brief  get user choice from keyboard
 */
void formatUser(sUserDataType *sampleUser);

/**
 * @brief  get user choice from keyboard
 */
uint32_t countBookBorrowed(sUserDataType *sampleUser);

#endif /* _USER_H_ */
