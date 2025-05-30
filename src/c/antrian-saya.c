#include <stdio.h>
#include <string.h>
#include "../header/user.h"

void antrianSaya(User *current_user, Matrix *denah, boolean *isLogin) {
    if (!(*isLogin)) {
        printf(RED "Login sebagai Pasien terlebih dahulu!\n\n" RESET);
        return;
    }

    if (current_user->role == ROLE_PASIEN) {
        int ditemukan = 0;


        // cari di mana pasien berada di denah
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
                            printf(YELLOW BOLD "Anda sedang berada di dalam ruangan dokter!\n\n" RESET);
                            return;
                        }
                        printf(CYAN BOLD "=== Status Antrian Anda ===\n" RESET);
                        printf(GRAY "Dokter: " RESET YELLOW "%s\n" RESET, denah->data[i][j].namaDokter);
                        printf(GRAY "Ruangan: " RESET YELLOW "%c%d\n" RESET, 'A' + i, j + 1);
                        printf(GRAY "Posisi Antrian: " RESET YELLOW "%d dari %d\n\n" RESET, posisiPasien, panjangAntriLuar);
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
            printf(RED "\nAnda belum terdaftar dalam antrian check-up!\n" RESET);
            printf(CYAN "Silahkan daftar terlebih dahulu dengan command " YELLOW BOLD "DAFTAR_CHECKUP\n\n" RESET);
        }
    } else {
        printf(RED "Anda bukan pasien! Tidak bisa lihat antrian!\n\n" RESET);
    }
}