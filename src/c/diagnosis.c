#include <stdio.h>
#include <string.h>
#include "../header/user.h"

void diagnosis(User *current_user, PenyakitList *listPenyakit, boolean *isLogin) {
    if (!(*isLogin)) {
        printf("Login sebagai Dokter terlebih dahulu!\n\n");
        return;
    }

    if (current_user->role == ROLE_DOKTER) {
        printf("=== DIAGNOSIS PASIEN ===\n");

        if(current_user == NULL){
            printf("Tidak ada pasien untuk diperiksa!\n");
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
