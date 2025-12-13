#ifndef _BORROW_H_
#define _BORROW_H_

#include "Book.h"
#include "User.h"
#include "Log.h"

#define BORR_RET_CHAR_TO_NUM(x) (((x) >= '0' && (x) <= '9') ? ((x) - '0') : BORR_RET_INVALID_ACC)

typedef enum eBorr
{
    BORR_RET_BORROW,
    BORR_RET_RETURN,
    BORR_RET_PIRNT,
    BORR_RET_INVALID_ACC
} eBorrRetSelAcc_t;

typedef struct sBorr
{
    eBorrRetSelAcc_t id;
    const char *msg;
} sBorrRetSelAcc_t;

static const sBorrRetSelAcc_t sBorrRetSelAcc[] = {
    {BORR_RET_BORROW,       "Borrow a book"},
    {BORR_RET_RETURN,       "Return a book"},
    {BORR_RET_PIRNT,        "Print all book status"},
};

/**
 * @brief  get user choice from keyboard
 */
void printBorrRetlAcc();

/**
 * @brief  get user choice from keyboard
 */
eBorrRetSelAcc_t borrRetSelAcc();

/**
 * @brief  get user choice from keyboard
 */
void borrRetBook(eBorrRetSelAcc_t eBorrOrRet);

/**
 * @brief  get user choice from keyboard
 */
void borrBook(sUserData_t **tempUser);

/**
 * @brief  get user choice from keyboard
 */
void returnBook();

/**
 * @brief  get user choice from keyboard
 */
bool canBorrBook(sUserData_t *tempUser, uint8_t *index);

#endif/* _BORROW_H_ */