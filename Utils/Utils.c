#include "Utils.h"

sBookDataType getBookInput(void)
{
    sBookDataType sRet;
    uint32_t id;
    uint8_t temp;
    uint8_t sTitle[TITLE_SIZE];
    uint8_t sAuthor[AUTHOR_SIZE];

    printf("Please text the book's title:\n");
    fgets(sTitle, sizeof(sTitle), stdin);
    strcpy(sRet.title, sTitle);
    printf("sTile: %s", sTitle);
    printf("Please text the book's author:\n");
    fgets(sAuthor, sizeof(sAuthor), stdin);
    strcpy(sRet.author, sAuthor);
    printf("sAuthor: %s", sAuthor);

    return sRet;
}
