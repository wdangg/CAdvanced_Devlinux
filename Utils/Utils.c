#include "Utils.h"

sBookDataType getBookInput(void)
{
    sBookDataType sRet;
    uint32_t id;
    uint8_t temp;
    uint8_t sTitle[TITLE_SIZE];
    uint8_t sAuthor[AUTHOR_SIZE];

    /* format the book before write data */
    formatBook(&sRet);

    printf("Please text the book's title:\n");
    fgets(sTitle, sizeof(sTitle), stdin);
    trimNewline(sTitle);
    strcpy(sRet.title, sTitle);
    printf("sTile: %s\n", sTitle);
    printf("Please text the book's author:\n");
    fgets(sAuthor, sizeof(sAuthor), stdin);
    trimNewline(sAuthor);
    strcpy(sRet.author, sAuthor);
    printf("sAuthor: %s\n", sAuthor);

    return sRet;
}

sUserDataType midGetUserInput()
{
    sUserDataType sRet;
    uint32_t id;
    uint8_t temp;
    uint8_t strName[USER_NAME_SIZE];

    /* format the user before write data */
    formatUser(&sRet);

    printf("Please text the user name:\n");
    fgets(strName, sizeof(strName), stdin);
    trimNewline(strName);
    strcpy(sRet.name, strName);
    printf("strName: %s\n", strName);

    return sRet;
}

void trimNewline(char *str)
{
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n')
        str[len - 1] = '\0';
}

void midBookMana()
{
    sBookDataType tempBook;
    eBookSelAccType eBookSelAcc;

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
        printfBookInfo();
        delBook();
    }
    else if (BOOK_MODIFY_INFO == eBookSelAcc)
    {
        printfBookInfo();
        modifyBook();
    }
}

void midUserMana()
{
    sUserDataType tempUser;
    eUserSelAccType eUserSelAcc;

    
    /* init some users for test */
    /* initUserForTest(); */
    printUserlAcc();

    eUserSelAcc = userSelectAcc();
    if (USER_ADD == eUserSelAcc)
    {
        tempUser = midGetUserInput();
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

void midPrintBooks()
{
    sBookDataType *pBook;

    pBook = getBookAdd();
    printfBookInfo(pBook);
}

