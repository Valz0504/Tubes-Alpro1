#include <stdio.h>
#include <string.h>

#include "../header/user.h"

void assignDokter(Matrix *denah, UserList *list, User *current_user, boolean *isLogin) {
    if (*isLogin) {
        if (current_user->role == ROLE_MANAGER) {
            printf("=== ASSIGN DOKTER ===\n");
    
            char nama_dokter[100], ruang[100];    
            printf("Username: ");
            scanf(" %[^\n]", nama_dokter);
            printf("Ruangan: ");
            scanf(" %[^\n]", ruang);
            
            // cek apakah nama_dokter nya ada 
            User *dokter = findUser(list, nama_dokter);
            if (dokter == NULL) {
                printf("Tidak ada dokter dengan nama %s.\n\n", nama_dokter);
                return;
            }

            if (dokter->role != ROLE_DOKTER) {
                printf("%s bukan dokter!\n\n", dokter->username);
                return;
            }

            int row,col;
            if (getPosisiRuangan(denah, ruang, &row, &col)) {
                boolean kosong = FALSE;
                if (isRuanganKosong(denah->data[row][col])) {
                    kosong = TRUE;
                }
                
                if (kosong && !isDokterSudahAssign(denah, nama_dokter)) {
                    strcpy(denah->data[row][col].nama_dokter, nama_dokter);
                    printf("Dokter %s berhasil ditugaskan ke ruangan %s!\n\n", nama_dokter, ruang);
                } else if (kosong && isDokterSudahAssign(denah, nama_dokter)) {
                    printf("Dokter %s sudah diassign ke ruangan %s!\n\n", nama_dokter, ruang);
                } else if (!kosong && !isDokterSudahAssign(denah, nama_dokter)) {
                    printf("Dokter %s sudah menempati ruangan %s!\n", denah->data[row][col].nama_dokter, ruang);
                    printf("Silakan cari ruangan lain untuk dokter %s.\n\n", nama_dokter);
                } else if (!kosong && isDokterSudahAssign(denah, nama_dokter)) {
                    printf("Dokter %s sudah diassign ke ruangan lain!\n", nama_dokter);
                    printf("Ruangan %s juga sudah ditempati dokter %s!\n\n", ruang, denah->data[row][col].nama_dokter);
                }
            } else {
                printf(("Nama ruangan tidak valid!\n\n"));
            }
        } else {
            printf("Anda bukan manager! Tidak bisa assign dokter!\n\n");
        }
    } else {
        printf("Login sebagai Manager terlebih dahulu!\n\n");
    }
}

void tambahDokter(UserList *list, User *current_user, Set *set, boolean *isLogin) {
    if (*isLogin) {
        if (current_user->role == ROLE_MANAGER) {
            printf("=== TAMBAH DOKTER ===\n");
            char username[100], password[100];
            
            printf("Username: ");
            scanf(" %[^\n]", username);
            printf("Password: ");
            scanf(" %[^\n]", password);
            
            User *temp_user = findUser(list, username);

            toLower(username);
            if (isUsernameUnique(*set, username)) {
                insertSet(set, username);
    
                User new_user;
                CreateUser(list, &new_user, username, password, 1);
                AddUser(list, new_user);
                
                printf("Dokter %s berhasil ditambahkan!\n\n", username);
            } else {
                if (temp_user != NULL) {
                    if (temp_user->role == ROLE_DOKTER) {
                        printf("Sudah ada Dokter bernama %s!\n\n", username);
                    } else {
                        printf("Sudah ada User bernama %s!\n\n", username);
                    }
                }
            }
        } else {
            printf("Anda bukan manager! Tidak bisa tambah dokter!\n\n");
        }
    } else {
        printf("Login sebagai Manager terlebih dahulu!\n\n");
    }

}

