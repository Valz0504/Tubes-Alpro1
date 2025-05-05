#include <stdio.h>
#include <string.h>
#include "header/user.h"

void diagnosis(User *u, PenyakitList *listPenyakit) {
    printf("=== DIAGNOSIS PASIEN ===\n");

    if(u == NULL){
        printf("Tidak ada pasien untuk diperiksa!\n");
    }
    else{
        boolean found = FALSE;

        for (int i = 0; i < listPenyakit->Neff; i++) {
            Penyakit p = listPenyakit->data[i];
    
            if (
                u->suhu_tubuh >= p.suhu_tubuh_Min && u->suhu_tubuh <= p.suhu_tubuh_Max &&
                u->tekanan_darah_sistolik >= p.tekanan_sistolik_Min && u->tekanan_darah_sistolik <= p.tekanan_sistolik_Max &&
                u->tekanan_darah_diastolik >= p.tekanan_diastolik_Min && u->tekanan_darah_diastolik <= p.tekanan_diastolik_Max &&
                u->detak_jantung >= p.detak_jantung_Min && u->detak_jantung <= p.detak_jantung_Max &&
                u->saturasi_oksigen >= p.saturasi_Min && u->saturasi_oksigen <= p.saturasi_Max &&
                u->kadar_gula_darah >= p.kadar_gula_Min && u->kadar_gula_darah <= p.kadar_gula_Max &&
                u->berat_badan >= p.berat_badan_Min && u->berat_badan <= p.berat_badan_Max &&
                u->tinggi_badan >= p.tinggi_badan_Min && u->tinggi_badan <= p.tinggi_badan_Max &&
                u->kadar_kolesterol >= p.kolesterol_Min && u->kadar_kolesterol <= p.kolesterol_Max &&
                u->trombosit >= p.trombosit_Min && u->trombosit <= p.trombosit_Max
            ) {
                printf("%s terdiagnosa penyakit %s\n", u->username, p.nama);
                strncpy(u->riwayat_penyakit, p.nama, sizeof(u->riwayat_penyakit));
                found = TRUE;
                break; 
            }
        }
    
        if (!found) {
            printf("%s tidak terdiagnosa penyakit apapun\n", u->username);
            strcpy(u->riwayat_penyakit, "Sehat");
            u->riwayat_penyakit[sizeof(u->riwayat_penyakit) - 1] = '\0';
        }
    }
}
