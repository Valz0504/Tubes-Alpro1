#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header/user.h"

void lihatRuangan(Matrix denah, UserList dataBaseUser, User current_user, boolean *isLogin) {
    if (!(*isLogin)) {
        printf(RED "Silakan login terlebih dahulu!\n\n" RESET);
        return;
    }
    char kode[5];
    int row, col;
    scanf("%s", kode);

    row = kode[0] - 'A';
    col = atoi(&kode[1]) - 1;

    if (row >= 0 && row < denah.rows && col >= 0 && col < denah.cols) {
        printf(BLUE BOLD "--- Detail Ruangan %s ---\n" RESET, kode);
        printf(GRAY "Kapasitas : " YELLOW "%d\n" RESET, denah.kapasitasRuangan);

        if (strcmp(denah.data[row][col].nama_dokter, "") == 0) {
            printf(GRAY "Dokter    : " RESET RED "-\n" RESET);
        } else {
            printf(GRAY "Dokter    : " RESET CYAN "%s\n" RESET, denah.data[row][col].nama_dokter);
        }

        printf(GRAY "Pasien di dalam ruangan:\n" RESET);

        Node *curr = denah.data[row][col].antrian.head;
        if (!isEmpty(denah.data[row][col].antrian)) {
            int index = 0;
            while (curr != NULL && index < denah.kapasitasRuangan) {
                User *pasien = findUserByID(&dataBaseUser, curr->info);
                if (pasien != NULL) {
                    printf(BRIGHT_BLACK "    %d. %s\n" RESET, index + 1, pasien->username);
                    index++;
                }
                curr = curr->next;
            }
        } else {
            printf(YELLOW "Tidak ada pasien di dalam ruangan ini.\n\n" RESET);
            printf(BLUE "-------------------------\n\n" RESET);
            return;
        }
        printf(BLUE "-------------------------\n\n" RESET);
    } else {
        printf(RED "Ruangan tidak ditemukan dalam denah.\n\n" RESET);
        return;
    }
}