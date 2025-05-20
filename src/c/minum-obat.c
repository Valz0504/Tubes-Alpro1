#include <stdio.h>
#include "../header/stack.h"
#include "../header/user.h"

void minumObat(User *current_user, ObatList *dataObat, boolean *isLogin) {
    if (!(*isLogin)) {
        printf("Anda belum login!\n\n");
        return;
    }

    if (current_user->role == ROLE_PASIEN) {
        printf("==== DAFTAR OBAT ====\n");
        
        if (current_user->inventory.jumlahObat == 0) {
            printf("Anda tidak memiliki obat apapun di inventory!\n\n");
            return;
        }

        for (int i = 0; i < current_user->inventory.jumlahObat; i++) {
            printf("%d. %s\n", i+1, getObatName(dataObat, current_user->inventory.obat[i]));
        }
        printf("\n");

        int choice;
        do {
            printf(">>> Pilih obat untuk diminum: ");
            scanf("%d", &choice);

            if (choice <= 0 || choice > current_user->inventory.jumlahObat) {
                printf("Pilihan nomor tidak tersedia!\n\n");
            }
        } while (choice <= 0 || choice > current_user->inventory.jumlahObat);

        int obat_id;
        printf("GLEKGLEKGLEK... %s berhasil diminum!!\n\n", getObatName(dataObat, current_user->inventory.obat[choice - 1]));
        deleteAt(&current_user->inventory, &obat_id, choice - 1);

        // masukin ke stack (ntar berhubungan sama minum penawar)
        push(&current_user->perut, obat_id);
    } else {
        printf("Anda bukan pasien! Tidak bisa minum obat!\n\n");
    }
}

