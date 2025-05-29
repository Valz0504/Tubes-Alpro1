#include <stdio.h>
#include <stdlib.h>
#include "./header/user.h"

int main(int argc, char* argv[]) {
    system("clear");

    if (argc < 2) { 
        printf(RED "\nTidak ada nama folder yang diberikan!\n" RESET);
        printf(RED "Usage: ./main <<nama_folder>>\n" RESET);
        return 0;
    }

    // Inisialisasi semua Database yang diperlukan
    UserList dataBaseUser;
    PenyakitList dataPenyakit;
    ObatList dataObat;
    Obat_PenyakitList dataObatPenyakit;
    Matrix denahRS;
    Set nama_unik;
    
    initSet(&nama_unik, 5);

    // LOAD DATA from file folder
    LOAD(argv[1], &dataBaseUser, &dataPenyakit, &dataObat, &dataObatPenyakit, &nama_unik, &denahRS);
    
    // Inisialisasi state LOGIN
    User current_user;
    boolean isLogin = FALSE;

    printBanner();
    printf(CYAN "Ketik command " YELLOW BOLD "HELP" RESET CYAN " untuk melihat apa saja yang dapat kamu lakukan sekarang!\n\n" RESET);

    // Program Utama
    boolean run_program = TRUE;
    while (run_program) {
        char prompt[100];
        
        if (isLogin) {
            printf(GRAY "%s@%s " RESET, current_user.username, roleToStr(current_user.role));
        } else {
            printf(GRAY "anon@none " RESET);
        }
        printf(MAGENTA ">>> Command: " RESET);

        scanf("%s", prompt);
        printf("\n");

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
            denahRumahSakit(denahRS, &isLogin);
        } else if (strcmp(prompt, "LIHAT_RUANGAN") == 0){
            lihatRuangan(denahRS, dataBaseUser, current_user, &isLogin);
        } else if (strcmp(prompt, "EXIT") == 0) {
            EXIT(&dataBaseUser, &dataObat, &dataPenyakit, &dataObatPenyakit, &denahRS, &run_program);
        } else if (strcmp(prompt, "TAMBAH_DOKTER") == 0) {
            tambahDokter(&dataBaseUser, &current_user, &nama_unik, &isLogin);
        } else if (strcmp(prompt, "ASSIGN_DOKTER") == 0) {
            assignDokter(&denahRS, &dataBaseUser, &current_user, &isLogin);
        } else if (strcmp(prompt, "MINUM_OBAT") == 0) {
            minumObat(&current_user, &dataBaseUser,&dataObat, &isLogin);
        } else if (strcmp(prompt, "PENAWAR") == 0) {
            minumPenawar(&current_user, &dataBaseUser,&dataObat, &denahRS, &isLogin);
        } else if (strcmp(prompt, "DIAGNOSIS") == 0) {
            diagnosis(&current_user, &dataBaseUser, &dataPenyakit, &isLogin, &denahRS);
        } else if (strcmp(prompt, "LIHAT_SEMUA_ANTRIAN") == 0) {
            lihatAntrian(&dataBaseUser, &current_user, &denahRS, &isLogin);
        } else if (strcmp(prompt, "DAFTAR_CHECKUP") == 0) {
            daftarCheckUp(&current_user, &dataBaseUser, &isLogin, &denahRS);
        } else if (strcmp(prompt, "CARI_USER") == 0) {
            cariUser(&dataBaseUser, &current_user, &isLogin);
        } else if (strcmp(prompt, "CARI_PASIEN") == 0) {
            cariPasien(&dataBaseUser, &current_user, &isLogin);
        } else if (strcmp(prompt, "CARI_DOKTER") == 0) {
            cariDokter(&dataBaseUser, &current_user, &isLogin);
        } else if (strcmp(prompt, "LIHAT_USER") == 0) {
            lihatUser(&dataBaseUser, &current_user, &isLogin);
        } else if (strcmp(prompt, "LIHAT_PASIEN") == 0) {
            lihatPasien(&dataBaseUser, &current_user, &isLogin);
        } else if (strcmp(prompt, "LIHAT_DOKTER") == 0) {
            lihatDokter(&dataBaseUser, &current_user, &isLogin);
        } else if (strcmp(prompt, "ANTRIAN") == 0) {
            antrianSaya(&current_user, &denahRS, &isLogin);
        } else if (strcmp(prompt, "PULANGDOK") == 0) {
            bolehPulangGaa(&current_user,  &dataBaseUser,&dataPenyakit, &dataObat, &dataObatPenyakit, &denahRS, &isLogin);
        } else if (strcmp(prompt, "NGOBATIN") == 0) {
            ngobatin(&current_user, &dataBaseUser, &dataPenyakit, &dataObat, &dataObatPenyakit, &denahRS, &isLogin);
        } else if (strcmp(prompt, "SKIP_ANTRIAN") == 0) {
            skipAntrian(&dataBaseUser, &current_user, &denahRS, &isLogin);
        } else if (strcmp(prompt, "CANCEL_ANTRIAN") == 0) {
            cancelAntrian(&dataBaseUser, &current_user, &denahRS, &isLogin);
        }
        else {
            printf(RED "Nama fungsi tidak terdaftar atau kesalahan pengetikan command!\n\n" RESET);
        }
    }

    return 0;
}