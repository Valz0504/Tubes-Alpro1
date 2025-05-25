#include <stdio.h>
#include "../header/user.h"

void minumPenawar(User *current_user, ObatList *dataObat, boolean *isLogin) {
    if (!(*isLogin)) {
        printf(RED "Anda belum login!\n\n" RESET);
        return;
    }

    if (current_user->role == ROLE_PASIEN) {
        char answer[100];
        if (current_user->perut.length == 0) {
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
            pop(&current_user->perut, &value);
            Obat *obat = getObatbyId(dataObat, value);
            insertLast(&current_user->inventory, value);
            printf(GREEN "Uwekkk!!! %s keluar dari tubuhmu dan kembali ke inventory!\n\n" RESET, obat->nama);
        } else {
            printf(YELLOW "Tidak jadi minum penawar...\n\n" RESET);
        }

    } else {
        printf(RED "Anda bukan pasien! Tidak bisa minum penawar!\n\n" RESET);
    }
}