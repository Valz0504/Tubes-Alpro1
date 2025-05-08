#include <stdio.h>
#include <stdlib.h>
#include "user.h"

int main(int argc, char* argv[]) {

    // Inisialisasi Database User
    UserList database;
    CreateListDin(&database, 5);

    // Inisialisasi Set nama unik Pasien dan Dokter
    Set nama_unik;
    initSet(&nama_unik, 5);

    // LOAD DATA from file folder
    /* belum ada */

    // Inisialisasi state LOGIN
    User current_user;
    boolean isLogin = FALSE;

    // Inisialisasi Denah
    Matrix denah_rs;
    denah_rs.rows = 5;
    denah_rs.cols = 5;

    // Inisialisasi INFINITELOOP program
    boolean run_program = TRUE;
    while (run_program) {
        char prompt[100];
        printf(">>> ");
        scanf("%s", prompt);
    
        if (strcmp(prompt, "LOGIN") == 0) {
            system("clear");
            login(&database, &current_user, &isLogin);
        } else if (strcmp(prompt, "REGISTER") == 0) {
            system("clear");
            registerPasien(&database, &nama_unik, &isLogin);
        } else if (strcmp(prompt, "LUPA_PASSWORD") == 0) {
            system("clear");
            lupa_password(&database, &isLogin);
        } else if (strcmp(prompt, "LOGOUT") == 0) {
            system("clear");
            logout(&current_user, &isLogin);
        } else if (strcmp(prompt, "HELP") == 0) {
            system("clear");
            helpMenu(current_user, &isLogin);
        } else if (strcmp(prompt, "LIHAT_DENAH") == 0) {
            system("clear");
            denahRumahSakit(denah_rs);
        } else if (strcmp(prompt, "EXIT") == 0) {
            system("clear");
            EXIT(&current_user, &database, &run_program);
        } else if (strcmp(prompt, "TAMBAH_DOKTER") == 0) {
            system("clear");
            tambahDokter(&database, &nama_unik);
        }
        else {
            printf("Nama fungsi tidak terdaftar atau kesalahan pengetikan nama fungsi!\n\n");
        }
    }

    return 0;
}