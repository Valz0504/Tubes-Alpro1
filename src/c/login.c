#include <stdio.h>
#include <string.h>

#include "header/user.h"
#include "header/boolean.h"

void login(UserList *list, User *current_user, boolean *isLogin) {
    printf("=== LOGIN ===\n");
    
    char username[100], password[100];

    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    User *user = findUser(list, username);   // nampung user yang sudah dicari
    if (user == NULL) {
        printf("Tidak ada Manager, Dokter, atau pun Pasien yang bernama %s\n\n", username);
        return;
    }

    if (strcmp(user->password, password) == 0) {
        if (user->role == 0) {
            printf("Selamat pagi %s! Ada keluhan apa ?\n\n", user->username);
        } else if (user->role == 1) {
            printf("Selamat pagi %s %s!\n\n", roleToStr(user->role), user->username);
        } else if (user->role == 2) {
            printf("Selamat pagi %s %s!\n\n", roleToStr(user->role) ,user->username);
        }
        *current_user = *user;
        *isLogin = TRUE;
    } else {
        printf("Username atau password salah untuk pengguna yang bernama %s\n\n", username);
    }
}