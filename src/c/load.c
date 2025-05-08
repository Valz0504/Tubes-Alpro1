#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "header/user.h"
#include "header/penyakit.h"
#include "header/boolean.h"

#define initialCap 10
#define maxChar 100
#define MAX_RELASI 1000

void loadDataUser(const char *filename, UserList *userList) {
    FILE *fileUser = fopen(filename, "r");
    if (fileUser == NULL) {
        perror("Gagal membuka file User!\n");
        return;
    }

    userList->data = (User *)malloc(initialCap * sizeof(User));
    userList->Neff = 0;
    userList->capacity = initialCap;

    char line[1024];
    fgets(line, sizeof(line), fileUser); // Lewati header

    while (fgets(line, sizeof(line), fileUser)) {
        User u;
        char buffer[128];
        int idx = 0, field = 0, i = 0;

        memset(&u, 0, sizeof(User)); // Inisialisasi semua field jadi nol

        while (line[i] != '\0' && line[i] != '\n') {
            if (line[i] == ',') {
                buffer[idx] = '\0';

                switch (field) {
                    case 0: u.id = atoi(buffer); break;
                    case 1: strncpy(u.username, buffer, sizeof(u.username)); break;
                    case 2: strncpy(u.password, buffer, sizeof(u.password)); break;
                    case 3: u.role = atoi(buffer); break;
                    case 4: strncpy(u.riwayat_penyakit, buffer, sizeof(u.riwayat_penyakit)); break;
                    case 5: u.suhu_tubuh = atof(buffer); break;
                    case 6: u.tekanan_darah_sistolik = atoi(buffer); break;
                    case 7: u.tekanan_darah_diastolik = atoi(buffer); break;
                    case 8: u.detak_jantung = atoi(buffer); break;
                    case 9: u.saturasi_oksigen = atof(buffer); break;
                    case 10: u.kadar_gula_darah = atoi(buffer); break;
                    case 11: u.berat_badan = atof(buffer); break;
                    case 12: u.tinggi_badan = atoi(buffer); break;
                    case 13: u.kadar_kolesterol = atoi(buffer); break;
                    case 14: u.kadar_kolesterol_Ldl = atoi(buffer); break;
                    case 15: u.trombosit = atoi(buffer); break;
                }

                field++;
                idx = 0;
            } else {
                buffer[idx++] = line[i];
            }
            i++;
        }

        // Ambil field terakhir (setelah koma terakhir)
        buffer[idx] = '\0';
        if (field == 15) u.trombosit = atoi(buffer);

        if (userList->Neff >= userList->capacity) {
            userList->capacity *= 2;
            userList->data = (User *)realloc(userList->data, userList->capacity * sizeof(User));
        }

        userList->data[userList->Neff++] = u;
    }

    fclose(fileUser);
}

