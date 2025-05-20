/* File : user.h */
/* Deskripsi : Berisi ADT user */

#ifndef USER_H
#define USER_H

#include "matrix.h"
#include "set.h"
#include "penyakit.h"
#include "queue.h"
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
    Inventory inventory;
    Stack perut;
} User;


/* --- Struct ListUser --- */
typedef struct 
{
    User *data;
    int Neff;
    int capacity;
} UserList;

/* --- PROSEDUR FITUR PROGRAM --- */
void login(UserList *list, User *current_user, boolean *isLogin); // general
void lupa_password(UserList *list, boolean *isLogin); // general
void logout(User *current_user, boolean *isLogin); // general
void registerPasien(UserList *list, Set *set, boolean *isLogin); // pasien
void helpMenu(User current_user, boolean *isLogin); // general
void denahRumahSakit(Matrix M); // general
void lihatRuangan(); // general
void lihatAntrian(); // manager
void cariUser(); // manager
void lihatUser(); // manager
void assignDokter(Matrix *denah, UserList *list, User *current_user, boolean *isLogin); // manager
void tambahDokter(UserList *list, User *current_user, Set *set, boolean *isLogin); // manager
// void lihatUser(); // manager
// void cariUser(); // manager
void diagnosis(User *current_user, PenyakitList *penyakit, boolean *isLogin); // dokter
void ngobatin(User *current_user, PenyakitList *penyakitList, Obat_PenyakitList *obatPenyakitList, boolean *isLogin); // dokter
void daftarCheckUp(); // pasien
void antrianSaya(); // pasien
void minumObat(User *current_user, ObatList *dataObat, boolean *isLogin); // pasien
void minumPenawar(); // pasien
void bolehPulangGaa(); // pasien
void SAVE(); // general
void EXIT(User *current_user, UserList *list, boolean *run_program); // general
void LOAD(const char *folderName, UserList *userList, PenyakitList *penyakitList, ObatList *obatList, Obat_PenyakitList *relasiList, Set *nama_unik, Matrix *denah);


/* LOAD */
void loadDataUser(const char *filename, UserList *userList, Set *nama_unik);
void loadDataPenyakit(const char *filename, PenyakitList *penyakitList);
void loadDataObat(const char *filename, ObatList *obatList);
void loadDataObatPenyakit(const char *filename, Obat_PenyakitList *relasiList);
void loadConfig(const char *filename, Matrix *denah, UserList *userList);
// void loadDataUser(const char *filename, UserList *list, Set *nama_unik);
// void loadDataPenyakit(const char *filename, PenyakitList *list);
// void loadDataObat(const char *filename, ObatList *obatList);
// void loadDataObatPenyakit(const char *filename, Obat_PenyakitList *relasi);
// void loadDataObatPenyakit(const char *filename, Obat_PenyakitList *relasiList);


/* List Dinamis untuk UserList */
void CreateListDin(UserList *l, int capacity); 
void dealocateListDin(UserList *l); 
void expandList(UserList *l, int num); 
void copyList(UserList lIn, UserList *lOut);


/* Prosedur untuk manajemen Inventory User */
void insertLast(Inventory *inventory, int id);
void deleteAt(Inventory *inventory, int *id, int idx);


/* --- Fungsi/Prosedur Manajemen User --- */
void CreateUser(UserList *l, User *u, char name[], char pass[], Role role);  
User* findUser(UserList *l, char username[]);
boolean isUsernameExist(UserList l, char username[]);
void AddUser(UserList *l, User u);
char* roleToStr(Role role); 
void toLower(char *str);

#endif
