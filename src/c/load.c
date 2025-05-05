#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "header/user.h"
#include "header/penyakit.h"
#include "header/boolean.h"

#define initialCap 10
#define maxChar 100

void loadDataUser(const char *filename, UserList *userList){
    FILE *fileUser = fopen("user.csv", "r");
    if(fileUser == NULL){
        perror("File kosong!\n");
        return;
    }
    
    userList->data = (User *)malloc(initialCap * sizeof(User));
    userList->Neff = 0;
    userList->capacity = initialCap;
    
    char line[maxChar * 10];

    // Lewati header
    fgets(line, sizeof(line), fileUser);
    
    // Pembacaan dan penyalinan data
    while(fgets(line, sizeof(line), fileUser)){
        User u;
        line[strcspn(line, "\n")] = 0;
        char token = strtok(line, ",");
        if(token != NULL) u.id = atoi(token);

        token = strtok(NULL, ",");
        if (token != NULL) strncpy(u.username, token, sizeof(u.username));  // Username

        token = strtok(NULL, ",");
        if (token != NULL) strncpy(u.password, token, sizeof(u.password));  // Password

        token = strtok(NULL, ",");
        if (token != NULL) u.role = atoi(token);  // Role (0, 1, 2)

        token = strtok(NULL, ",");
        if (token != NULL) strncpy(u.riwayat_penyakit, token, sizeof(u.riwayat_penyakit));  // Riwayat Penyakit

        token = strtok(NULL, ",");
        if (token != NULL) u.suhu_tubuh = atof(token);  // Suhu Tubuh

        token = strtok(NULL, ",");
        if (token != NULL) u.tekanan_darah_sistolik = atoi(token);  // Tekanan Darah Sistolik

        token = strtok(NULL, ",");
        if (token != NULL) u.tekanan_darah_diastolik = atoi(token);  // Tekanan Darah Diastolik

        token = strtok(NULL, ",");
        if (token != NULL) u.detak_jantung = atoi(token);  // Detak Jantung

        token = strtok(NULL, ",");
        if (token != NULL) u.saturasi_oksigen = atof(token);  // Saturasi Oksigen

        token = strtok(NULL, ",");
        if (token != NULL) u.kadar_gula_darah = atoi(token);  // Kadar Gula Darah

        token = strtok(NULL, ",");
        if (token != NULL) u.berat_badan = atof(token);  // Berat Badan

        token = strtok(NULL, ",");
        if (token != NULL) u.tinggi_badan = atoi(token);  // Tinggi Badan

        token = strtok(NULL, ",");
        if (token != NULL) u.kadar_kolesterol = atoi(token);  // Kadar Kolesterol

        token = strtok(NULL, ",");
        if (token != NULL) u.kadar_kolesterol_Ldl = atoi(token);  // Kadar Kolesterol

        token = strtok(NULL, ",");
        if (token != NULL) u.trombosit = atoi(token);  // Trombosit
    
        if (userList->Neff >= userList->capacity) {
            userList->capacity *= 2;
            userList->data = (User *)realloc(userList->data, userList->capacity * sizeof(User));
        }

        userList->data[userList->Neff++] = u;
    }
    fclose(fileUser);
}

void loadDataPenyakit(const char *filename, PenyakitList *listPenyakit){
    FILE *filePenyakit = fopen("penyakit.csv", "r");
    if(filePenyakit == NULL){
        printf("Tidak ada data penyakit!");
        return;
    }

    listPenyakit->capacity = 10;
    listPenyakit->Neff = 0;
    listPenyakit->data = malloc(listPenyakit->capacity * sizeof(Penyakit));

    char line[512];
    while (fgets(line, sizeof(line), filePenyakit)) {
        if (listPenyakit->Neff >= listPenyakit->capacity) {
            listPenyakit->capacity *= 2;
            listPenyakit->data = realloc(listPenyakit->data, listPenyakit->capacity * sizeof(Penyakit));
        }

        Penyakit *p = &listPenyakit->data[listPenyakit->Neff];
        sscanf(line, "%d,%99[^,],%f,%f,%d,%d,%d,%d,%d,%d,%f,%f,%d,%d,%f,%f,%d,%d,%d,%d,%d,%d",
                &p->id, p->nama,
                &p->suhu_tubuh_Min, &p->suhu_tubuh_Max,
                &p->tekanan_sistolik_Min, &p->tekanan_sistolik_Max,
                &p->tekanan_diastolik_Min, &p->tekanan_diastolik_Max,
                &p->detak_jantung_Min, &p->detak_jantung_Max,
                &p->saturasi_Min, &p->saturasi_Max,
                &p->kadar_gula_Min, &p->kadar_gula_Max,
                &p->berat_badan_Min, &p->berat_badan_Max,
                &p->tinggi_badan_Min, &p->tinggi_badan_Max,
                &p->kolesterol_Min, &p->kolesterol_Max,
                &p->trombosit_Min, &p->trombosit_Max
        );
        listPenyakit->Neff++;
    }

    fclose(filePenyakit);
}

void loadDataObat(const char *filename, Obat *dataObat);

void loadDataObatPenyakit(const char *filename, Obat_Penyakit *relasi, int *jumlahRelasi);


