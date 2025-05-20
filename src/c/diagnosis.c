#include <stdio.h>
#include <string.h>
#include "../header/user.h"

void diagnosis(User *current_user, UserList *listUser, PenyakitList *listPenyakit, boolean *isLogin, Matrix *denah) {
    if (!(*isLogin)) {
        printf("Login sebagai Dokter terlebih dahulu!\n\n");
        return;
    }

    int row, col;
    boolean foundRuangan = FALSE;
    if (current_user->role == ROLE_DOKTER) {
        for (int i = 0; i < denah->rows; i++){
            for (int j = 0; j < denah->cols; j++){
                if (strcmp(current_user->username, denah->data[i][j].nama_dokter)){
                    row =  i;
                    col = j;
                    foundRuangan = TRUE;
                }
            }
        }

        if (!foundRuangan) {
        printf("Dokter %s belum ditugaskan ke ruangan manapun.\n\n", current_user->username);
        return;
        }

        Queue *antrian = &denah->data[row][col].antrian;

        
        if (antrian->head == NULL) {
            printf("Tidak ada pasien dalam antrian untuk diperiksa!\n\n");
            return;
        }

        int idPasien = antrian->head->info;

        // Cari User dengan ID sesuai
        User *pasien = NULL;
        for (int i = 0; i < listUser->Neff; i++) {
            if (listUser->data[i].id == idPasien) {
                pasien = &listUser->data[i];
                break;
            }
        }


        printf("=== DIAGNOSIS PASIEN ===\n");

        if (pasien == NULL) {
            printf("Data pasien tidak ditemukan.\n\n");
            return;
        }
        else{
            boolean found = FALSE;

            for (int i = 0; i < listPenyakit->Neff; i++) {
                Penyakit p = listPenyakit->data[i];
        
                if (
                    current_user->suhu_tubuh >= p.suhu_tubuh_Min && current_user->suhu_tubuh <= p.suhu_tubuh_Max &&
                    current_user->tekanan_darah_sistolik >= p.tekanan_sistolik_Min && current_user->tekanan_darah_sistolik <= p.tekanan_sistolik_Max &&
                    current_user->tekanan_darah_diastolik >= p.tekanan_diastolik_Min && current_user->tekanan_darah_diastolik <= p.tekanan_diastolik_Max &&
                    current_user->detak_jantung >= p.detak_jantung_Min && current_user->detak_jantung <= p.detak_jantung_Max &&
                    current_user->saturasi_oksigen >= p.saturasi_Min && current_user->saturasi_oksigen <= p.saturasi_Max &&
                    current_user->kadar_gula_darah >= p.kadar_gula_Min && current_user->kadar_gula_darah <= p.kadar_gula_Max &&
                    current_user->berat_badan >= p.berat_badan_Min && current_user->berat_badan <= p.berat_badan_Max &&
                    current_user->tinggi_badan >= p.tinggi_badan_Min && current_user->tinggi_badan <= p.tinggi_badan_Max &&
                    current_user->kadar_kolesterol >= p.kolesterol_Min && current_user->kadar_kolesterol <= p.kolesterol_Max &&
                    current_user->trombosit >= p.trombosit_Min && current_user->trombosit <= p.trombosit_Max
                ) {
                    printf("%s terdiagnosa penyakit %s\n", current_user->username, p.nama);
                    strncpy(current_user->riwayat_penyakit, p.nama, sizeof(current_user->riwayat_penyakit));
                    found = TRUE;
                    break; 
                }
            }
        
            if (!found) {
                printf("%s tidak terdiagnosa penyakit apapun\n", current_user->username);
                strcpy(current_user->riwayat_penyakit, "Sehat");
                current_user->riwayat_penyakit[sizeof(current_user->riwayat_penyakit) - 1] = '\0';
            }
        }
    } else {
        printf("Anda bukan dokter! Tidak bisa diagnosis pasien!\n\n");
    }
}
