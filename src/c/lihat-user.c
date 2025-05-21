#include <stdio.h>
#include <string.h>
#include "../header/user.h"

void lihatUser(UserList *dataBaseUser, User *current_user, boolean *isLogin) {
    if (!(*isLogin) || current_user->role != ROLE_MANAGER) {
        printf("Login sebagai Manager terlebih dahulu!\n\n");
        return;
    }

    if (current_user->role == ROLE_MANAGER) {
        int urutan, arahSort;
        printf("Urutkan berdasarkan?\n");
        printf("1. ID\n");
        printf("2. Nama\n");
        printf(">> Pilihan: ");
        scanf("%d", &urutan);

        printf("Urutan sort?\n");
        printf("1. A-Z\n");
        printf("2. Z-A\n");
        printf(">> Pilihan: ");
        scanf("%d", &arahSort);

        UserList temp;
        copyList(*dataBaseUser, &temp);

        if (urutan == 1) {
            sortListByID(&temp, arahSort == 1);
        } else {
            sortListByUsername(&temp, arahSort == 1);
        }

        printf("\nID | Nama             | Role     | Penyakit\n");
        printf("----------------------------------------------\n");
        for (int i = 0; i < temp.Neff; i++) {
            User u = temp.data[i];
            printf("%2d | %-16s | %-8s | %s\n", u.id, u.username, roleToStr(u.role), u.riwayat_penyakit);
        }
        printf("\n");
        dealocateListDin(&temp);
    }
}
void lihatPasien(UserList *dataBaseUser, User *current_user, boolean *isLogin) {
    if (!(*isLogin) || current_user->role != ROLE_MANAGER) {
        printf("Login sebagai Manager terlebih dahulu!\n\n");
        return;
    }

    if (current_user->role == ROLE_MANAGER) {
        int urutan, arahSort;
        printf("Urutkan berdasarkan?\n");
        printf("1. ID\n");
        printf("2. Nama\n");
        printf(">> Pilihan: ");
        scanf("%d", &urutan);

        printf("Urutan sort?\n");
        printf("1. A-Z\n");
        printf("2. Z-A\n");
        printf(">> Pilihan: ");
        scanf("%d", &arahSort);

        UserList temp;
        CreateListDin(&temp, dataBaseUser->capacity);
        for (int i = 0; i < dataBaseUser->Neff; i++) {
            if (dataBaseUser->data[i].role == ROLE_PASIEN) {
                AddUser(&temp, dataBaseUser->data[i]);
            }
        }

        if (urutan == 1) {
            sortListByID(&temp, arahSort == 1);
        } else {
            sortListByUsername(&temp, arahSort == 1);
        }

        printf("\nID | Nama             | Penyakit\n");
        printf("--------------------------------------\n");
        for (int i = 0; i < temp.Neff; i++) {
            User u = temp.data[i];
            printf("%2d | %-16s | %s\n", u.id, u.username, u.riwayat_penyakit);
        }
        printf("\n");

        dealocateListDin(&temp);
    }
}

void lihatDokter(UserList *dataBaseUser, User *current_user, boolean *isLogin) {
    if (!(*isLogin) || current_user->role != ROLE_MANAGER) {
        printf("Login sebagai Manager terlebih dahulu!\n\n");
        return;
    }

    if (current_user->role == ROLE_MANAGER) {
        int urutan, arahSort;
        printf("Urutkan berdasarkan?\n");
        printf("1. ID\n");
        printf("2. Nama\n");
        printf(">> Pilihan: ");
        scanf("%d", &urutan);

        printf("Urutan sort?\n");
        printf("1. A-Z\n");
        printf("2. Z-A\n");
        printf(">> Pilihan: ");
        scanf("%d", &arahSort);

        UserList temp;
        CreateListDin(&temp, dataBaseUser->capacity);
        for (int i = 0; i < dataBaseUser->Neff; i++) {
            if (dataBaseUser->data[i].role == ROLE_DOKTER) {
                AddUser(&temp, dataBaseUser->data[i]);
            }
        }

        if (urutan == 1) {
            sortListByID(&temp, arahSort == 1);
        } else {
            sortListByUsername(&temp, arahSort == 1);
        }

        printf("\nID | Nama\n");
        printf("-------------------\n");
        for (int i = 0; i < temp.Neff; i++) {
            User u = temp.data[i];
            printf("%2d | %s\n", u.id, u.username);
        }
        printf("\n");

        dealocateListDin(&temp);
    }
}