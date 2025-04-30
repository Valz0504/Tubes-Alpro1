/* File : ADT.h */
/* Deskripsi : Berisi berbagai macam ADT yang digunakan dalam program */

#ifndef USER_H
#define USER_H


/* --- ADT User : Menyimpan atribut dari User --- */
typedef struct
{   
    int id;
    char *username[100];
    char *password[100];
    char *role[7];
    char *riwayat_penyakit[1000];
    float suhu_tubuh;
    int tekanan_darah_tistolik;
    int tekanan_darah_diastolik;
    int detak_jantung;
    float saturasi_oksigen;
    int kadar_gula_darah;
    float berat_badan;
    int tinggi_badan;
    int kadar_kolesterol;
    int kadar_kolesterol_Ldl;
    int trombosit;
} User;


/* --- ADT Penyakit : Menyimpan atribut Penyakit --- */

typedef struct
{
    int id;
    char* nama_penyakit[100];
    float suhu_tubuh_Min;
    float suhu_tubuh_Max;
    int tekanan_sistolik_Min;
    int tekanan_sistolik_Max;
    int tekanan_diastolik_Min;
    int tekanan_diastolik_Max;
    int detak_jantung_Min;
    int detak_jantung_Max;
    float saturasi_oksigen_Min;
    float saturasi_oksigen_Max;
    int kadar_gula_darah_Min;
    int kadar_gula_darah_Max;
    float berat_badan_Min;
    float berat_badan_Max;
    int tinggi_badan_Min;
    int tinggi_badan_Max;
    int kolesterol_Min;
    int kolesterol_Max;
    int trombosit_Min;
    int trombosit_Max;
} Penyakit;


/* --- ADT Obat : Menyimpan atribut Obat --- */
typedef struct
{
    int obat_ID;
    char* nama_obat[100];
} Obat;


#endif