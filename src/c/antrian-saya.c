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
                int posisi = 1;

                while (curr != NULL) {
                    if (curr->info == current_user->id) {
                        printf("\nStatus antrian Anda:\n");
                        if (strlen(denah->data[i][j].nama_dokter) > 0) {
                            printf("Dokter: Dr. %s\n", denah->data[i][j].nama_dokter);
                        } else {
                            printf("Dokter belum ditentukan untuk ruangan ini.\n");
                        }
                        printf("Ruangan: %c%d\n", 'A' + j, i + 1);
                        
                        int totalAntrian = 0;
                        Node *hit = antrian.head;
                        while (hit != NULL) {
                            totalAntrian++;
                            hit = hit->next;
                        }
                        printf("Posisi antrian: %d dari %d\n", posisi, totalAntrian);

                        ditemukan = 1;
                        break;
                    }
                    curr = curr->next;
                    posisi++;
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