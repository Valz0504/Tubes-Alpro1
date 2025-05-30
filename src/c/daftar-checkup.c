#include <stdio.h>
#include "../header/user.h"

void daftarCheckUp(User *current_user, UserList *user1, boolean *isLogin, Matrix *Hospital) {
    if (!(*isLogin)) {
        printf(RED "Anda belum login!\n\n" RESET);
        return;
    }

    User *pasien = findUser(user1, current_user->username);

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
        int tekanan_sis, tekanan_dis, jantung;
        float saturasi;
        int gula_darah;
        float berat;
        int tinggi, kolesterol, trombosit;

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
            scanf("%d %d", &tekanan_sis, &tekanan_dis);
            if (tekanan_dis < 0 || tekanan_sis < 0) {
                printf(RED "Tekanan darah harus berupa angka positif\n" RESET);
            }
        } while (tekanan_dis < 0 || tekanan_sis < 0);

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
            scanf("%d", &gula_darah);
            if (gula_darah < 0) {
                printf(RED "Kadar Gula Darah harus berupa angka positif\n" RESET);
            }
        } while (gula_darah < 0);

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

        pasien->suhu_tubuh = suhu;
        pasien->tekanan_darah_sistolik = tekanan_sis;
        pasien->tekanan_darah_diastolik = tekanan_dis;
        pasien->detak_jantung = jantung;
        pasien->saturasi_oksigen = saturasi;
        pasien->kadar_gula_darah = gula_darah;
        pasien->berat_badan = berat;
        pasien->tinggi_badan = tinggi;
        pasien->kadar_kolesterol = kolesterol;
        pasien->trombosit = trombosit;

        int Antrian;
        int dokter_available[100][4];
        int dokterYangAda = 0;

        // nyari ruangan yang memiliki dokter dan antriannya masih muat
        for (int i = 0; i < Hospital->rows; i++) {
            for (int j = 0; j < Hospital->cols; j++) {
                Queue *AntrianRuang = &Hospital->data[i][j].antrian;
                Ruangan *Ruang = &Hospital->data[i][j];
                Antrian = countQueue(*AntrianRuang);

                if (!isRuanganKosong(*Ruang) && Antrian < Hospital->kapasitasRuangan + Hospital->kapasitasLuar) {
                    User *dokternya = findUser(user1, Hospital->data[i][j].nama_dokter);

                    if (dokternya == NULL) {
                        continue;
                    }

                    dokter_available[dokterYangAda][0] = dokternya->id;
                    dokter_available[dokterYangAda][1] = Antrian;
                    dokter_available[dokterYangAda][2] = i;
                    dokter_available[dokterYangAda][3] = j;
                    dokterYangAda++;
                }
            }
        }

        char ruangan[10];
        printf(CYAN "\nBerikut adalah daftar dokter yang tersedia:\n" RESET);
        for (int i = 0; i < dokterYangAda; i++) {
            User *Dokter= findUserByID(user1, dokter_available[i][0]);
            getRuanganDokter(Hospital, Dokter->username, ruangan);
            printf(YELLOW "%d. Dr. %s - Spesialis Umum - Ruangan %s (Antrian: %d orang) - Aura %d\n" RESET,
                   i + 1, Dokter->username, ruangan, dokter_available[i][1], Dokter->aura);
        }

        int pilihanDokter;
        do {
            printf(CYAN "\nPilih dokter: " RESET);
            scanf("%d", &pilihanDokter);

            if (pilihanDokter < 1 || pilihanDokter > dokterYangAda) {
                printf(RED "Masukan tidak valid!\n" RESET);
            }
        } while (pilihanDokter < 1 || pilihanDokter > dokterYangAda);

        Queue *AntrianDokterPilihan = &Hospital->data[dokter_available[pilihanDokter - 1][2]][dokter_available[pilihanDokter - 1][3]].antrian;
        User *DokterPilihan = findUserByID(user1, dokter_available[pilihanDokter - 1][0]);
        getRuanganDokter(Hospital, DokterPilihan->username, ruangan);

        enqueue(AntrianDokterPilihan, pasien->id);
        printf(GREEN BOLD"\nPendaftaran check-up berhasil!\n" RESET);
        printf(GREEN BOLD"Anda terdaftar pada antrian Dr. %s di ruangan %s.\n" RESET, DokterPilihan->username, ruangan);
        printf(GREEN BOLD"Posisi antrian Anda: %d\n\n" RESET, countQueue(*AntrianDokterPilihan));
    } else {
        printf(RED "Anda bukan pasien! Tidak bisa daftar checkup!\n\n" RESET);
    }
}
