#ifndef _USER_H_
#define _USER_H_

#include "Book.h"

#define USER_NAME_SIZE 30u
#define USER_MAX_BOOK_CAN_BORROW 2u

typedef struct User
{
    /* data */
    uint32_t id;
    uint8_t name[USER_NAME_SIZE];
    uint32_t bookBorrowed[USER_MAX_BOOK_CAN_BORROW];
    struct User *pNextUser;
} sUserDataType;

/**
 * @brief  get user choice from keyboard
 */
void userMana(sUserDataType **pUser);

/**
 * @brief  get user choice from keyboard
 */
void printUserInfo(sUserDataType *pUser);

#endif /* _USER_H_ */
