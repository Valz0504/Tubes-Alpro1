#include <stdio.h>
#include <string.h>
#include "../header/user.h"
#include "../header/matrix.h"
#include "../header/queue.h"

void lihatRuangan(Matrix denah, UserList dataBaseUser, User current_user, boolean isLogin) {
    if (!isLogin) {
        printf("Silakan login terlebih dahulu!\n\n");
        return;
    }
    char kode[5];
    int row, col;
    scanf("%s", kode);

    if (!getPosisiRuangan(&denah, kode, &row, &col) || row >= denah.rows || col >= denah.cols) {
        printf("Ruangan tidak ditemukan dalam denah.\n\n");
        return;
    }

    Ruangan *R = &denah.data[row][col];

    printf("\n--- Detail Ruangan %s ---\n", kode);
    printf("Kapasitas : %d\n", denah.kapasitasRuangan);
    printf("Dokter    : %s\n", strlen(R->nama_dokter) > 0 ? R->nama_dokter : "-");

    printf("Pasien di dalam ruangan:\n");

    if (isEmpty(R->antrian)) {
        printf("    Tidak ada pasien di dalam ruangan saat ini.\n");
    } else {
        Node *curr = R->antrian.head;
        int index = 0;
        while (curr != NULL && index < denah.kapasitasRuangan) {
            User *pasien = findUserByID(&dataBaseUser, curr->info);
            if (pasien != NULL) {
                printf("    %d. %s\n", index + 1, pasien->username);
            } else {
                printf("    %d. Pasien ID %d (tidak ditemukan)\n", index + 1, curr->info);
            }
            curr = curr->next;
            index++;
        }
        if (curr != NULL) {
            printf("Pasien di dalam antrian: Tidak ditampilkan\n");
        } else {
            printf("Pasien di dalam antrian: Tidak ada pasien di dalam antrian saat ini.\n");
        }
    }
    printf("----------------------------\n\n");
}