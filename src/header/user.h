/* File : user.h */
/* Deskripsi : Berisi ADT user */

#ifndef USER_H
#define USER_H

#include <unistd.h>
#include "coloring.h" // Iseng wkwkwk
#include "map.h"
#include "matrix.h"
#include "set.h"
#include "penyakit.h"
#include "queue.h"
#include "boolean.h"
#include "ascii.h"

/**
 * Enumerasi Role User
 */
typedef enum {
    ROLE_PASIEN,
    ROLE_DOKTER,
    ROLE_MANAGER
} Role;

/**
 * Struct User
 */
typedef struct
{   
    int id;
    int nyawa;
    int aura;
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
    int trombosit;
    Inventory inventory;
    Stack perut;
} User;

/**
 * Struct UserList
 */
typedef struct 
{
    User *data;
    int Neff;
    int capacity;
    int currMaxId;
} UserList;


/**
 * PROSEDUR SEMUA FITUR PROGRAM
 */
void login(UserList *list, User *current_user, boolean *isLogin); // general
void lupa_password(UserList *list, boolean *isLogin); // general
void logout(User *current_user, boolean *isLogin); // general
void registerPasien(UserList *list, Set *set, boolean *isLogin); // pasien
void helpMenu(User current_user, boolean *isLogin); // general
void denahRumahSakit(Matrix M, boolean *isLogin); // general
void lihatRuangan(Matrix denah, UserList dataBaseUser, User current_user, boolean *isLogin); // general
void lihatAntrian(UserList *dataBaseUser, User *current_user, Matrix *denah, boolean *isLogin); // manager
void lihatUser(UserList *dataBaseUser, User *current_user, boolean *isLogin); // manager
void lihatPasien(UserList *dataBaseUser, User *current_user, boolean *isLogin); //manager
void lihatDokter(UserList *dataBaseUser, User *current_user, boolean *isLogin); //manager
void assignDokter(Matrix *denah, UserList *list, User *current_user, boolean *isLogin); // manager
void tambahDokter(UserList *list, User *current_user, Set *set, boolean *isLogin); // manager
void cariUser(UserList *dataBaseUser, User *current_user, boolean *isLogin); // manager
void cariPasien(UserList *dataBaseUser, User *current_user, boolean *isLogin); // manager
void cariDokter(UserList *dataBaseUser, User *current_user, boolean *isLogin); // manager
void diagnosis(User *current_user, UserList *dataBaseUser, PenyakitList *penyakit, boolean *isLogin, Matrix *denah); // dokter
void ngobatin(User *current_user, UserList *dataBaseUser, PenyakitList *dataPenyakit, ObatList *dataObat, Obat_PenyakitList *dataObatPenyakit, Matrix *denah, boolean *isLogin); // dokter
void daftarCheckUp(User *current_user, UserList *user1, boolean *isLogin, Matrix *Hospital); // pasien
void antrianSaya(User *current_user, Matrix *denah, boolean *isLogin); // pasien
void minumObat(User *current_user, UserList *dataBaseUser, ObatList *dataObat, boolean *isLogin); // pasien
void minumPenawar(User *current_user, UserList *dataBaseUser, ObatList *dataObat, Matrix *denah, boolean *isLogin); // pasien
void bolehPulangGaa(User *current_user, UserList *dataBaseUser, PenyakitList *dataPenyakit, ObatList *dataObat, Obat_PenyakitList *dataObatPenyakit, Matrix *denah, boolean *isLogin); // pasien
void SAVE(UserList *user1, ObatList *Obat, PenyakitList *sakit, Obat_PenyakitList *obat_penyakit, Matrix *Hospital); 
void skipAntrian(UserList *dataBaseUser, User *current_user, Matrix *denah, boolean *isLogin); // pasien
void cancelAntrian(UserList *dataBaseUser, User *current_user, Matrix *denah, boolean *isLogin); // pasien

/* EXIT */
void EXIT(UserList *user1, ObatList *Obat, PenyakitList *sakit, Obat_PenyakitList *obat_penyakit, Matrix *Hospital, boolean *exit);

/* LOAD */
void LOAD(const char *folderName, UserList *userList, PenyakitList *penyakitList, ObatList *obatList, Obat_PenyakitList *relasiList, Set *nama_unik, Matrix *denah);
void loadDataUser(const char *filename, UserList *userList, Set *nama_unik);
void loadDataPenyakit(const char *filename, PenyakitList *penyakitList);
void loadDataObat(const char *filename, ObatList *obatList);
void loadDataObatPenyakit(const char *filename, Obat_PenyakitList *relasiList);
void loadConfig(const char *filename, Matrix *denah, UserList *userList);


/**
 * Prosedur Modifikasi List Dinamis untuk UserList
 */
void CreateListDin(UserList *l, int capacity); 
void dealocateListDin(UserList *l); 
void expandList(UserList *l, int num); 
void copyList(UserList lIn, UserList *lOut);
void sortListByUsername(UserList *l, boolean asc);
void sortListByID(UserList *l, boolean asc);
void sortListByAura(UserList *l, boolean asc);


/**
 * Prosedur untuk manajemen Inventory User
 */
void insertLast(Inventory *inventory, int id);
void deleteAt(Inventory *inventory, int *id, int idx);


/**
 * Fungsi/Prosedur Manajemen User
 */
void CreateUser(UserList *l, User *u, char name[], char pass[], Role role);  
void deleteUser(UserList *l, User *u);
User* findUser(UserList *l, char username[]);
User* findUserByID(UserList *l, int id);
boolean isUsernameExist(UserList l, char username[]);
void AddUser(UserList *l, User *u);
char* roleToStr(Role role); 
void toLower(char *str);

#endif

