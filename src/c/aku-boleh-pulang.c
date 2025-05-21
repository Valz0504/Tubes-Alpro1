#include <stdio.h>
#include "../header/user.h"

void bolehPulangGaa(User *current_user, PenyakitList *dataPenyakit, ObatList *dataObat, Obat_PenyakitList *dataObatPenyakit, boolean *isLogin) {
    if (!(*isLogin)) {
        printf("Anda belum login!\n\n");
        return;
    } 

    if (current_user->role == ROLE_PASIEN) {

        if (strcmp(current_user->riwayat_penyakit, "-") == 0) {
            printf("Kamu belum menerima diagnosis apapun dari dokter, jangan buru-buru pulang!\n\n");
            return;
        }

        printf("Dokter sedang memeriksa keadaanmu...\n\n");
        int idPenyakit = getIDPenyakit(dataPenyakit, current_user->riwayat_penyakit);
        int indexDiMap = getMapIndexByPenyakit(dataObatPenyakit, idPenyakit);
        if (current_user->perut.length != dataObatPenyakit->buffer[indexDiMap].jumlah_obat) {
            printf("Masih ada obat yang belum kamu habiskan, minum semuanya dulu yukk!\n\n");
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
            printf("Selamat! Kamu sudah dinyatakan sembuh oleh dokter. Silahkan pulang dan semoga sehat selalu!\n\n");
        } else {
            printf("Maaf, tapi kamu masih belum bisa pulang!\n\n");

            printf("Urutan peminuman obat yang diharapkan: \n");
            for (int i = 0; i < dataObatPenyakit->buffer[indexDiMap].jumlah_obat; i++) {
                printf("%s", getObatName(dataObat, dataObatPenyakit->buffer[indexDiMap].urutan_obat[i]));
                if (i != dataObatPenyakit->buffer[indexDiMap].jumlah_obat - 1) {
                    printf(" -> ");
                }
            }
            printf("\n\n");

            printf("Urutan obat yang kamu minum:\n");
            for (int i = 0; i < current_user->perut.length; i++) {
                printf("%s", getObatName(dataObat, current_user->perut.data[i]));
                if (i != current_user->perut.length - 1) {
                    printf(" -> ");
                }
            }
            printf("\n\n");

            printf("Silakan kunjungi dokter untuk meminta penawar yang sesuai!\n\n");
        }

    } else {
        printf("Anda bukan pasien!\n\n");
    }
}