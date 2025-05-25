#include <stdio.h>
#include "../header/user.h"

void daftarCheckUp(User *current_user, UserList *user1, boolean *isLogin, Matrix *Hospital) {
    if (!(*isLogin)) {
        printf(RED "Anda belum login!\n\n" RESET);
        return;
    }
    if (current_user->role == ROLE_PASIEN) {
        float suhu;
        int tekanan_sis, tekanan_dis, jantung;
        float saturasi;
        int gula_darah;
        float berat;
        int tinggi, kolesterol, trombosit;

        printf(CYAN BOLD "Silakan masukkan data check-up Anda:\n" RESET);

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

        current_user->suhu_tubuh = suhu;
        current_user->tekanan_darah_sistolik = tekanan_sis;
        current_user->tekanan_darah_diastolik = tekanan_dis;
        current_user->detak_jantung = jantung;
        current_user->saturasi_oksigen = saturasi;
        current_user->kadar_gula_darah = gula_darah;
        current_user->berat_badan = berat;
        current_user->tinggi_badan = tinggi;
        current_user->kadar_kolesterol = kolesterol;
        current_user->trombosit = trombosit;

        int Antrian;
        int dokter_available[100][4];
        int asalan = 0;

        for (int i = 0; i < Hospital->rows; i++) {
            for (int j = 0; j < Hospital->cols; j++) {
                Queue *A = &Hospital->data[i][j].antrian;
                Ruangan *R = &Hospital->data[i][j];
                Antrian = countQueue(*A);

                if (!isRuanganKosong(*R) && Antrian < Hospital->kapasitasRuangan + Hospital->kapasitasLuar) {
                    User *dokternya = findUser(user1, Hospital->data[i][j].nama_dokter);
                    printf(GRAY "Mencari dokter \"%s\" ...\n" RESET, Hospital->data[i][j].nama_dokter);

                    if (dokternya == NULL) {
                        printf(RED "[ERROR] Dokter tidak ditemukan!\n" RESET);
                        continue;
                    }

                    dokter_available[asalan][0] = dokternya->id;
                    dokter_available[asalan][1] = Antrian;
                    dokter_available[asalan][2] = i;
                    dokter_available[asalan][3] = j;
                    asalan++;
                }
            }
        }

        char ruangan;
        printf(CYAN "\nBerikut adalah daftar dokter yang tersedia:\n" RESET);
        for (int i = 0; i < asalan; i++) {
            User *A = findUserByID(user1, dokter_available[i][0]);
            getRuanganDokter(Hospital, A->username, &ruangan);
            printf(YELLOW "%d. Dr. %s - Spesialis Umum - Ruangan %c (Antrian: %d orang)\n" RESET,
                   i + 1, A->username, ruangan, dokter_available[i][1]);
        }

        int pilihanDokter;
        do {
            printf(CYAN "\nPilih dokter: " RESET);
            scanf("%d", &pilihanDokter);

            if (pilihanDokter < 1 || pilihanDokter > asalan) {
                printf(RED "Masukan tidak valid!\n" RESET);
            }
        } while (pilihanDokter < 1 || pilihanDokter > asalan);

        Queue *B = &Hospital->data[dokter_available[pilihanDokter - 1][2]][dokter_available[pilihanDokter - 1][3]].antrian;
        User *C = findUserByID(user1, dokter_available[pilihanDokter - 1][0]);
        getRuanganDokter(Hospital, C->username, &ruangan);

        enqueue(B, current_user->id);
        printf(GREEN "\nPendaftaran check-up berhasil!\n" RESET);
        printf(GREEN "Anda terdaftar pada antrian Dr. %s di ruangan %c.\n" RESET, C->username, ruangan);
        printf(GREEN "Posisi antrian Anda: %d\n\n" RESET, countQueue(*B));
    } else {
        printf(RED "Anda bukan pasien! Tidak bisa daftar checkup!\n\n" RESET);
    }
}
