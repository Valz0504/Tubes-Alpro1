#include <stdio.h>
#include "../header/user.h"

void minumPenawar(User *current_user, UserList *dataBaseUser, ObatList *dataObat, boolean *isLogin) {
    if (!(*isLogin)) {
        printf(RED "Anda belum login!\n\n" RESET);
        return;
    }

    if (current_user->role == ROLE_PASIEN) {
        User *pasien = findUser(dataBaseUser, current_user->username);

        char answer[10];
        char answer[10];
        // tidak bisa penawar jika perut kosong
        if (pasien->perut.length == 0) {
            printf(YELLOW "Perut kosong!! Belum ada obat yang dimakan.\n\n" RESET);
            return;
        }

        printf(CYAN "Yakin minum penawar? (" GREEN "y" RESET CYAN "/" RED "n" RESET CYAN ") " RESET);

        do {
            scanf("%s", answer);
            toLower(answer);

            if (strcmp(answer, "y") != 0 && strcmp(answer, "n") != 0) {
                printf(RED "Masukan anda belum benar, coba lagi!\n\n" RESET);
                printf(CYAN "Yakin minum penawar? (" GREEN "y" RESET CYAN "/" RED "n" RESET CYAN ") " RESET);
            }
        } while (strcmp(answer, "y") != 0 && strcmp(answer, "n") != 0);

        if (strcmp(answer, "y") == 0) {
            int value;
            pop(&pasien->perut, &value);
            Obat *obat = getObatbyId(dataObat, value);
            insertLast(&pasien->inventory, value);
            printf(GREEN "Uwekkk!!! %s keluar dari tubuhmu dan kembali ke inventory, tapi...\n\n" RESET, obat->nama);

            pasien->nyawa--;
            if (pasien->nyawa == 0) {
                printf(RED "[Dokter]: 'Tidakkk, kenapa kamu salah minum obat sampe 3 kaliii...\n" RESET);
                printf(RED "Pasien mati... ded~\n\n" RESET);
                deleteUser(dataBaseUser, pasien);
                *isLogin = FALSE;
                return;
            } else {
                printf(YELLOW "Nyawa berkurang 1\n" RESET);
                printf(YELLOW "Sisa nyawa anda: %d\n\n" RESET, pasien->nyawa);
            }
        } else {
            printf(YELLOW "Tidak jadi minum penawar...\n\n" RESET);
        }

    } else {
        printf(RED "Anda bukan pasien! Tidak bisa minum penawar!\n\n" RESET);
    }
}