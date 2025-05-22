#include <stdio.h>
#include "../header/user.h"
#include "../header/coloring.h"

void helpMenu(User current_user, boolean *isLogin) {
    printf(CYAN BOLD "==========[ HELP MENU ]==========\n\n" RESET);

    if (!(*isLogin)) {
        printf(YELLOW "Kamu belum login sebagai role apapun. Silakan login terlebih dahulu.\n\n" RESET);
        printf(GRAY BOLD "  %-18s " BRIGHT_BLACK ": Masuk ke dalam akun yang sudah terdaftar\n" RESET, "LOGIN");
        printf(GRAY BOLD "  %-18s " BRIGHT_BLACK ": Membuat akun baru\n" RESET, "REGISTER");
        printf(GRAY BOLD "  %-18s " BRIGHT_BLACK ": Lupa password akun? Gunakan command ini\n\n" RESET, "LUPA_PASSWORD");
    } else {
        if (current_user.role == 0 || current_user.role == 1) {
            printf(GREEN "Halo %s %s!\n" RESET, roleToStr(current_user.role), current_user.username);
            printf(CYAN "Berikut adalah hal-hal yang dapat kamu lakukan sekarang:\n\n" RESET);
            if (current_user.role == 0) {
                printf(GRAY BOLD "  %-18s " BRIGHT_BLACK ": Keluar dari akun yang sedang digunakan\n" RESET, "LOGOUT");
                printf(GRAY BOLD "  %-18s " BRIGHT_BLACK ": Mendaftarkan diri untuk pemeriksaan dokter\n" RESET, "DAFTAR_CHECKUP");
                printf(GRAY BOLD "  %-18s " BRIGHT_BLACK ": Melihat status antrian dari dokter yang kamu pilih untuk check-up\n" RESET, "ANTRIAN");
                printf(GRAY BOLD "  %-18s " BRIGHT_BLACK ": Meminum obat yang kamu miliki di inventori\n" RESET, "MINUM_OBAT");
                printf(GRAY BOLD "  %-18s " BRIGHT_BLACK ": Mengeluarkan obat terakhir yang diminum\n" RESET, "MINUM_PENAWAR");
                printf(GRAY BOLD "  %-18s " BRIGHT_BLACK ": Konsultasi ulang ke dokter untuk izin pulang\n" RESET, "PULANGDOK");
                printf(GRAY BOLD "  %-18s " BRIGHT_BLACK ": Melihat keseluruhan bangunan dari rumah sakit\n" RESET, "LIHAT_DENAH");
                printf(GRAY BOLD "  %-18s " BRIGHT_BLACK ": Melihat nama dokter & pasien di ruangan\n" RESET, "LIHAT_RUANGAN <<nama_ruangan>>");
                printf(GRAY BOLD "  %-18s " BRIGHT_BLACK ": Keluar dari Rumah Sakit\n\n" RESET, "EXIT");
            } else if (current_user.role == 1) {
                printf(GRAY BOLD "  %-18s " BRIGHT_BLACK ": Keluar dari akun yang sedang digunakan\n" RESET, "LOGOUT");
                printf(GRAY BOLD "  %-18s " BRIGHT_BLACK ": Diagnosis penyakit pasien\n" RESET, "DIAGNOSIS");
                printf(GRAY BOLD "  %-18s " BRIGHT_BLACK ": Memberikan obat sesuai penyakit\n" RESET, "NGOBATIN");
                printf(GRAY BOLD "  %-18s " BRIGHT_BLACK ": Melihat keseluruhan bangunan dari rumah sakit\n" RESET, "LIHAT_DENAH");
                printf(GRAY BOLD "  %-18s " BRIGHT_BLACK ": Melihat nama dokter & pasien di ruangan\n" RESET, "LIHAT_RUANGAN <<nama_ruangan>>");
                printf(GRAY BOLD "  %-18s " BRIGHT_BLACK ": Keluar dari Rumah Sakit\n\n" RESET, "EXIT");
            }
        } else if (current_user.role == 2) {
            printf(GREEN "Halo Manager %s!\n" RESET, current_user.username);
            printf(CYAN "Berikut adalah hal-hal yang dapat kamu lakukan sekarang:\n\n" RESET);
            printf(GRAY BOLD "  %-18s " BRIGHT_BLACK ": Keluar dari akun yang sedang digunakan\n" RESET, "LOGOUT");
            printf(GRAY BOLD "  %-18s " BRIGHT_BLACK ": Mendaftarkan dokter baru ke sistem\n" RESET, "TAMBAH_DOKTER");
            printf(GRAY BOLD "  %-18s " BRIGHT_BLACK ": Assign ruangan ke dokter tertentu\n" RESET, "ASSIGN_DOKTER");
            printf(GRAY BOLD "  %-18s " BRIGHT_BLACK ": Melihat data pengguna\n" RESET, "LIHAT_USER");
            printf(GRAY BOLD "  %-18s " BRIGHT_BLACK ": Menampilkan seluruh pasien\n" RESET, "LIHAT_PASIEN");
            printf(GRAY BOLD "  %-18s " BRIGHT_BLACK ": Menampilkan seluruh dokter\n" RESET, "LIHAT_DOKTER");
            printf(GRAY BOLD "  %-18s " BRIGHT_BLACK ": Melihat rincian seluruh ruangan\n" RESET, "LIHAT_SEMUA_ANTRIAN");
            printf(GRAY BOLD "  %-18s " BRIGHT_BLACK ": Menampilkan pengguna secara spesifik\n" RESET, "CARI_USER");
            printf(GRAY BOLD "  %-18s " BRIGHT_BLACK ": Menampilkan pasien secara spesifik\n" RESET, "CARI_PASIEN");
            printf(GRAY BOLD "  %-18s " BRIGHT_BLACK ": Menampilkan dokter secara spesifik\n" RESET, "CARI_DOKTER");
            printf(GRAY BOLD "  %-18s " BRIGHT_BLACK ": Melihat keseluruhan bangunan dari rumah sakit\n" RESET, "LIHAT_DENAH");
            printf(GRAY BOLD "  %-18s " BRIGHT_BLACK ": Melihat nama dokter & pasien di ruangan\n" RESET, "LIHAT_RUANGAN <<nama_ruangan>>");
            printf(GRAY BOLD "  %-18s " BRIGHT_BLACK ": Keluar dari Rumah Sakit\n\n" RESET, "EXIT");
        }
    }
    printf(BLUE "----------------------------------------\n" RESET);
    printf(YELLOW "Footnote:\n" RESET);
    printf(GRAY BOLD "  - Untuk menggunakan aplikasi, masukkan nama fungsi yang terdaftar\n" RESET);
    printf(GRAY BOLD "  - Jangan lupa untuk memasukkan input yang valid\n" RESET);
    printf(GRAY BOLD "  - Command " CYAN BOLD "LUPA_PASSWORD" GRAY BOLD " dapat kamu akses sebelum LOGIN\n" RESET);
    printf(GRAY BOLD "  - Command " CYAN BOLD "HELP" GRAY BOLD " dapat kamu akses kapan saja!\n\n" RESET);
}