#include <stdio.h>
#include <string.h>

#include "../header/user.h"

void registerPasien(UserList *list, Set *set, boolean *isLogin) {
    if (!(*isLogin)) {
        printf("=== REGISTER ===\n");
        char username[100], password[100];
        
        printf("Username: ");
        scanf(" %[^\n]s", username);
        printf("Password: ");
        scanf(" %[^\n]s", password);

        toLower(username);
        if (isUsernameUnique(*set, username)) {
            insertSet(set, username);

            User new_user;
            CreateUser(list, &new_user, username, password, 0);
            AddUser(list, new_user);
            
            printf("Pasien %s berhasil ditambahkan!\n\n", username);
        } else {
            printf("Registrasi gagal! Sudah ada User dengan nama %s.\n\n", username);
        }
    } else {
        printf("Anda sedang login! Logout terlebih dahulu!\n\n");
    }
}

