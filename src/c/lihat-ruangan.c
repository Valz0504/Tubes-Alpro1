#include <stdio.h>
#include <string.h>
#include "../header/user.h"
#include "../header/matrix.h"
#include "../header/queue.h"

void lihatRuangan(Matrix denah, UserList dataBaseUser, User current_user, boolean *isLogin) {
    if (!(*isLogin)) {
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
    
    Node *curr = R->antrian.head;
    int index = 0;

    while (curr != NULL && index < denah.kapasitasRuangan) {
        User *pasien = findUserByID(&dataBaseUser, curr->info);
        if (pasien != NULL) {
            printf("    %d. %s\n", index + 1, pasien->username);
            index++;
        }
        curr = curr->next;
    }
    if (index == 0) {
        printf("    Tidak ada pasien di dalam ruangan saat ini.\n");
    }
    printf("----------------------------\n\n");
}