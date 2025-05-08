#include <stdio.h>
#include <stdlib.h>
#include "user.h"

int main(int argc, char* argv[]) {

    // Inisialisasi Database User
    UserList database;
    CreateListDin(&database, 5);

    // Inisialisasi Set nama unik User
    Set nama_unik;
    initSet(&nama_unik, 5);

    // LOAD DATA from file folder
    /* belum ada */

    // Inisialisasi state LOGIN
    User current_user;
    boolean isLogin = FALSE;

    while (1) {
        char prompt[100];
        printf(">>> ");
        scanf("%s", prompt);
    
        if (strcmp(prompt, "LOGIN") == 0) {
            system("clear");
            login(&database, &current_user, &isLogin);
        } else if (strcmp(prompt, "REGISTER") == 0) {
            system("clear");
            registerPasien(&database, &nama_unik);
        } else if (strcmp(prompt, "LUPA_PASSWORD") == 0) {
            system("clear");
            lupa_password(&database);
        } else if (strcmp(prompt, "LOGOUT") == 0) {
            system("clear");
            logout(&current_user, &isLogin);
        } else if (strcmp(prompt, "HELP") == 0) {
            system("clear");
            helpMenu(current_user, &isLogin);
        } else {
            printf("Nama fungsi tidak terdaftar atau kesalahan pengetikan nama fungsi!\n\n");
        }
    }

    return 0;
}