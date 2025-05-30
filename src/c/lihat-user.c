#include <stdio.h>
#include <string.h>
#include "../header/user.h"

void lihatUser(UserList *dataBaseUser, User *current_user, boolean *isLogin) {
    if (!(*isLogin) || current_user->role != ROLE_MANAGER) {
        printf(RED "Login sebagai Manager terlebih dahulu!\n\n" RESET);
        return;
    }

    if (current_user->role == ROLE_MANAGER) {
        int urutan, arahSort;
        printf(CYAN "Urutkan berdasarkan?\n" RESET);
        printf(GRAY "1. ID\n2. Nama\n" RESET);
        printf(GRAY ">> Pilihan: " RESET);
        scanf("%d", &urutan);

        printf(CYAN "Urutan sort?\n" RESET);
        printf(GRAY "1. A-Z\n2. Z-A\n" RESET);
        printf(GRAY ">> Pilihan: " RESET);
        scanf("%d", &arahSort);

        UserList temp;
        copyList(*dataBaseUser, &temp);

        if (urutan == 1) {    // lihat berdasarkan ID
            if (arahSort == 1) sortListByID(&temp, 1);
            else if (arahSort == 2) sortListByID(&temp, 0);
        } else if (urutan == 2) {    // lihat berdasarkan namaq
            if (arahSort == 1) sortListByUsername(&temp, 1);
            else if (arahSort == 2) sortListByUsername(&temp, 0);
        } else {
            printf(RED "Pilihan tidak valid!" RESET);
        }

        printf(BLUE BOLD "\n+-----+--------------------+-----------+----------------------+\n" RESET);
        printf(BLUE BOLD "| ID  | Nama               | Role      | Penyakit             |\n" RESET);
        printf(BLUE BOLD "+-----+--------------------+-----------+----------------------+\n" RESET);
        for (int i = 0; i < temp.Neff; i++) {
            User u = temp.data[i];
            printf(GRAY " %-3d " RESET " | " GRAY "%-18s" RESET " | " YELLOW "%-9s" RESET " | " YELLOW "%-20s" RESET " |\n",
                u.id, u.username, roleToStr(u.role), u.riwayat_penyakit);
        }
        printf(BLUE BOLD "+-----+--------------------+-----------+----------------------+\n\n" RESET);
        dealocateListDin(&temp);
    }
}

void lihatPasien(UserList *dataBaseUser, User *current_user, boolean *isLogin) {
    if (!(*isLogin) || current_user->role != ROLE_MANAGER) {
        printf(RED "Login sebagai Manager terlebih dahulu!\n\n" RESET);
        return;
    }

    if (current_user->role == ROLE_MANAGER) {
        int urutan, arahSort;
        printf(CYAN "Urutkan berdasarkan?\n" RESET);
        printf(GRAY "1. ID\n2. Nama\n" RESET);
        printf(GRAY ">> Pilihan: " RESET);
        scanf("%d", &urutan);

        printf(CYAN "Urutan sort?\n" RESET);
        printf(GRAY "1. A-Z\n2. Z-A\n" RESET);
        printf(GRAY ">> Pilihan: " RESET);
        scanf("%d", &arahSort);

        UserList temp;
        CreateListDin(&temp, dataBaseUser->capacity);
        for (int i = 0; i < dataBaseUser->Neff; i++) {
            if (dataBaseUser->data[i].role == ROLE_PASIEN) {
                AddUser(&temp, &dataBaseUser->data[i]);
            }
        }

        if (urutan == 1) {
            sortListByID(&temp, arahSort == 1);
        } else {
            sortListByUsername(&temp, arahSort == 1);
        }

        printf(BLUE BOLD "\n+-----+--------------------+----------------------+\n" RESET);
        printf(BLUE BOLD "| ID  | Nama               | Penyakit             |\n" RESET);
        printf(BLUE BOLD "+-----+--------------------+----------------------+\n" RESET);
        for (int i = 0; i < temp.Neff; i++) {
            User u = temp.data[i];
            printf(GRAY " %-3d " RESET " | " GRAY "%-18s" RESET " | " YELLOW "%-20s" RESET " |\n",
                u.id, u.username, u.riwayat_penyakit);
        }
        printf(BLUE BOLD "+-----+--------------------+----------------------+\n\n" RESET);

        dealocateListDin(&temp);
    }
}

void lihatDokter(UserList *dataBaseUser, User *current_user, boolean *isLogin) {
    if (!(*isLogin) || current_user->role != ROLE_MANAGER) {
        printf(RED "Login sebagai Manager terlebih dahulu!\n\n" RESET);
        return;
    }

    if (current_user->role == ROLE_MANAGER) {
        int urutan, arahSort;
        printf(CYAN "Urutkan berdasarkan?\n" RESET);
        printf(GRAY "1. ID\n2. Nama\n3. Aura\n" RESET);
        printf(GRAY ">> Pilihan: " RESET);
        scanf("%d", &urutan);

        printf(CYAN "Urutan sort?\n" RESET);
        printf(GRAY "1. A-Z\n2. Z-A\n" RESET);
        printf(GRAY ">> Pilihan: " RESET);
        scanf("%d", &arahSort);

        UserList temp;
        CreateListDin(&temp, dataBaseUser->capacity);
        for (int i = 0; i < dataBaseUser->Neff; i++) {
            if (dataBaseUser->data[i].role == ROLE_DOKTER) {
                AddUser(&temp, &dataBaseUser->data[i]);
            }
        }

        if (urutan == 1) {
            sortListByID(&temp, arahSort == 1);
        } else if (urutan == 2){
            sortListByUsername(&temp, arahSort == 1);
        } else if (urutan == 3) {
            sortListByAura(&temp, arahSort == 1);

            printf(BLUE BOLD "\n+-----+--------------------+------+\n" RESET);
            printf(BLUE BOLD "| ID  | Nama               | Aura |\n" RESET);
            printf(BLUE BOLD "+-----+--------------------+------+\n" RESET);
            for (int i = 0; i < temp.Neff; i++) {
                User u = temp.data[i];
                printf(GRAY " %-3d " RESET " | " GRAY "%-18s" RESET " | " YELLOW "%-4d" RESET " |\n", u.id, u.username, u.aura);
            }
            printf(BLUE BOLD "+-----+--------------------+------+\n\n" RESET);
            return;
        }

        printf(BLUE BOLD "\n+-----+--------------------+\n" RESET);
        printf(BLUE BOLD "| ID  | Nama               |\n" RESET);
        printf(BLUE BOLD "+-----+--------------------+\n" RESET);
        for (int i = 0; i < temp.Neff; i++) {
            User u = temp.data[i];
            printf(GRAY " %-3d " RESET " | " GRAY "%-18s" RESET " |\n", u.id, u.username);
        }
        printf(BLUE BOLD "+-----+--------------------+\n\n" RESET);

        dealocateListDin(&temp);
    }
}