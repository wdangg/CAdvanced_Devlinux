#include "User.h"

void printUserInfo(sUserDataType *pUser)
{
    sUserDataType *tempUser = pUser;

    if (tempUser == NULL)
    {
        printf("There is no user in library.\n");
    }
    else
    {
        printf("====================================================================================\n");
        printf("| %-2s | %-25s | %-25s |\n",
               "ID", "NAME", "BORROWED");
        printf("------------------------------------------------------------------------------------\n");
    
        while (tempUser != NULL)
        {
            printf("| %-2d | %-25s | %-25d |\n",
                   tempUser->id,
                   tempUser->name,
                   (sizeof(tempUser->bookBorrowed)/sizeof(tempUser->bookBorrowed[0])));
    
            tempUser = tempUser->pNextUser;
        }
    
        printf("====================================================================================\n");
    }
}

void userMana(sUserDataType **pUser)
{

}
