#include <stdio.h>
#include <string.h>

#include "../header/user.h"

void registerPasien(UserList *list, Set *set, boolean *isLogin) {
    if (!(*isLogin)) {
        printf(CYAN BOLD "=== REGISTER ===\n" RESET);
        char username[100], password[100];
        
        printf(YELLOW "Username: " RESET);
        scanf("%s", username);
        printf(YELLOW "Password: " RESET);
        scanf("%s", password);

        char usernameTemp[100];
        strcpy(usernameTemp, username);
        toLower(username);
        if (isUsernameUnique(*set, username)) {
            insertSet(set, username);

            User new_user;
            initStack(&new_user.perut);
            CreateUser(list, &new_user, usernameTemp, password, 0);
            AddUser(list, new_user);
            
            printf(GREEN "Pasien %s berhasil ditambahkan!\n\n", usernameTemp);
        } else {
            printf(RED "Registrasi gagal! Sudah ada User dengan nama %s.\n\n", username);
        }
    } else {
        printf(YELLOW "Anda sedang login! Logout terlebih dahulu!\n\n");
    }
}

