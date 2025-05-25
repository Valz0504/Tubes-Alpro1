#include <stdio.h>
#include <string.h>
#include "../header/user.h"

void antrianSaya(User *current_user, Matrix *denah, boolean *isLogin) {
    if (!(*isLogin)) {
        printf("Login sebagai Pasien terlebih dahulu!\n\n");
        return;
    }

    if (current_user->role == ROLE_PASIEN) {
        int ditemukan = 0;

        for (int i = 0; i < denah->rows; i++) {
            for (int j = 0; j < denah->cols; j++) {
                Queue antrian = denah->data[i][j].antrian;
                Node *curr = antrian.head;
                
                int panjangAntriLuar = countQueue(antrian) - denah->kapasitasRuangan;
                int posisiPasien = 1;
                
                while (curr != NULL) {
                    if (curr->info == current_user->id) {
                        if (posisiPasien > denah->kapasitasRuangan) {
                            posisiPasien -= denah->kapasitasRuangan;
                        } else {
                            printf(YELLOW "Anda sedang berada di dalam ruangan dokter!\n\n" RESET);
                            return;
                        }
                        printf("Status antrian Anda: \n");
                        printf("Dokter: %s\n", denah->data[i][j].nama_dokter);
                        printf("Ruangan: %c%d\n", 'A'+i, j+1);
                        printf("Posisi antrian: %d dari %d\n\n", posisiPasien, panjangAntriLuar);
                        ditemukan = 1;
                        break;
                    }
                    curr = curr->next;
                    posisiPasien++;
                }
                if (ditemukan) break;
            }
            if (ditemukan) break;
        }

        if (!ditemukan) {
            printf("\nAnda belum terdaftar dalam antrian check-up!\n");
            printf("Silahkan daftar terlebih dahulu dengan command DAFTAR_CHECKUP\n\n");
        }
    } else {
        printf("Anda bukan pasien! Tidak bisa lihat antrian!\n\n");
    }
}