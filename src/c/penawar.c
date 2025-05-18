#include <stdio.h>
#include "../header/user.h"

void minumPenawar(User *current_user, boolean *isLogin) {
    if (!(*isLogin)) {
        printf("Anda belum login!\n\n");
        return;
    }

    if (current_user->role == ROLE_PASIEN) {
        char answer[100];
        if (current_user->inventory.urutanObat.top == -1) {
            printf("Anda belum minum obat apapun!\n\n");
            return;
        }

        printf("Yakin minum penawar? (y/n) ");

        do {
            scanf("%s", answer);
            toLower(answer);

            if (strcmp(answer, "y") != 0 && strcmp(answer, "n") != 0) {
                printf("Masukan anda belum benar, coba lagi!\n\n");
                printf("Yakin minum penawar? (y/n) ");
            }
        } while (strcmp(answer, "y") != 0 && strcmp(answer, "n") != 0);


        if (strcmp(answer, "y") == 0) {
            int value;
            pop(&current_user->inventory.urutanObat, &value);
            insertLast(&current_user->inventory, value);
        } else {
            printf("Tidak jadi minum penawar...\n\n");
        }

    } else {
        printf("Anda bukan pasien! Tidak bisa penawar!\n\n");
    }
}