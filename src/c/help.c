#include <stdio.h>
#include "user.h"

void helpMenu(User current_user, boolean *isLogin) {
    printf("=========== HELP ===========\n\n");
    if (!(*isLogin)) {
        printf("Kamu belum login sebagai role apapun. Silahkan login terlebih dahulu.\n");
        printf("\t1. LOGIN: Masuk ke dalam akun yang sudah terdaftar\n");
        printf("\t2. REGISTER: Membuat akun baru\n");
    } else {
        if (current_user.role == 0 || current_user.role == 1) {
            printf("Halo %s %s. Kamu memanggil command HELP. Kamu pasti sedang kebingungan.\n", roleToStr(current_user.role), current_user.username);
            printf("Berikut adalah hal-hal yang dapat kamu lakukan sekarang: \n");
            if (current_user.role == 0) {
                printf("\t1. LOGOUT: Keluar dari akun yang sedang digunakan\n");
                printf("\t2. DAFTAR_CHECKUP: Mendaftarkan diri untuk pemeriksaan dokter\n");
                printf("\t3. ANTRIAN_SAYA: Melihat status antrian dari dokter yang kamu pilih untuk check-up\n");
                printf("\t4. MINUM_OBAT: Meminum obat yang kamu miliki di inventori\n");
                printf("\t5. MINUM_PENAWAR: Mengeluarkan obat terakhir yang diminum\n");
                printf("\t6. BOLEH_PULANG_GA: Konsultasi ulang ke dokter untuk mendapatkan izin pulang\n");
                printf("\t7. EXIT: Keluar dari Rumah Sakit\n");
            } else if (current_user.role == 1) {
                printf("\t1. LOGOUT: Keluar dari akun yang sedang digunakan\n");
                printf("\t2. DIAGNOSIS: Melakukan diagnosis penyakit pasien berdasarkan kondisi tubuh pasien\n");
                printf("\t3. NGOBATIN: Memberikan obat-obat yang sesuai dengan penyakit kepada pasien\n");
                printf("\t4. EXIT: Keluar dari Rumah Sakit\n");
            }
        } else if (current_user.role == 2) {
            printf("Halo Manager %s. Kenapa kamu memanggil command HELP? Kan kamu manager, tapi yasudahlah kamu pasti sedang kebingungan.\n", current_user.username);
            printf("Berikut adalah hal-hal yang dapat kamu lakukan sekarang: \n");
            printf("\t1. LOGOUT: Keluar dari akun yang sedang digunakan\n");
            printf("\t2. TAMBAH_DOKTER: Mendaftarkan dokter baru ke sistem\n");
            printf("\t3. ASSIGN_DOKTER: Melakukan assign ruangan ke dokter tertentu\n");
            printf("\t4. LIHAT_USER: Melihat data pengguna dan memilih metode penampilan data pengguna\n");
            printf("\t5. LIHAT_ANTRIAN: Melihat rincian seluruh ruangan di Rumah Sakit\n");
            printf("\t6. CARI_USER: Mencari data pengguna secara spesifik\n");
        }
    }
    printf("Footnote: \n");
    printf("\t1. Untuk menggunakan aplikasi, silahkan masukkan nama fungsi yang terdaftar\n");
    printf("\t2. Jangan lupa untuk memasukkan input yang valid\n\n");
}