/* File : user.h */
/* Deskripsi : Berisi ADT user */

#ifndef USER_H
#define USER_H

#include "penyakit.h"
#include "boolean.h"

typedef enum {
    ROLE_PASIEN,
    ROLE_DOKTER,
    ROLE_MANAGER
} Role;

/* --- Struct User --- */
typedef struct
{   
    int id;
    char username[100];
    char password[100];
    Role role;
    char riwayat_penyakit[100];
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
    User *data;
    int Neff;
    int capacity;
} UserList;

/* --- PROSEDUR FITUR PROGRAM --- */
void login(); // general
void lupa_password(); // general
void logout(); // general
void exit(); // general
void registerPasien(); // pasien
void helpMenu(); // general
void cariUser(); // manager
void lihatUser(); // manager
void tambahDokter(); // manager
void assignDokter(); // manager
void LOAD();
void SAVE();


/* --- Fungsi/Prosedur Manajemen User --- */
void CreateUser(User *u, char name[], char pass[], char role[]);
User findUser(UserList l, char username[]); /* cari data User dari usernamenya */
boolean isUsernameExist(UserList l, char username[]); /* cari di list user ada ga usernamenya */
void AddUser(UserList *l, User u); /* nambahin user baru ke list user */

void CreateListDin(UserList *l, int capacity);
void dealocateListDin(UserList *l);

/* --- Setter User --- */
void SetUsername(User *u, char name[]); 
void SetPassword(User *u, char pass[]);
void SetNewPassword(UserList *l, char username[], char pass[]);



#endif
