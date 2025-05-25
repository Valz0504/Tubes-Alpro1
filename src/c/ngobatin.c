#include <stdio.h>
#include <string.h>
#include "../header/user.h"

void ngobatin(User *current_user, UserList *dataBaseUser, PenyakitList *dataPenyakit, ObatList *dataObat, Obat_PenyakitList *dataObatPenyakit, Matrix *denah, boolean *isLogin) {
    if (!(*isLogin)) {
        printf(RED "Login sebagai Dokter terlebih dahulu!\n\n" RESET);
        return;
    }

    if (current_user->role != ROLE_DOKTER) {
        printf(RED "Anda bukan dokter! Tidak bisa mengobati pasien!\n\n" RESET);
        return;
    }

    int row, col;
    boolean foundRuangan = FALSE;
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
        printf(CYAN "Antrian kosong, tidak ada pasien untuk diobati!\n\n" RESET);
        return;
    }

    int idPasien = antrian->head->info;
    User *pasien = findUserByID(dataBaseUser, idPasien);

    if (pasien->inventory.jumlahObat > 0) {
        printf(GREEN "%s sudah diobati!\n\n" RESET, pasien->username);
        denah->data[row][col].serving = TRUE;
        return;
    }

    printf(CYAN "Dokter sedang mengobati pasien...\n" RESET);

    if (strcmp(pasien->riwayat_penyakit, "-") == 0) {
        printf(RED "Pasien tidak memiliki penyakit!\n" RESET);
        printf(YELLOW "Pasien belum didiagnosis!\n\n" RESET);
        return;
    }

    int idPenyakit = getIDPenyakit(dataPenyakit, pasien->riwayat_penyakit);
    int indexDiMap = getMapIndexByPenyakit(dataObatPenyakit, idPenyakit);

    printf(GREEN "Pasien memiliki penyakit %s\n" RESET, pasien->riwayat_penyakit);
    printf(CYAN "Obat yang harus diberikan:\n" RESET);

    for (int i = 0; i < dataObatPenyakit->buffer[indexDiMap].jumlah_obat; i++) {
        Obat *obat = getObatbyId(dataObat, dataObatPenyakit->buffer[indexDiMap].urutan_obat[i]);

        printf(GREEN "%d. %s\n" RESET, i + 1, obat->nama);
        pasien->inventory.obat[i] = obat->id;
        pasien->inventory.jumlahObat++;
    }
}