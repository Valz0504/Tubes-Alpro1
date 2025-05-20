#include <stdio.h>
#include <stdlib.h>
#include "./header/user.h"

int main(int argc, char* argv[]) {
    system("clear");

    if (argv[1] == NULL) {
        printf("Tidak ada nama folder yang diberikan!\n");
        printf("Usage: ./main <<nama_folder>>\n");
        return 0;
    }
    // masih harus ada pengecekan kalo foldernya gaada


    // Inisialisasi semua Database yang diperlukan
    UserList dataBaseUser;
    PenyakitList dataPenyakit;
    ObatList dataObat;
    Obat_PenyakitList dataObatPenyakit;
    Matrix denah_rs;
    Set nama_unik;
    
    CreateListDin(&dataBaseUser, 5);
    CreateMatrix(10, 10, &denah_rs);
    initSet(&nama_unik, 5);

    // LOAD DATA from file folder
    LOAD(&dataBaseUser, &dataPenyakit, &dataObat, &dataObatPenyakit, &nama_unik);

    // Inisialisasi state LOGIN
    User current_user;
    boolean isLogin = FALSE;
    
    // Opening Program
    printf("=== SELAMAT DATANG ===\n");
    printf("Ketik command HELP untuk melihat apa saja yang dapat kamu lakukan sekarang!\n\n");

    // Program Utama
    boolean run_program = TRUE;
    while (run_program) {
        char prompt[100];
        printf(">>> Command: ");
        scanf("%s", prompt);
    
        if (strcmp(prompt, "LOGIN") == 0) {
            login(&dataBaseUser, &current_user, &isLogin);
        } else if (strcmp(prompt, "REGISTER") == 0) {
            registerPasien(&dataBaseUser, &nama_unik, &isLogin);
        } else if (strcmp(prompt, "LUPA_PASSWORD") == 0) {
            lupa_password(&dataBaseUser, &isLogin);
        } else if (strcmp(prompt, "LOGOUT") == 0) {
            logout(&current_user, &isLogin);
        } else if (strcmp(prompt, "HELP") == 0) {
            helpMenu(current_user, &isLogin);
        } else if (strcmp(prompt, "LIHAT_DENAH") == 0) {
            denahRumahSakit(denah_rs);
        } else if (strcmp(prompt, "LIHAT_RUANGAN") == 0){
            lihatRuangan(denah_rs, dataBaseUser, current_user, isLogin);
        } else if (strcmp(prompt, "EXIT") == 0) {
            EXIT(&current_user, &dataBaseUser, &run_program);
        } else if (strcmp(prompt, "TAMBAH_DOKTER") == 0) {
            tambahDokter(&dataBaseUser, &current_user, &nama_unik, &isLogin);
        } else if (strcmp(prompt, "ASSIGN_DOKTER") == 0) {
            assignDokter(&denah_rs, &dataBaseUser, &current_user, &isLogin);
        } else if (strcmp(prompt, "MINUM_OBAT") == 0) {
            minumObat(&current_user, &dataObat, &isLogin);
        } else if (strcmp(prompt, "MINUM_PENAWAR") == 0) {
            minumPenawar(&current_user, &isLogin);
        }
        else {
            printf("Nama fungsi tidak terdaftar atau kesalahan pengetikan command!\n\n");
        }
    }

    return 0;
}