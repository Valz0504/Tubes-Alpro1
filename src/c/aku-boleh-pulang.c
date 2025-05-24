#include <stdio.h>
#include "../header/user.h"

void bolehPulangGaa(User *current_user, PenyakitList *dataPenyakit, ObatList *dataObat, Obat_PenyakitList *dataObatPenyakit, boolean *isLogin) {
    if (!(*isLogin)) {
        printf(RED "Anda belum login!\n\n" RESET);
        return;
    } 

    if (current_user->role == ROLE_PASIEN) {

        if (strcmp(current_user->riwayat_penyakit, "-") == 0) {
            printf(YELLOW "Kamu belum menerima diagnosis apapun dari dokter, jangan buru-buru pulang!\n\n" RESET);
            return;
        }

        if (strcmp(current_user->riwayat_penyakit, "Sehat") == 0) {
            printf(GREEN "Kamu sudah sehat dan boleh langsung pulang, sampai jumpa!\n\n" RESET);
            return;
        }

        printf(CYAN "Dokter sedang memeriksa keadaanmu...\n\n" RESET);
        int idPenyakit = getIDPenyakit(dataPenyakit, current_user->riwayat_penyakit);
        int indexDiMap = getMapIndexByPenyakit(dataObatPenyakit, idPenyakit);
        if (current_user->perut.length != dataObatPenyakit->buffer[indexDiMap].jumlah_obat) {
            printf(YELLOW "Masih ada obat yang belum kamu habiskan, minum semuanya dulu yukk!\n\n" RESET);
            return;
        }

        boolean bolehPulang = TRUE;
        for (int i = 0; i < current_user->perut.length; i++) {
            if (current_user->perut.data[i] != dataObatPenyakit->buffer[indexDiMap].urutan_obat[i]) {
                bolehPulang = FALSE;
            }
        }

        if (bolehPulang) {
            emptyStack(&current_user->perut);

            // reset data 
            strcpy(current_user->riwayat_penyakit, "-");
            current_user->suhu_tubuh = 0.0;
            current_user->tekanan_darah_sistolik = -1;
            current_user->tekanan_darah_diastolik = -1;
            current_user->detak_jantung = -1;
            current_user->saturasi_oksigen = 0.0;
            current_user->kadar_gula_darah = -1;
            current_user->berat_badan = 0.0;
            current_user->tinggi_badan = -1;
            current_user->kadar_kolesterol = -1;
            current_user->kadar_kolesterol_Ldl = -1;
            current_user->trombosit = -1;

            printf(GREEN BOLD "Selamat! Kamu sudah dinyatakan sembuh oleh dokter. Silahkan pulang dan semoga sehat selalu!\n\n" RESET);
        } else {
            printf(RED "Maaf, tapi kamu masih belum bisa pulang!\n\n" RESET);

            printf(CYAN "Urutan peminuman obat yang diharapkan:\n" RESET);
            printf(BLUE BOLD "  ");
            for (int i = 0; i < dataObatPenyakit->buffer[indexDiMap].jumlah_obat; i++) {
                printf("%s", getObatName(dataObat, dataObatPenyakit->buffer[indexDiMap].urutan_obat[i]));
                if (i != dataObatPenyakit->buffer[indexDiMap].jumlah_obat - 1) {
                    printf(" " YELLOW "->" BLUE BOLD " ");
                }
            }
            printf(RESET "\n");

            printf(MAGENTA "Urutan obat yang kamu minum:\n" RESET);
            printf(YELLOW "  ");
            for (int i = 0; i < current_user->perut.length; i++) {
                printf("%s", getObatName(dataObat, current_user->perut.data[i]));
                if (i != current_user->perut.length - 1) {
                    printf(" " YELLOW "->" YELLOW " ");
                }
            }
            printf(RESET "\n\n");

            printf(YELLOW "Silakan kunjungi dokter untuk meminta penawar yang sesuai!\n\n" RESET);
        }

    } else {
        printf(RED "Anda bukan pasien!\n\n" RESET);
    }
}