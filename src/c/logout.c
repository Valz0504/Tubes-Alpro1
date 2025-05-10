#include <stdio.h>
#include <string.h>

#include "../header/user.h" 

void logout(User *current_user, boolean *isLogin) {
    if (*isLogin == FALSE) {
        printf("Logout gagal!\n");
        printf("Anda belum login, silahkan login terlebih dahulu sebelum melakukan logout!\n\n");
        return;
    }

    char answer[100];
    printf("Apakah anda yakin untuk logout? (y/n)\n");
    do {
        scanf("%s", answer);
        toLower(answer);

        if (strcmp(answer, "y") != 0 && strcmp(answer, "n") != 0) {
            printf("Masukan anda belum benar, coba lagi!\n\n");
            printf("Apakah anda yakin untuk logout? (y/n)\n");
        }
    } while (strcmp(answer, "y") != 0  && strcmp(answer, "n") != 0);
    
    if (strcmp(answer, "y") == 0) {
        current_user = NULL;
        *isLogin = FALSE;
        printf("Sampai jumpa!\n\n");
        return;
    } else {
        printf("Anda tidak jadi logout...\n\n");
    }
}
