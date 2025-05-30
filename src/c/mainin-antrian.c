#include <stdio.h>
#include "../header/user.h"

void skipAntrian(UserList *dataBaseUser, User *current_user, Matrix *denah, boolean *isLogin) {
    if (!(*isLogin)) {
        printf(RED "Login sebagai Pasien terlebih dahulu!\n\n" RESET);
        return;
    }
    
    if (current_user->role != ROLE_PASIEN) {
        printf(RED "Anda bukan pasien! Tidak bisa skip antrian!\n\n" RESET);
        return;
    }

    int ditemukan = 0;
    Queue *antrianPasien;
    int posisiPasien;

    int row,col;
    char dokter[100];
    // cari di mana pasien berada di denah
    for (int i = 0; i < denah->rows; i++) {
        for (int j = 0; j < denah->cols; j++) {
            Queue antrian = denah->data[i][j].antrian;
            Node *curr = antrian.head;
            int posisi = 1;

            while (curr != NULL) {
                if (curr->info == current_user->id) {
                    antrianPasien = &denah->data[i][j].antrian;
                    posisiPasien = posisi;
                    ditemukan = 1;
                    row = i; col = j;
                    strcpy(dokter, denah->data[i][j].nama_dokter);
                }
                curr = curr->next;
                posisi++;
            }  
            if (ditemukan) break;
        }
        if (ditemukan) break;
    }

    if (!ditemukan) {
        printf(RED "Skip antrian gagal! Anda tidak sedang terdaftar di antrian mana pun!\n\n" RESET);
        return;
    }

    if (posisiPasien <= denah->kapasitasRuangan) {
        printf(RED "Anda sudah di dalam ruangan! Tidak bisa skip antrian!\n\n" RESET);
        return;
    }

    if (posisiPasien == denah->kapasitasRuangan + 1) {
        printf(RED "Anda sudah berada di posisi paling depan antrian! Tidak bisa skip lagi.\n\n" RESET);
        return;
    }

    // hapus pasiennya dari antrian
    Node *curr = antrianPasien->head;
    Node *prev = NULL;
    while (curr != NULL) {
        if (curr->info == current_user->id) {
            if (prev != NULL) {
                prev->next = curr->next;
            } else {
                antrianPasien->head = curr->next;
            }
            if (curr == antrianPasien->tail) {
                antrianPasien->tail = prev;
            }
            free(curr);
            break;
        }
        prev = curr;
        curr = curr->next;
    }

    // sisipkan pasiennya menjadi yang pertama di luar ruangan
    Node *nodePasien = (Node *)malloc(sizeof(Node));
    nodePasien->info = current_user->id;
    nodePasien->next = NULL;

    curr = antrianPasien->head;
    int posisiNew = 1;
    prev = NULL;

    while (curr != NULL && posisiNew < denah->kapasitasRuangan) {
        curr = curr->next;
        posisiNew++;
    }
    nodePasien->next = curr->next;
    curr->next = nodePasien;
    if (curr == antrianPasien->tail) {
        antrianPasien->tail = nodePasien;
    }
    printf(GREEN "Anda berhasil maju ke depan antrian Dr. %s di ruangan %c%d!\n", dokter, 'A'+row, col+1);
    printf(GREEN "Posisi antrian Anda sekarang: 1\n\n" RESET);
}   

void cancelAntrian(UserList *dataBaseUser, User *current_user, Matrix *denah, boolean *isLogin) {
    if (!(*isLogin)) {
        printf(RED "Login sebagai Pasien terlebih dahulu!\n\n" RESET);
        return;
    }
    
    if (current_user->role != ROLE_PASIEN) {
        printf(RED "Anda bukan pasien! Tidak bisa cancel antrian!\n\n" RESET);
        return;
    }

    int ditemukan = 0;
    Queue *antrianPasien;
    int posisiPasien;

    int row,col;
    char dokter[100];
    // cari di mana pasien berada di denah
    for (int i = 0; i < denah->rows; i++) {
        for (int j = 0; j < denah->cols; j++) {
            Queue antrian = denah->data[i][j].antrian;
            Node *curr = antrian.head;
            int posisi = 1;

            while (curr != NULL) {
                if (curr->info == current_user->id) {
                    antrianPasien = &denah->data[i][j].antrian;
                    posisiPasien = posisi;
                    ditemukan = 1;
                    row = i; col = j;
                    strcpy(dokter, denah->data[i][j].nama_dokter);
                }
                curr = curr->next;
                posisi++;
            }  
            if (ditemukan) break;
        }
        if (ditemukan) break;
    }

    if (!ditemukan) {
        printf(RED "Pembatalan antrian gagal! Anda tidak sedang terdaftar di antrian mana pun!\n\n" RESET);
        return;
    }

    if (posisiPasien <= denah->kapasitasRuangan) {
        printf(RED "Anda sudah di dalam ruangan! Tidak bisa batalkan antrian!\n\n" RESET);
        return;
    }

    // hapus pasien dari antrian
    Node *curr = antrianPasien->head;
    Node *prev = NULL;
    while (curr != NULL) {
        if (curr->info == current_user->id) {
            if (prev != NULL) {
                prev->next = curr->next;
            } else {
                antrianPasien->head = curr->next;
            }
            if (curr == antrianPasien->tail) {
                antrianPasien->tail = prev;
            }
            free(curr);
            break;
        }
        prev = curr;
        curr = curr->next;
    }
    printf(GREEN "Anda berhasil keluar dari antrian Dr. %s di ruangan %c%d.\n\n" RESET, dokter, 'A'+row, col+1);
}