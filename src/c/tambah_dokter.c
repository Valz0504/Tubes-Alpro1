#include <stdio.h>
#include <string.h>

#include "../header/user.h"
#include "../header/set.h"
#include "../header/boolean.h"

void tambahDokter(UserList *list, User *current_user, Set *set, boolean *isLogin) {
    if (*isLogin) {
        if (current_user->role == ROLE_MANAGER) {
            printf("=== TAMBAH DOKTER ===\n");
            char username[100], password[100];
            
            printf("Username: ");
            scanf(" %[^\n]s", username);
            printf("Password: ");
            scanf(" %[^\n]s", password);
    
            toLower(username);
            if (isUsernameUnique(*set, username)) {
                insertSet(set, username);
    
                User new_user;
                CreateUser(list, &new_user, username, password, 1);
                AddUser(list, new_user);
                
                printf("Dokter %s berhasil ditambahkan!\n\n", username);
            } else {
                printf("Sudah ada Dokter bernama %s!\n\n", username);
            }
        } else {
            printf("Anda bukan manager! Tidak bisa tambah dokter!\n\n");
        }
    } else {
        printf("Login terlebih dahulu!\n\n");
    }

}

