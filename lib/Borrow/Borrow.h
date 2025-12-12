#ifndef _BORROW_H_
#define _BORROW_H_

#include "Book.h"
#include "User.h"

#define BORR_RET_CHAR_TO_NUM(x) (((x) >= '0' && (x) <= '9') ? ((x) - '0') : BORR_RET_INVALID_ACC)

typedef enum eBorr
{
    BORR_RET_BORROW,
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
    {BORR_RET_PIRNT,        "Print all book status"},
};

/**
 * @brief  get user choice from keyboard
 */
void printBorrRetlAcc();

/**
 * @brief  get user choice from keyboard
 */
eBorrRetSelAcc_t borrRetSelectAcc();

/**
 * @brief  get user choice from keyboard
 */
void borrRetBook();

#endif/* _BORROW_H_ */