#include <stdio.h>
#include "../header/user.h"

void lihatAntrian(UserList *dataBaseUser, User *currentUser, Matrix *denah, boolean *isLogin) {
    if (!(*isLogin)) {
        printf(RED "Login sebagai Manager terlebih dahulu!\n\n" RESET);
        return;
    }

    if (currentUser->role == ROLE_MANAGER) {
        denahRumahSakit(*denah, isLogin);

        int adaAntrian = 0;
        // cari setiap indeks yang ada dokternya
        for (int i = 0; i < denah->rows; i++) {
            for (int j = 0; j < denah->cols; j++) {
                if (!isRuanganKosong(denah->data[i][j])) {
                    adaAntrian = 1;
                    printf(BLUE BOLD "============ %c%d ============\n" RESET, 'A' + i, j + 1);
                    printf(GRAY "Kapasitas   : " RESET YELLOW "%d\n" RESET, denah->kapasitasRuangan);
                    printf(GRAY "Dokter      : " RESET CYAN "%s\n" RESET, denah->data[i][j].namaDokter);

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

        if (!adaAntrian) {
            printf(YELLOW "Tidak ada satu pun ruangan yang memiliki pasien ataupun dokter!\n\n" RESET);
            return;
        }

    } else {
        printf(RED "Anda bukan manager! Tidak bisa lihat semua antrian!\n\n" RESET);
    }
}