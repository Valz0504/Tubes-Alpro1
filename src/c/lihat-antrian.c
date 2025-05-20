#include <stdio.h>
#include "../header/user.h"

void lihatAntrian(UserList *dataBaseUser, User *current_user, Matrix *denah, boolean *isLogin) {
    if (!(*isLogin)) {
        printf("Login sebagai Manager terlebih dahulu!\n\n");
        return;
    }

    if (current_user->role == ROLE_MANAGER) {
        denahRumahSakit(*denah);

        for (int i = 0; i < denah->rows; i++) {
            for (int j = 0; j < denah->cols; j++) {
                if (!isRuanganKosong(denah->data[i][j])) {
                    printf("============ %c%d ============\n", 'A' + j, i + 1);
                    printf("Kapasitas: %d\n", denah->kapasitasRuangan);
                    printf("Dokter: Dr. %s\n", denah->data[i][j].nama_dokter);
                    
                    Node *curr = denah->data[i][j].antrian.head;
                    printf("Pasien di dalam ruangan: \n");
                    if (!isEmpty(denah->data[i][j].antrian)) {
                        int index = 0;
                        while (curr != NULL && index < denah->kapasitasRuangan) {
                            User *pasien = findUserByID(dataBaseUser, curr->info);
                            printf("\t%d. %s\n", index+1, pasien->username);
                            curr = curr->next;
                            index++;
                        }

                        index = 1;
                        printf("Pasien di dalam antrian: \n");
                        if (curr == NULL) {
                            printf("\tTidak ada pasien di dalam antrian saat ini.\n\n");
                            return;
                        }
                        while (curr != NULL) {
                            User *pasien = findUserByID(dataBaseUser, curr->info);
                            printf("\t%d. %s\n", index, pasien->username);
                            curr = curr->next;
                            index++;
                        }

                    } else {
                        printf("\tTidak ada pasien di dalam ruangan saat ini.\n");
                        printf("Pasien di dalam antrian: \n");
                        printf("\tTidak ada pasien di dalam antrian saat ini.\n");
                    }
                    
                    printf("\n");
                }
            }
        }

    } else {
        printf("Anda bukan manager! Tidak bisa lihat semua antrian!\n\n");
    }
}