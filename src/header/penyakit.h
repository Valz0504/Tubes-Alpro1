
#ifndef PENYAKIT_H
#define PENYAKIT_H

#include "boolean.h"

typedef struct {
    int id;
    char nama[100];
    float suhu_tubuh_Min;
    float suhu_tubuh_Max;
    int tekanan_sistolik_Min;
    int tekanan_sistolik_Max;
    int tekanan_diastolik_Min;
    int tekanan_diastolik_Max;
    int detak_jantung_Min;
    int detak_jantung_Max;
    float saturasi_Min;
    float saturasi_Max;
    int kadar_gula_Min;
    int kadar_gula_Max;
    float berat_badan_Min;
    float berat_badan_Max;
    int tinggi_badan_Min;
    int tinggi_badan_Max;
    int kolesterol_Min;
    int kolesterol_Max;
    int trombosit_Min;
    int trombosit_Max;
} Penyakit;

typedef struct 
{
    Penyakit *data;
    int Neff;
    int capacity;
} PenyakitList;

typedef struct {
    int id;
    char nama[100];
} Obat;

typedef struct {
    int id_obat;
    int id_penyakit;
    int urutan_minum;
} Obat_Penyakit;

void diagnosis(User *u, PenyakitList *penyakit);
void minumObat();
void minumPenawar();
void bolehPulangGaa();
void ngobatin();

#endif