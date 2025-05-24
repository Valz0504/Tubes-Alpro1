#include <stdio.h>
#include "../header/user.h"

void lihatAntrian(UserList *dataBaseUser, User *current_user, Matrix *denah, boolean *isLogin) {
    if (!(*isLogin)) {
        printf(RED "Login sebagai Manager terlebih dahulu!\n\n" RESET);
        return;
    }

    if (current_user->role == ROLE_MANAGER) {
        denahRumahSakit(*denah);

        for (int i = 0; i < denah->rows; i++) {
            for (int j = 0; j < denah->cols; j++) {
                if (!isRuanganKosong(denah->data[i][j])) {
                    printf(BLUE BOLD "============ %c%d ============\n" RESET, 'A' + i, j + 1);
                    printf(GRAY "Kapasitas   : " RESET YELLOW "%d\n" RESET, denah->kapasitasRuangan);
                    printf(GRAY "Dokter      : " RESET CYAN "%s\n" RESET, denah->data[i][j].nama_dokter);

                    Node *curr = denah->data[i][j].antrian.head;
                    printf(GRAY "Pasien di antrian dalam ruangan:\n" RESET);
                    if (!isEmpty(denah->data[i][j].antrian)) {
                        int index = 0;
                        while (curr != NULL && index < denah->kapasitasRuangan) {
                            User *pasien = findUserByID(dataBaseUser, curr->info);
                            printf(YELLOW "\t%d. %s\n" RESET, index + 1, pasien->username);
                            curr = curr->next;
                            index++;
                        }

                        printf(GRAY "Pasien di antrian luar ruangan:\n" RESET);
                        if (curr == NULL) {
                            printf(YELLOW "\tTidak ada pasien di antrian luar ruangan saat ini.\n\n" RESET);
                        } else {
                            index = 1;
                            while (curr != NULL) {
                                User *pasien = findUserByID(dataBaseUser, curr->info);
                                printf(YELLOW "\t%d. %s\n" RESET, index, pasien->username);
                                curr = curr->next;
                                index++;
                            }
                        }

                    } else {
                        printf(YELLOW "\tTidak ada pasien di antrian dalam ruangan saat ini.\n" RESET);
                        printf(GRAY "Pasien di antrian luar ruangan:\n" RESET);
                        printf(YELLOW "\tTidak ada pasien di antrian luar ruangan saat ini.\n" RESET);
                    }

                    printf("\n");
                }
            }
        }

    } else {
        printf(RED "Anda bukan manager! Tidak bisa lihat semua antrian!\n\n" RESET);
    }
}