#include <stdio.h>
#include "../header/user.h"

void daftarCheckUp(User *currentUser, UserList *user1, boolean *isLogin, Matrix *Hospital) {
    if (!(*isLogin)) {
        printf(RED "Anda belum login!\n\n" RESET);
        return;
    }

    User *pasien = findUser(user1, currentUser->username);

    if (pasien->role == ROLE_PASIEN) {

        boolean foundInAntrian = FALSE;
        // cari tahu dulu apakah pasiennya udah di antrian atau belum
        for (int i = 0; i < Hospital->rows; i++) {
            for (int j = 0; j < Hospital->cols; j++) {
                Queue antrian = Hospital->data[i][j].antrian;
                Node *curr = antrian.head;

                while (curr != NULL) {
                    if (curr->info == pasien->id) {
                        foundInAntrian = TRUE;
                        break;
                    }
                    curr = curr->next;
                }
                if (foundInAntrian) break;
            }
            if (foundInAntrian) break;
        }

        if (foundInAntrian) {
            printf(YELLOW "Anda sudah terdaftar dalam antrian check-up!\n" RESET);
            printf(YELLOW "Silakan selesaikan check-up yang sudah terdaftar terlebih dahulu!\n\n" RESET);
            return;
        }

        float suhu;
        int tekanansis, tekanandis, jantung;
        float saturasi;
        int guladarah;
        float berat;
        int tinggi, kolesterol, trombosit;

        int Antrian;
        int dokterAvailable[100][4];
        int dokterYangAda = 0;

        // nyari ruangan yang memiliki dokter dan antriannya masih muat
        for (int i = 0; i < Hospital->rows; i++) {
            for (int j = 0; j < Hospital->cols; j++) {
                Queue *AntrianRuang = &Hospital->data[i][j].antrian;
                Ruangan *Ruang = &Hospital->data[i][j];
                Antrian = countQueue(*AntrianRuang);

                if (!isRuanganKosong(*Ruang) && Antrian < Hospital->kapasitasRuangan + Hospital->kapasitasLuar) {
                    User *dokternya = findUser(user1, Hospital->data[i][j].namaDokter);

                    if (dokternya == NULL) {
                        continue;
                    }

                    dokterAvailable[dokterYangAda][0] = dokternya->id;
                    dokterAvailable[dokterYangAda][1] = Antrian;
                    dokterAvailable[dokterYangAda][2] = i;
                    dokterAvailable[dokterYangAda][3] = j;
                    dokterYangAda++;
                }
            }
        }

        if (dokterYangAda == 0) {
            printf(YELLOW "Saat ini tidak ada dokter yang sedang bertugas, maaf yaa :(\n\n" RESET);
            return;
        }
        printf(CYAN BOLD "Silakan masukkan data check-up Anda:\n" RESET);

        // pemasukan data pasien
        do {
            printf(YELLOW "Suhu Tubuh (Celcius): " RESET);
            scanf("%f", &suhu);
            if (suhu <= 0) {
                printf(RED "Suhu tubuh harus berupa angka positif!\n" RESET);
            }
        } while (suhu <= 0);

        do {
            printf(YELLOW "Tekanan Darah (sistol/diastol, contoh 120 80): " RESET);
            scanf("%d %d", &tekanansis, &tekanandis);
            if (tekanandis < 0 || tekanansis < 0) {
                printf(RED "Tekanan darah harus berupa angka positif\n" RESET);
            }
        } while (tekanandis < 0 || tekanansis < 0);

        do {
            printf(YELLOW "Detak Jantung (bpm): " RESET);
            scanf("%d", &jantung);
            if (jantung < 0) {
                printf(RED "Detak Jantung harus berupa angka positif\n" RESET);
            }
        } while (jantung < 0);

        do {
            printf(YELLOW "Saturasi Oksigen (%%): " RESET);
            scanf("%f", &saturasi);
            if (saturasi < 0) {
                printf(RED "Saturasi Oksigen harus berupa angka positif\n" RESET);
            }
        } while (saturasi < 0);

        do {
            printf(YELLOW "Kadar Gula Darah (mg/dL): " RESET);
            scanf("%d", &guladarah);
            if (guladarah < 0) {
                printf(RED "Kadar Gula Darah harus berupa angka positif\n" RESET);
            }
        } while (guladarah < 0);

        do {
            printf(YELLOW "Berat Badan (kg): " RESET);
            scanf("%f", &berat);
            if (berat < 0) {
                printf(RED "Berat Badan harus berupa angka positif\n" RESET);
            }
        } while (berat < 0);

        do {
            printf(YELLOW "Tinggi Badan (cm): " RESET);
            scanf("%d", &tinggi);
            if (tinggi < 0) {
                printf(RED "Tinggi Badan harus berupa angka positif\n" RESET);
            }
        } while (tinggi < 0);

        do {
            printf(YELLOW "Kadar Kolesterol (mg/dL): " RESET);
            scanf("%d", &kolesterol);
            if (kolesterol < 0) {
                printf(RED "Kadar Kolesterol harus berupa angka positif\n" RESET);
            }
        } while (kolesterol < 0);

        do {
            printf(YELLOW "Trombosit (ribu/µL): " RESET);
            scanf("%d", &trombosit);
            if (trombosit < 0) {
                printf(RED "Trombosit harus berupa angka positif\n" RESET);
            }
        } while (trombosit < 0);

        printf("\n");

        pasien->suhuTubuh = suhu;
        pasien->tekananDarahSistolik = tekanansis;
        pasien->tekananDarahDiastolik = tekanandis;
        pasien->detakJantung = jantung;
        pasien->saturasiOksigen = saturasi;
        pasien->kadarGulaDarah = guladarah;
        pasien->beratBadan = berat;
        pasien->tinggiBadan = tinggi;
        pasien->kadarKolesterol = kolesterol;
        pasien->trombosit = trombosit;


        char ruangan[10];
        printf(CYAN "\nBerikut adalah daftar dokter yang tersedia:\n" RESET);
        for (int i = 0; i < dokterYangAda; i++) {
            User *Dokter= findUserByID(user1, dokterAvailable[i][0]);
            getRuanganDokter(Hospital, Dokter->username, ruangan);
            printf(YELLOW "%d. Dr. %s - Spesialis Umum - Ruangan %s (Antrian: %d orang) - Aura %d\n" RESET,
                   i + 1, Dokter->username, ruangan, dokterAvailable[i][1], Dokter->aura);
        }

        int pilihanDokter;
        do {
            printf(CYAN "\nPilih dokter: " RESET);
            scanf("%d", &pilihanDokter);

            if (pilihanDokter < 1 || pilihanDokter > dokterYangAda) {
                printf(RED "Masukan tidak valid!\n" RESET);
            }
        } while (pilihanDokter < 1 || pilihanDokter > dokterYangAda);

        Queue *AntrianDokterPilihan = &Hospital->data[dokterAvailable[pilihanDokter - 1][2]][dokterAvailable[pilihanDokter - 1][3]].antrian;
        User *DokterPilihan = findUserByID(user1, dokterAvailable[pilihanDokter - 1][0]);
        getRuanganDokter(Hospital, DokterPilihan->username, ruangan);

        enqueue(AntrianDokterPilihan, pasien->id);
        printf(GREEN BOLD"\nPendaftaran check-up berhasil!\n" RESET);
        printf(GREEN BOLD"Anda terdaftar pada antrian Dr. %s di ruangan %s.\n" RESET, DokterPilihan->username, ruangan);
        printf(GREEN BOLD"Posisi antrian Anda: %d\n\n" RESET, countQueue(*AntrianDokterPilihan));
    } else {
        printf(RED "Anda bukan pasien! Tidak bisa daftar checkup!\n\n" RESET);
    }
}
