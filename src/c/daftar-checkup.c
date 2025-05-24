#include <stdio.h>
#include "../header/user.h"

void daftarCheckUp(User *current_user, UserList *user1, boolean *isLogin, Matrix *Hospital){
    if (!(*isLogin)) {
        printf("Anda belum login!\n\n");
        return;
    }
    if(current_user->role == ROLE_PASIEN){
        float suhu;
        int tekanan_sis, tekanan_dis, jantung;
        float saturasi;
        int gula_darah;
        float berat;
        int tinggi, kolesterol, kolesterol_Ldl, trombosit;
        printf("Silakan masukkan data check-up Anda:\n");
        do{
            printf("Suhu Tubuh (Celcius): ");
            scanf("%f", &suhu);
            //printf("\n");
            if(suhu <= 0){
                printf("Suhu tubuh harus berupa angka positif!\n");
            }
        }while(suhu <= 0);
        do{
            printf("Tekanan Darah (sistol/diastol, contoh 120 80):");
            scanf("%d %d", &tekanan_sis, &tekanan_dis);
            //printf("\n");
            if(tekanan_dis < 0 || tekanan_sis < 0){
                printf("Tekanan darah harus berupa angka positif\n");
            }
        }while(tekanan_dis < 0 || tekanan_sis < 0);
        do{
            printf("Detak Jantung (bpm):");
            scanf("%d", &jantung);
            //printf("\n");
            if(jantung < 0){
                printf("Detak Jantung harus berupa angka positif\n");
            }
        }while(jantung < 0);
        do{
            printf("Saturasi Oksigen (%%):");
            scanf("%f", &saturasi);
            //printf("\n");
            if(saturasi < 0){
                printf("Saturasi Oksigen harus berupa angka positif\n");
            }
        }while(saturasi < 0);
        do{
            printf("Kadar Gula Darah (mg/dL):");
            scanf("%d", &gula_darah);
            //printf("\n");
            if(gula_darah < 0){
                printf("Kadar Gula Darah harus berupa angka positif\n");
            }
        }while(gula_darah < 0);
        do{
            printf("Berat Badan (kg):");
            scanf("%f", &berat);
            //printf("\n");
            if(berat < 0){
                printf("Berat Badan harus berupa angka positif\n");
            }
        }while(berat < 0);
        do{
            printf("Tinggi Badan (cm):");
            scanf("%d", &tinggi);
            //printf("\n");
            if(tinggi < 0){
                printf("Tinggi Badan harus berupa angka positif\n");
            }
        }while(tinggi < 0);
        do{
            printf("Kadar Kolestrol (mg/dL):");
            scanf("%d", &kolesterol);
            //printf("\n");
            if(kolesterol < 0){
                printf("Kadar Kolestrol harus berupa angka positif\n");
            }
        }while(kolesterol < 0);
        do{
            printf("Kadar Kolestrol LDL (mg/dL):");
            scanf("%d", &kolesterol_Ldl);
            //printf("\n");
            if(kolesterol_Ldl < 0){
                printf("Kadar Kolestrol LDL harus berupa angka positif\n");
            }
        }while(kolesterol_Ldl < 0);
        do{
            printf("Trombosit (ribu/µL):");
            scanf("%d", &trombosit);
            //printf("\n");
            if(trombosit < 0){
                printf("Trombosit harus berupa angka positif\n");
            }
        }while(trombosit < 0);
        printf("\n\n");
        current_user->suhu_tubuh = suhu;
        current_user->tekanan_darah_sistolik = tekanan_sis;
        current_user->tekanan_darah_diastolik = tekanan_dis;
        current_user->detak_jantung = jantung;
        current_user->saturasi_oksigen = saturasi;
        current_user->kadar_gula_darah = gula_darah;
        current_user->berat_badan = berat;
        current_user->tinggi_badan = tinggi;
        current_user->kadar_kolesterol = kolesterol;
        current_user->kadar_kolesterol_Ldl = kolesterol_Ldl;
        current_user->trombosit = trombosit;
        int Antrian;// row di dokter_available
        int dokter_available[100][4]; // list dokter dengan antrian tidak penuh
        int asalan = 0;
        for(int i = 0; i < Hospital->rows; i++){
            for(int j = 0; j < Hospital->cols; j++){
                Queue *A = &Hospital->data[i][j].antrian;
                Ruangan *R = &Hospital->data[i][j];
                Antrian = countQueue(*A);
                if(!isRuanganKosong(*R) && Antrian < Hospital->kapasitasRuangan + Hospital->kapasitasLuar){
                    User *dokternya = findUser(user1, Hospital->data[i][j].nama_dokter);
                    printf("Mencari dokter \"%s\" ...\n", Hospital->data[i][j].nama_dokter);
                    if (dokternya == NULL) {
                        printf("[ERROR] Dokter tidak ditemukan!\n");
                        continue;  // atau break; tergantung logika yang diinginkan
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
        printf("Berikut adalah daftar dokter yang tersedia:\n");
        for(int i = 0; i < asalan; i++){
            User *A = findUserByID(user1, dokter_available[i][0]);
            getRuanganDokter(Hospital, A->username, &ruangan);
            printf("%d Dr. %s - Spesialis Umum - Ruangan %c (Antrian: %d orang)\n", i+1, A->username, ruangan, dokter_available[i][1]);
        }
        int pilihanDokter;
        do {
            printf("\nPilih dokter (1-%d): ", asalan);
            scanf("%d", &pilihanDokter);
        } while (pilihanDokter < 1 || pilihanDokter > asalan);
        Queue *B = &Hospital->data[dokter_available[pilihanDokter-1][2]][dokter_available[pilihanDokter-1][3]].antrian;
        User *C = findUserByID(user1, dokter_available[pilihanDokter-1][0]);// cari identitas dokter;
        getRuanganDokter(Hospital, C->username, &ruangan);//Mencari ruangan
        enqueue(B, current_user->id);
        printf("Pendaftaran check-up berhasil!\n");
        printf("Anda terdaftar pada antrian Dr. %s di ruangan %c.\n", C->username, ruangan);
        printf("Posisi antrian Anda: %d\n", countQueue(*B));
    }
    else{
        printf("Anda bukan pasien! Tidak bisa daftar checkup!\n\n");
    }
}