void loadDataPenyakit(const char *filename, PenyakitList *listPenyakit) {
    FILE *filePenyakit = fopen(filename, "r");
    if (filePenyakit == NULL) {
        printf("Gagal membuka file penyakit!");
        return;
    }

    listPenyakit->capacity = 10;
    listPenyakit->Neff = 0;
    listPenyakit->data = malloc(listPenyakit->capacity * sizeof(Penyakit));

    char line[1024];
    while (fgets(line, sizeof(line), filePenyakit)) {
        if (listPenyakit->Neff >= listPenyakit->capacity) {
            listPenyakit->capacity *= 2;
            listPenyakit->data = realloc(listPenyakit->data, listPenyakit->capacity * sizeof(Penyakit));
        }

        Penyakit *p = &listPenyakit->data[listPenyakit->Neff];
        char buffer[128];
        int idx = 0, field = 0, i = 0;

        memset(p, 0, sizeof(Penyakit));

        while (line[i] != '\0' && line[i] != '\n') {
            if (line[i] == ',') {
                buffer[idx] = '\0';

                switch (field) {
                    case 0: p->id = atoi(buffer); break;
                    case 1: strncpy(p->nama, buffer, sizeof(p->nama)); break;
                    case 2: p->suhu_tubuh_Min = atof(buffer); break;
                    case 3: p->suhu_tubuh_Max = atof(buffer); break;
                    case 4: p->tekanan_sistolik_Min = atoi(buffer); break;
                    case 5: p->tekanan_sistolik_Max = atoi(buffer); break;
                    case 6: p->tekanan_diastolik_Min = atoi(buffer); break;
                    case 7: p->tekanan_diastolik_Max = atoi(buffer); break;
                    case 8: p->detak_jantung_Min = atoi(buffer); break;
                    case 9: p->detak_jantung_Max = atoi(buffer); break;
                    case 10: p->saturasi_Min = atof(buffer); break;
                    case 11: p->saturasi_Max = atof(buffer); break;
                    case 12: p->kadar_gula_Min = atoi(buffer); break;
                    case 13: p->kadar_gula_Max = atoi(buffer); break;
                    case 14: p->berat_badan_Min = atof(buffer); break;
                    case 15: p->berat_badan_Max = atof(buffer); break;
                    case 16: p->tinggi_badan_Min = atoi(buffer); break;
                    case 17: p->tinggi_badan_Max = atoi(buffer); break;
                    case 18: p->kolesterol_Min = atoi(buffer); break;
                    case 19: p->kolesterol_Max = atoi(buffer); break;
                    case 20: p->trombosit_Min = atoi(buffer); break;
                }

                field++;
                idx = 0;
            } else {
                buffer[idx++] = line[i];
            }
            i++;
        }

        // Field terakhir (trombosit_Max)
        buffer[idx] = '\0';
        if (field == 21) p->trombosit_Max = atoi(buffer);

        listPenyakit->Neff++;
    }

    fclose(filePenyakit);
}


void loadDataObat(const char *filename, ObatList *listObat){
    FILE *fileObat = fopen(filename, "r");
    if (fileObat == NULL) {
        perror("Gagal membuka file obat");
        return;
    }

    listObat->capacity = initialCap;
    listObat->Neff = 0;
    listObat->data = malloc(listObat->capacity * sizeof(Obat));

    char line[256];

    fgets(line, sizeof(line), fileObat);  // Lewati header jika ada

    while (fgets(line, sizeof(line), fileObat)) {
        if (listObat->Neff >= listObat->capacity) {
            listObat->capacity *= 2;
            listObat->data = realloc(listObat->data, listObat->capacity * sizeof(Obat));
        }

        Obat o;
        char buffer[128];
        int i = 0, j = 0, field = 0;

        while (line[i] != '\0' && line[i] != '\n') {
            if (line[i] == ',') {
                buffer[j] = '\0';
                o.id = atoi(buffer);  // field pertama: id
                field++;
                j = 0;
            } else {
                buffer[j++] = line[i];
            }
            i++;
        }

        buffer[j] = '\0';
        if (field == 1) {
            strncpy(o.nama, buffer, sizeof(o.nama));
        }

        listObat->data[listObat->Neff++] = o;
    }

    fclose(fileObat);
}

void loadDataObatPenyakit(const char *filename, Obat_PenyakitList *relasiList) {
    FILE *fileOP = fopen(filename, "r");
    if (fileOP == NULL) {
        perror("Gagal membuka file obat-penyakit");
        return;
    }

    relasiList->data = malloc(initialCap * sizeof(Obat_Penyakit));
    relasiList->Neff = 0;
    relasiList->capacity = initialCap;

    char line[256];
    fgets(line, sizeof(line), fileOP);  // Lewati header

    while (fgets(line, sizeof(line), fileOP)) {
        Obat_Penyakit r;
        char buffer[64];
        int i = 0, j = 0, field = 0;

        while (line[i] != '\0' && line[i] != '\n') {
            if (line[i] == ',') {
                buffer[j] = '\0';
                if (field == 0) r.id_obat = atoi(buffer);
                else if (field == 1) r.id_penyakit = atoi(buffer);
                field++;
                j = 0;
            } else {
                buffer[j++] = line[i];
            }
            i++;
        }

        buffer[j] = '\0';
        if (field == 2) r.urutan_minum = atoi(buffer);

        // Tambah ke list
        if (relasiList->Neff >= relasiList->capacity) {
            relasiList->capacity *= 2;
            relasiList->data = realloc(relasiList->data, relasiList->capacity * sizeof(Obat_Penyakit));
        }

        relasiList->data[relasiList->Neff++] = r;
    }

    fclose(fileOP);
}


