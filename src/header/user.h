/* File : user.h */
/* Deskripsi : Berisi ADT user */

#ifndef USER_H
#define USER_H

#include "matrix.h"
#include "set.h"
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
    int tekanan_darah_sistolik;
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
void login(UserList *list, User *current_user, boolean *isLogin); // general (DONE)
void lupa_password(UserList *list, boolean *isLogin); // general (DONE)
void logout(User *current_user, boolean *isLogin); // general
void EXIT(User *current_user, UserList *list, boolean *run_program); // general
void registerPasien(UserList *list, Set *set, boolean *isLogin); // pasien
void helpMenu(User current_user, boolean *isLogin); // general
void denahRumahSakit(Matrix M); // general
void cariUser(); // manager
void lihatUser(); // manager
void tambahDokter(UserList *list, User *current_user, Set *set, boolean *isLogin); // manager
void diagnosis(User *u, PenyakitList *penyakit); // dokter
void minumObat();
void minumPenawar();
void bolehPulangGaa();
void ngobatin();
void assignDokter(); // manager
void SAVE();


/* LOAD */
void LOAD(UserList *userList, PenyakitList *penyakitList, ObatList *obatList, Obat_PenyakitList *relasiList);
void loadDataUser(const char *filename, UserList *list);
void loadDataPenyakit(const char *filename, PenyakitList *list);
void loadDataObat(const char *filename, ObatList *obatList);
void loadDataObatPenyakit(const char *filename, Obat_PenyakitList *relasi);
void loadDataConfig();


void CreateListDin(UserList *l, int capacity); // DONE IMPLEMENT
void dealocateListDin(UserList *l); // DONE IMPLEMENT
void expandList(UserList *l, int num); // DONE IMPLEMENT
void copyList(UserList lIn, UserList *lOut); // DONE IMPLEMENT
void RemoveUser(UserList *l, User *user); //DONE IMPLEMENT

/* --- Fungsi/Prosedur Manajemen User --- */

void CreateUser(UserList *l, User *u, char name[], char pass[], Role role);  // DONE IMPLEMENT
/* membuat user dengan nama, pass, role diinisialisasi, sisanya diberi default value*/

User* findUser(UserList *l, char username[]); // DONE IMPLEMENT
/* cari data User dari usernamenya */

boolean isUsernameExist(UserList l, char username[]); // DONE IMPLEMENT
/* cari di list user ada ga usernamenya */

void AddUser(UserList *l, User u); // DONE IMPLEMENT
/* nambahin user baru ke list user */

char* roleToStr(Role role); // DONE IMPLEMENT
/* mengembalikan nama role */

void toLower(char *str); // DONE IMPLEMENT
/* membuat string menjadi lower case semua */

/* --- Setter User --- */
void SetUsername(User *u, char name[]); 
void SetPassword(User *u, char pass[]);
void SetNewPassword(UserList *l, char username[], char pass[]); // DONE IMPLEMENT

#endif
