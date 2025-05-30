#include <stdio.h>
#include <string.h>
#include "../header/user.h"

void diagnosis(User *currentUser, UserList *listUser, PenyakitList *listPenyakit, boolean *isLogin, Matrix *denah) {
    if (!(*isLogin)) {
        printf(RED "Login sebagai Dokter terlebih dahulu!\n\n" RESET);
        return;
    }

    int row, col;
    boolean foundRuangan = FALSE;

    if (currentUser->role == ROLE_DOKTER) {
        // Cari ruangan dokter berdasarkan username
        for (int i = 0; i < denah->rows; i++) {
            for (int j = 0; j < denah->cols; j++) {
                if (strcmp(currentUser->username, denah->data[i][j].namaDokter) == 0) {
                    row = i;
                    col = j;
                    foundRuangan = TRUE;
                }
            }
        }

        // jika dokter tidak ditemukan di denah tidak bisa diagnosis
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

        // jika pasien sudah punya obat atau sudah didiagnosis tidak bisa didiagnosis lagi
        if (pasien->inventory.jumlahObat > 0 || strcmp(pasien->riwayatPenyakit, "-") != 0) {
            denah->data[row][col].serving = TRUE;
        }
        if (denah->data[row][col].serving) {
            printf(RED BOLD "Anda sudah mendiagnosis %s.\n\n" RESET, pasien->username);
            return;
        }

        printf(CYAN "%s sedang dicek...\n\n" RESET, pasien->username);
        boolean foundPenyakit = FALSE;

        for (int i = 0; i < listPenyakit->Neff; i++) {
            Penyakit p = listPenyakit->data[i];

            if (
                pasien->suhuTubuh >= p.suhuTubuhMin && pasien->suhuTubuh <= p.suhuTubuhMax &&
                pasien->tekananDarahSistolik >= p.tekananSistolikMin && pasien->tekananDarahSistolik <= p.tekananSistolikMax &&
                pasien->tekananDarahDiastolik >= p.tekananDiastolikMin && pasien->tekananDarahDiastolik <= p.tekananDiastolikMax &&
                pasien->detakJantung >= p.detakJantungMin && pasien->detakJantung <= p.detakJantungMax &&
                pasien->saturasiOksigen >= p.saturasiMin && pasien->saturasiOksigen <= p.saturasiMax &&
                pasien->kadarGulaDarah >= p.kadarGulaMin && pasien->kadarGulaDarah <= p.kadarGulaMax &&
                pasien->beratBadan >= p.beratBadanMin && pasien->beratBadan <= p.beratBadanMax &&
                pasien->tinggiBadan >= p.tinggiBadanMin && pasien->tinggiBadan <= p.tinggiBadanMax &&
                pasien->kadarKolesterol >= p.kolesterolMin && pasien->kadarKolesterol <= p.kolesterolMax &&
                pasien->trombosit >= p.trombositMin && pasien->trombosit <= p.trombositMax
            ) {
                printf(GREEN BOLD"%s terdiagnosa penyakit %s!\n\n" RESET, pasien->username, p.nama);
                strncpy(pasien->riwayatPenyakit, p.nama, sizeof(pasien->riwayatPenyakit));
                foundPenyakit = TRUE;
                break;
            }
        }

        if (!foundPenyakit) {
            printf(YELLOW "%s tidak terdiagnosa penyakit apapun\n\n" RESET, pasien->username);
            strcpy(pasien->riwayatPenyakit, "Sehat");
            pasien->riwayatPenyakit[sizeof(pasien->riwayatPenyakit) - 1] = '\0';
        }
    } else {
        printf(RED "Anda bukan dokter! Tidak bisa diagnosis pasien!\n\n" RESET);
    }
}
