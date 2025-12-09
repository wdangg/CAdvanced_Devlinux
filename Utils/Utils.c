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

void trimNewline(char *str)
{
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n')
        str[len - 1] = '\0';
}
