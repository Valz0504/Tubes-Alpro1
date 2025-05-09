#include <stdio.h>
#include "../header/user.h"
#include "../header/boolean.h"

void EXIT(User *current_user, UserList *list, boolean *run_program){
    char input[2];
    do {
        printf("Apakah Anda mau melakukan penyimpanan file yang sudah diubah? (y/n) ");
        scanf("%s", input);
        toLower(input);
    } while (strcmp(input, "y") != 0 && strcmp(input, "n") != 0);
    // if(strcmp(input, "y") == 0){
    //     return;
    // }
    *run_program = FALSE;
    // x == "y" ga ada soalnya belum ada Save()
}
