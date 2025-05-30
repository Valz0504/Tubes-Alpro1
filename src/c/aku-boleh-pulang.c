#include <stdio.h>
#include "../header/user.h"

void bolehPulangGaa(User *currentUser, UserList *dataBaseUser, PenyakitList *dataPenyakit, ObatList *dataObat, Obat_PenyakitList *dataObatPenyakit, Matrix *denah, boolean *isLogin) {
    if (!(*isLogin)) {
        printf(RED "Anda belum login!\n\n" RESET);
        return;
    } 
    if (currentUser->role == ROLE_PASIEN) {
        User *pasien = findUser(dataBaseUser, currentUser->username);
        
        int row,col;
        Queue *antrianPasien = NULL;
        boolean isFront = FALSE;
        boolean isInQueue = FALSE;

        // cari apakah pasien sudah ada di antrian atau tidak
        for (int i = 0; i < denah->rows; i++) { 
            for (int j = 0; j < denah->cols; j++) {
                Queue *antrian = &denah->data[i][j].antrian;
                Node *curr = antrian->head;

                while (curr != NULL) {
                    if (curr->info == pasien->id) {
                        row = i; col = j;
                        isInQueue = TRUE;
                        if (curr == antrian->head) {
                            isFront = TRUE;
                            antrianPasien = antrian;
                        }
                        break;
                    }
                    curr = curr->next;
                }
            }
        }

        // jika di belum ada di antrian tidak bisa pulangdok
        if (!isInQueue) {
            printf(YELLOW "Kamu belum berada di antrian mana pun!\n\n" RESET);
            return;
        }

        // jika ada di antrian tapi tidak paling depan, tidak bisa pulang dok
        if (!isFront) {
            printf(YELLOW "Belum giliranmu untuk diperiksa, mohon bersabar!\n\n" RESET);
            return;
        }

        // jika pasien belum didiagnosis tidak bisa pulangdok
        if (strcmp(pasien->riwayatPenyakit, "-") == 0) {
            printf(YELLOW "Kamu belum menerima diagnosis apapun dari dokter, jangan buru-buru pulang!\n\n" RESET);
            return;
        }

        // jika pasien sehat tidak bisa pulangdok
        printf(CYAN "Dokter sedang memeriksa keadaanmu...\n\n" RESET);
        sleep(1);
        if (strcmp(pasien->riwayatPenyakit, "Sehat") == 0) {
            printf(GREEN BOLD "Kamu sudah sehat dan boleh langsung pulang, sampai jumpa!\n\n" RESET);
            int idPasien;
            dequeue(antrianPasien, &idPasien);
            denah->data[row][col].serving = FALSE;
            return;
        }

        int idPenyakit = getIDPenyakit(dataPenyakit, pasien->riwayatPenyakit);
        int indexDiMap = getMapIndexByPenyakit(dataObatPenyakit, idPenyakit);

        // jika masih ada obat yang belum diminum tidak bisa pulangdok
        if (pasien->perut.length != dataObatPenyakit->buffer[indexDiMap].jumlahObat) {
            printf(YELLOW "Masih ada obat yang belum kamu habiskan, minum semuanya dulu yukk!\n\n" RESET);
            return;
        }

        boolean bolehPulang = TRUE;
        for (int i = 0; i < pasien->perut.length; i++) {
            if (pasien->perut.data[i] != dataObatPenyakit->buffer[indexDiMap].urutanObat[i]) {
                bolehPulang = FALSE;
            }
        }

        if (bolehPulang) {
            
            // reset data pasien jika dibolehin pulang
            strcpy(pasien->riwayatPenyakit, "-");
            pasien->suhuTubuh = 0.0;
            pasien->tekananDarahSistolik = -1;
            pasien->tekananDarahDiastolik = -1;
            pasien->detakJantung = -1;
            pasien->saturasiOksigen = 0.0;
            pasien->kadarGulaDarah = -1;
            pasien->beratBadan = 0.0;
            pasien->tinggiBadan = -1;
            pasien->kadarKolesterol = -1;
            pasien->trombosit = -1;
            pasien->nyawa = 3;
            
            int idPasien;

            // keluarkan pasien dari antrian
            dequeue(antrianPasien, &idPasien);

            // kosongin perut pasien
            emptyStack(&pasien->perut);
            denah->data[row][col].serving = FALSE;

            printSembuh();
            User *dokter = findUser(dataBaseUser, denah->data[row][col].namaDokter);
            dokter->aura++;

            printf(GREEN BOLD "Selamat! Kamu sudah dinyatakan sembuh oleh dokter. Silahkan pulang dan semoga sehat selalu!\n\n" RESET);
        } else {

            // jika tidak sesuai urutan minum tidak bisa pulangdok
            printf(RED "Maaf, tapi kamu masih belum bisa pulang!\n\n" RESET);

            printf(CYAN "Urutan peminuman obat yang diharapkan:\n" RESET);
            printf(BLUE BOLD "  ");
            for (int i = 0; i < dataObatPenyakit->buffer[indexDiMap].jumlahObat; i++) {
                Obat *obat = getObatbyId(dataObat, dataObatPenyakit->buffer[indexDiMap].urutanObat[i]);
                printf("%s", obat->nama);
                if (i != dataObatPenyakit->buffer[indexDiMap].jumlahObat - 1) {
                    printf(" " YELLOW "->" BLUE BOLD " ");
                }
            }
            printf(RESET "\n");

            printf(CYAN "Urutan obat yang kamu minum:\n" RESET);
            printf(YELLOW "  " RESET);
            for (int i = 0; i < pasien->perut.length; i++) {
                Obat *obat = getObatbyId(dataObat, pasien->perut.data[i]);
                Obat *obatUrut = getObatbyId(dataObat, dataObatPenyakit->buffer[indexDiMap].urutanObat[i]);
                if (strcmp(obat->nama, obatUrut->nama) != 0) {
                    printf(RED "%s" RESET, obat->nama);
                } else {
                    printf(YELLOW "%s" RESET, obat->nama);
                }
                if (i != pasien->perut.length - 1) {
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