#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../header/user.h"

void login(UserList *list, User *current_user, boolean *isLogin) {
    if (!(*isLogin)) {
        printf(CYAN BOLD "=== LOGIN ===\n" RESET );
        
        char username[100], password[100];
        
        printf(YELLOW "Username: " RESET);
        scanf("%s", username);
        printf(YELLOW "Password: " RESET);
        scanf("%s", password);
    
        User *user = findUser(list, username);   // nampung user yang sudah dicari
        if (user == NULL) {
            printf(RED "Tidak ada Manager, Dokter, atau pun Pasien yang bernama %s\n\n", username);
            return;
        }
        // printf("[DEBUG] input password: '%s' %d\n", password, strlen(password));

        if (strcmp(user->password, password) == 0) {
            if (user->role == 0) {
                printf(GREEN "Selamat pagi %s! Ada keluhan apa ?\n\n", user->username);
            } else if (user->role == 1) {
                printf(GREEN "Selamat pagi %s %s!\n\n", roleToStr(user->role), user->username);
            } else if (user->role == 2) {
                printf(GREEN "Selamat pagi %s %s!\n\n", roleToStr(user->role) ,user->username);
            }
            *current_user = *user;
            *isLogin = TRUE;
        } else {
            printf(RED "Username atau password salah untuk pengguna yang bernama %s\n\n", username);
        }
    } else {
        printf(YELLOW "Anda sudah login!\n\n");
    }
}