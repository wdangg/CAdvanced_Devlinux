#include "Utils.h"

sBookData_t getBookInput(void)
{
    sBookData_t sRet;
    uint8_t sTitle[TITLE_SIZE];
    uint8_t sAuthor[AUTHOR_SIZE];

    /* format the book before write data */
    formatBook(&sRet);

    LOG_PRINT("Please text the book's title:");
    fgets((char *)sTitle, sizeof(sTitle), stdin);

    ((char *)sTitle)[strcspn((char *)sTitle, "\n")] = '\0';
    strcpy((char *)sRet.title, (char *)sTitle);
    LOG_PRINT("sTile: %s", sTitle);
    LOG_PRINT("Please text the book's author:");
    fgets((char *)sAuthor, sizeof(sAuthor), stdin);
    ((char *)sAuthor)[strcspn((char *)sAuthor, "\n")] = '\0';
    strcpy((char *)sRet.author, (char *)sAuthor);
    LOG_PRINT("sAuthor: %s", sAuthor);

    return sRet;
}

sUserData_t getUserInput()
{
    sUserData_t sRet;
    uint8_t strName[USER_NAME_SIZE];

    /* format the user before write data */
    formatUser(&sRet);

    LOG_PRINT("Please text the user name:");
    fgets((char *)strName, sizeof(strName), stdin);
    ((char *)strName)[strcspn((char *)strName, "\n")] = '\0';
    strcpy((char *)sRet.name, (char *)strName);
    LOG_PRINT("strName: %s", strName);

    return sRet;
}

void bookMana()
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

void userMana()
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
    else
    {
        LOG_ERROR("Invalid input, please follow the guide");
    }
}

void printBooks()
{
    printfBookInfo(BOOK_STATUS_ALL);
}

void borrRetMana()
{
    eBorrRetSelAcc_t eBorrRetSelAcc;

    printBorrRetlAcc();

    eBorrRetSelAcc = borrRetSelAcc();
    /* LOG_PRINT("eBorrRetSelAcc ================= %d", eBorrRetSelAcc); */
    if ((BORR_RET_BORROW == eBorrRetSelAcc) || (BORR_RET_RETURN == eBorrRetSelAcc))
    {
        /* LOG_PRINT("BORR_RET_BORROW == eBorrRetSelAcc"); */
        borrRetBook(eBorrRetSelAcc);
    }
    else
    {
        LOG_ERROR("Invalid input, please follow the guide");
    }
}

void findBook()
{
    char *line = NULL; 
    size_t len = 0;
    ssize_t read;

    printf("Please enter title or author you wanna find: ");
    read = getline(&line, &len, stdin);

    if ((-1) != read)
    {
        /* remove newline character from input */
        line[strcspn(line, "\n")] = 0;

        sBookData_t *tempBook = getBookAdd();
        bool found = false;

        printf("====================================================================================\n");
        printf("| %-2s | %-25s | %-25s | %-10s | %-25s |\n",
               "ID", "TITLE", "AUTHOR", "STATUS", "BORROWER");
        printf("------------------------------------------------------------------------------------\n");

        while (NULL != tempBook)
        {
            if ((NULL != strstr((char *)tempBook->title, line)) ||
                (NULL != strstr((char *)tempBook->author, line)))
            {
                const char *borrower = (tempBook->userBorrow[0] != 0) ? (char *)tempBook->userBorrow : "-";
                printf("| %-2d | %-25s | %-25s | %-10s | %-25s |\n",
                       tempBook->id,
                       tempBook->title,
                       tempBook->author,
                       (tempBook->status == BOOK_STATUS_AVAILABLE) ? "Available" : "Borrowed",
                       borrower);
                found = true;
            }
            tempBook = tempBook->pNextBook;
        }

        printf("====================================================================================\n");

        if (false == found)
        {
            LOG_INFO("No matching book found for '%s'.", line);
        }
    }
    else
    {
        LOG_ERROR("Error reading input");
    }

    free(line);
}
