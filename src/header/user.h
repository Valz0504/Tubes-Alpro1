/* File : user.h */
/* Deskripsi : Berisi ADT user */

#ifndef USER_H
#define USER_H


/* --- Struct User --- */
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


/* --- Struct ListUser --- */
typedef struct 
{
    User data[100];
    int Neff;
} UserList;

#endif