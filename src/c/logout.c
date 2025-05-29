#include <stdio.h>
#include <string.h>

#include "../header/user.h" 

void logout(User *current_user, boolean *isLogin) {
    if (*isLogin == FALSE) {
        printf(RED BOLD "Logout gagal!\n" RESET);
        printf(YELLOW "Anda belum login, silahkan login terlebih dahulu sebelum melakukan logout!\n\n" RESET);
        return;
    }

    char answer[100];
    printf(CYAN "Apakah anda yakin untuk logout? (" GREEN BOLD"y" RESET CYAN "/" RED "n" RESET CYAN ") " RESET);
    do {
        scanf("%s", answer);
        toLower(answer);

        if (strcmp(answer, "y") != 0 && strcmp(answer, "n") != 0) {
            printf(RED "Masukan anda belum benar, coba lagi!\n\n" RESET);
            printf(CYAN "Apakah anda yakin untuk logout? (" GREEN BOLD"y" RESET CYAN "/" RED "n" RESET CYAN ") " RESET);
        }
    } while (strcmp(answer, "y") != 0  && strcmp(answer, "n") != 0);
    
    if (strcmp(answer, "y") == 0) {
        current_user = NULL;
        *isLogin = FALSE;
        printf(GREEN "Sampai jumpa!\n\n\n" RESET);

        sleep(2);
        system("clear");
        
        printBanner();
        printf(CYAN "Ketik command " YELLOW BOLD "HELP" RESET CYAN " untuk melihat apa saja yang dapat kamu lakukan sekarang!\n\n" RESET);

        return;
    } else {
        printf(YELLOW "Anda tidak jadi logout...\n\n" RESET);
    }
}
