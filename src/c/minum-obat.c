#include <stdio.h>
#include "../header/stack.h"
#include "../header/user.h"

void minumObat(User *current_user, ObatList *dataObat, boolean *isLogin) {
    if (!(*isLogin)) {
        printf(RED "Anda belum login!\n\n" RESET);
        return;
    }

    if (current_user->role == ROLE_PASIEN) {
        printf(CYAN BOLD "==== DAFTAR OBAT ====\n" RESET);
        // printf("[DEBUG]jumlahobatinventory:%d\n", current_user->inventory.jumlahObat);
        if (current_user->inventory.jumlahObat == 0) {
            printf(YELLOW "Anda tidak memiliki obat apapun di inventory!\n\n" RESET);
            return;
        }

        for (int i = 0; i < current_user->inventory.jumlahObat; i++) {
            Obat *punya = getObatbyId(dataObat, current_user->inventory.obat[i]);
            printf(GRAY "%d. %s\n" RESET, i+1, punya->nama);
        }
        printf("\n");

        int choice;
        do {
            printf(CYAN ">>> Pilih obat untuk diminum: " RESET);
            scanf("%d", &choice);

            if (choice <= 0 || choice > current_user->inventory.jumlahObat) {
                printf(RED "Pilihan nomor tidak tersedia!\n\n" RESET);
            }
        } while (choice <= 0 || choice > current_user->inventory.jumlahObat);

        int obat_id;
        Obat *yangDiminum = getObatbyId(dataObat, current_user->inventory.obat[choice - 1]);
        printf(GREEN "GLEKGLEKGLEK... %s berhasil diminum!!\n\n" RESET, yangDiminum->nama);
        deleteAt(&current_user->inventory, &obat_id, choice - 1);

        // masukin ke stack (ntar berhubungan sama minum penawar)
        push(&current_user->perut, obat_id);
    } else {
        printf(RED "Anda bukan pasien! Tidak bisa minum obat!\n\n" RESET);
    }
}

