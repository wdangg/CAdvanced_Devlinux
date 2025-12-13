#include "Utils.h"

sBookData_t getBookInput(void)
{
    sBookData_t sRet;
    uint32_t id;
    uint8_t temp;
    uint8_t sTitle[TITLE_SIZE];
    uint8_t sAuthor[AUTHOR_SIZE];

    /* format the book before write data */
    formatBook(&sRet);

    LOG_PRINT("Please text the book's title:");
    fgets(sTitle, sizeof(sTitle), stdin);
    trimNewline(sTitle);
    strcpy(sRet.title, sTitle);
    LOG_PRINT("sTile: %s", sTitle);
    LOG_PRINT("Please text the book's author:");
    fgets(sAuthor, sizeof(sAuthor), stdin);
    trimNewline(sAuthor);
    strcpy(sRet.author, sAuthor);
    LOG_PRINT("sAuthor: %s", sAuthor);

    return sRet;
}

sUserData_t getUserInput()
{
    sUserData_t sRet;
    uint32_t id;
    uint8_t temp;
    uint8_t strName[USER_NAME_SIZE];

    /* format the user before write data */
    formatUser(&sRet);

    LOG_PRINT("Please text the user name:");
    fgets(strName, sizeof(strName), stdin);
    trimNewline(strName);
    strcpy(sRet.name, strName);
    LOG_PRINT("strName: %s", strName);

    return sRet;
}

void trimNewline(char *str)
{
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n')
        str[len - 1] = '\0';
}

void BookMana()
{
    sBookData_t tempBook;
    eBookSelAcc_t eBookSelAcc;

    /* init some book for test */
    /* initLibraryForTest(); */

    printBookSelAcc();
    eBookSelAcc = bookSelectAcc();
    if (BOOK_ADD == eBookSelAcc)
    {
        tempBook = getBookInput();
        addBook(tempBook);
    }
    else if (BOOK_DEL == eBookSelAcc)
    {
        printfBookInfo(BOOK_STATUS_ALL);
        delBook();
    }
    else if (BOOK_MODIFY_INFO == eBookSelAcc)
    {
        printfBookInfo(BOOK_STATUS_ALL);
        modifyBook();
    }
    else
    {
        LOG_ERROR("Invalid input, please follow the guide");
    }
}

void UserMana()
{
    sUserData_t tempUser;
    eUserSelAcc_t eUserSelAcc;

    
    /* init some users for test */
    /* initUserForTest(); */
    printUserlAcc();

    eUserSelAcc = userSelectAcc();
    if (USER_ADD == eUserSelAcc)
    {
        tempUser = getUserInput();
        addUser(tempUser);
    }
    else if (USER_DEL == eUserSelAcc)
    {
        printUserInfo();
        delUser();
    }
    else if (USER_MODIFY == eUserSelAcc)
    {
        printUserInfo();
        modifyUser();
    }
    else if (USER_PRINT == eUserSelAcc)
    {
        printUserInfo();
    }
}

void PrintBooks()
{
    printfBookInfo(BOOK_STATUS_ALL);
}

void BorrRetMana()
{
    eBorrRetSelAcc_t eBorrRetSelAcc;

    printBorrRetlAcc();

    eBorrRetSelAcc = borrRetSelAcc();
    if (BORR_RET_BORROW == eBorrRetSelAcc)
    {
        /* LOG_PRINT("BORR_RET_BORROW == eBorrRetSelAcc"); */
        borrRetBook(eBorrRetSelAcc);
    }
    else if (BORR_RET_PIRNT == eBorrRetSelAcc)
    {
        LOG_PRINT("BORR_RET_PIRNT == eBorrRetSelAcc");
        
    }
}

