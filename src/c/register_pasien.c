#include <stdio.h>
#include <string.h>

#include "../header/user.h"
#include "../header/set.h"
#include "../header/boolean.h"

void registerPasien(UserList *list, Set *set, boolean *isLogin) {
    if (!(*isLogin)) {
        printf("=== REGISTER ===\n");
        char username[100], password[100];
        
        printf("Username: ");
        scanf("%s", username);
        printf("Password: ");
        scanf("%s", password);

        toLower(username);
        if (isUsernameUnique(*set, username)) {
            insertSet(set, username);

            User new_user;
            CreateUser(list, &new_user, username, password, 0);
            AddUser(list, new_user);
            
            printf("Pasien %s berhasil ditambahkan!\n\n", username);
        } else {
            printf("Registrasi gagal! User dengan nama %s sudah terdaftar.\n\n", username);
        }
    } else {
        printf("Anda sedang login!\n\n");
    }
}

