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
            if (strcmp(current_user->username, denah->data[i][j].namaDokter) == 0) {
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
    // jika antrian kosong tidak dapat ngobatin
    if (antrian->head == NULL) {
        printf(CYAN "Antrian kosong, tidak ada pasien untuk diobati!\n\n" RESET);
        return;
    }

    int idPasien = antrian->head->info;
    User *pasien = findUserByID(dataBaseUser, idPasien);

    if (strcmp(pasien->riwayatPenyakit, "Sehat") == 0) {
        printf(GREEN BOLD"%s sudah sehat! Tidak ada obat yang dapat diberikan.\n\n" RESET, pasien->username);
        denah->data[row][col].serving = TRUE;
        return;
    }

    // kalau pasien udah punya obat pasti udah pernah diobati
    if (pasien->inventory.jumlahObat > 0) {
        printf(RED BOLD"%s sudah diobati!\n\n" RESET, pasien->username);
        denah->data[row][col].serving = TRUE;
        return;
    }

    printf(CYAN "Anda sedang mengobati %s...\n" RESET, pasien->username);

    if (strcmp(pasien->riwayatPenyakit, "-") == 0) {
        printf(RED BOLD "%s tidak memiliki penyakit!\n" RESET, pasien->username);
        printf(YELLOW "%s belum didiagnosis!\n\n" RESET, pasien->username);
        return;
    }

    int idPenyakit = getIDPenyakit(dataPenyakit, pasien->riwayatPenyakit);
    int indexDiMap = getMapIndexByPenyakit(dataObatPenyakit, idPenyakit);

    printf(YELLOW "%s memiliki penyakit %s\n\n" RESET, pasien->username, pasien->riwayatPenyakit);
    printf(CYAN "Obat yang harus diberikan:\n" RESET);

    for (int i = 0; i < dataObatPenyakit->buffer[indexDiMap].jumlahObat; i++) {
        Obat *obat = getObatbyId(dataObat, dataObatPenyakit->buffer[indexDiMap].urutanObat[i]);

        printf(YELLOW "%d. %s\n" RESET, i + 1, obat->nama);
        pasien->inventory.obat[i] = obat->id;
        pasien->inventory.jumlahObat++;
    }
    printf(GREEN BOLD"\nObat sudah diberikan berdasarkan dengan urutan minumnya!\n\n" RESET);
}