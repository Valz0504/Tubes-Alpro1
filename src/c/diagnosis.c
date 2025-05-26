#include <stdio.h>
#include <string.h>
#include "../header/user.h"

void diagnosis(User *current_user, UserList *listUser, PenyakitList *listPenyakit, boolean *isLogin, Matrix *denah) {
    if (!(*isLogin)) {
        printf(RED "Login sebagai Dokter terlebih dahulu!\n\n" RESET);
        return;
    }

    int row, col;
    boolean foundRuangan = FALSE;

    if (current_user->role == ROLE_DOKTER) {
        // Cari ruangan dokter berdasarkan username
        for (int i = 0; i < denah->rows; i++) {
            for (int j = 0; j < denah->cols; j++) {
                if (strcmp(current_user->username, denah->data[i][j].nama_dokter) == 0) {
                    row = i;
                    col = j;
                    foundRuangan = TRUE;
                }
            }
        }

        if (!foundRuangan) {
            printf(YELLOW "Anda belum ditugaskan ke ruangan manapun.\n\n" RESET);
            return;
        }

        Queue *antrian = &denah->data[row][col].antrian;
        if (antrian->head == NULL) {
            printf(CYAN "Tidak ada pasien untuk diperiksa!\n\n" RESET);
            return;
        }

        int idPasien = antrian->head->info;
        User *pasien = findUserByID(listUser, idPasien);

        if (pasien == NULL) {
            printf(RED "Data pasien tidak ditemukan.\n\n" RESET);
            return;
        }

        if (pasien->inventory.jumlahObat > 0 || strcmp(pasien->riwayat_penyakit, "-") != 0) {
            denah->data[row][col].serving = TRUE;
        }
        if (denah->data[row][col].serving) {
            printf(GREEN "Anda sudah mendiagnosis %s.\n\n" RESET, pasien->username);
            return;
        }

        printf(CYAN "%s sedang dicek...\n\n" RESET, pasien->username);
        boolean foundPenyakit = FALSE;

        for (int i = 0; i < listPenyakit->Neff; i++) {
            Penyakit p = listPenyakit->data[i];

            if (
                pasien->suhu_tubuh >= p.suhu_tubuh_Min && pasien->suhu_tubuh <= p.suhu_tubuh_Max &&
                pasien->tekanan_darah_sistolik >= p.tekanan_sistolik_Min && pasien->tekanan_darah_sistolik <= p.tekanan_sistolik_Max &&
                pasien->tekanan_darah_diastolik >= p.tekanan_diastolik_Min && pasien->tekanan_darah_diastolik <= p.tekanan_diastolik_Max &&
                pasien->detak_jantung >= p.detak_jantung_Min && pasien->detak_jantung <= p.detak_jantung_Max &&
                pasien->saturasi_oksigen >= p.saturasi_Min && pasien->saturasi_oksigen <= p.saturasi_Max &&
                pasien->kadar_gula_darah >= p.kadar_gula_Min && pasien->kadar_gula_darah <= p.kadar_gula_Max &&
                pasien->berat_badan >= p.berat_badan_Min && pasien->berat_badan <= p.berat_badan_Max &&
                pasien->tinggi_badan >= p.tinggi_badan_Min && pasien->tinggi_badan <= p.tinggi_badan_Max &&
                pasien->kadar_kolesterol >= p.kolesterol_Min && pasien->kadar_kolesterol <= p.kolesterol_Max &&
                pasien->trombosit >= p.trombosit_Min && pasien->trombosit <= p.trombosit_Max
            ) {
                printf(GREEN "%s terdiagnosa penyakit %s!\n\n" RESET, pasien->username, p.nama);
                strncpy(pasien->riwayat_penyakit, p.nama, sizeof(pasien->riwayat_penyakit));
                foundPenyakit = TRUE;
                break;
            }
        }

        if (!foundPenyakit) {
            printf(YELLOW "%s tidak terdiagnosa penyakit apapun\n\n" RESET, pasien->username);
            strcpy(pasien->riwayat_penyakit, "Sehat");
            pasien->riwayat_penyakit[sizeof(pasien->riwayat_penyakit) - 1] = '\0';
        }
    } else {
        printf(RED "Anda bukan dokter! Tidak bisa diagnosis pasien!\n\n" RESET);
    }
}
