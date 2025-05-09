#include <stdio.h>
#include <stdlib.h>
#include "./header/user.h"

int main(int argc, char* argv[]) {

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
    initSet(&nama_unik, 5);

    // LOAD DATA from file folder
    LOAD(&dataBaseUser, &dataPenyakit, &dataObat, &dataObatPenyakit);

    // Inisialisasi state LOGIN
    User current_user;
    boolean isLogin = FALSE;

    // Inisialisasi Denah
    denah_rs.rows = 5;
    denah_rs.cols = 5;

    // Program Utama
    boolean run_program = TRUE;
    while (run_program) {
        char prompt[100];
        printf(">>> ");
        scanf("%s", prompt);
    
        if (strcmp(prompt, "LOGIN") == 0) {
            system("clear");
            login(&dataBaseUser, &current_user, &isLogin);
        } else if (strcmp(prompt, "REGISTER") == 0) {
            system("clear");
            registerPasien(&dataBaseUser, &nama_unik, &isLogin);
        } else if (strcmp(prompt, "LUPA_PASSWORD") == 0) {
            system("clear");
            lupa_password(&dataBaseUser, &isLogin);
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
            EXIT(&current_user, &dataBaseUser, &run_program);
        } else if (strcmp(prompt, "TAMBAH_DOKTER") == 0) {
            system("clear");
            tambahDokter(&dataBaseUser, &current_user, &nama_unik, &isLogin);
        }
        else {
            printf("Nama fungsi tidak terdaftar atau kesalahan pengetikan nama fungsi!\n\n");
        }
    }

    return 0;
}