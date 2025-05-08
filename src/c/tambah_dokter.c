#include <stdio.h>
#include <string.h>

#include "user.h"
#include "set.h"
#include "boolean.h"

void tambahDokter(UserList *list, Set *set) {
    printf("=== TAMBAH DOKTER ===\n");
    char username[100], password[100];
    
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

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
}

