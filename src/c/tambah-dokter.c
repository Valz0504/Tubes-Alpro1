#include <stdio.h>
#include <string.h>

#include "../header/user.h"

void assignDokter(Matrix *denah, UserList *list, User *current_user, boolean *isLogin) {
    if (*isLogin) {

        if (current_user->role == ROLE_MANAGER) {
            printf(CYAN BOLD "=== ASSIGN DOKTER ===\n" RESET);
    
            char namaDokter[100], ruang[100];    
            printf(YELLOW "Username: " RESET);
            scanf("%s", namaDokter);
            printf(YELLOW "Ruangan: " RESET);
            scanf("%s", ruang);
            
            // cek apakah namaDokter nya ada 
            User *dokter = findUser(list, namaDokter);
            if (dokter == NULL) {
                printf(RED "Tidak ada dokter dengan nama %s.\n\n" RESET, namaDokter);
                return;
            }

            if (dokter->role != ROLE_DOKTER) {
                printf(RED "%s bukan dokter!\n\n" RESET, dokter->username);
                return;
            }

            int row, col;
            if (getPosisiRuangan(denah, ruang, &row, &col)) {
                if (strcmp(namaDokter, denah->data[row][col].namaDokter) == 0) {
                    printf(BLUE "Dokter %s sudah diassign ke ruangan ini!\n\n" RESET, namaDokter);
                    return;
                }

                boolean kosong = FALSE;
                if (isRuanganKosong(denah->data[row][col])) {
                    kosong = TRUE;
                }
                
                if (kosong && !isDokterSudahAssign(denah, namaDokter)) {
                    strcpy(denah->data[row][col].namaDokter, namaDokter);
                    printf(GREEN BOLD"Dokter %s berhasil ditugaskan ke ruangan %s!\n\n" RESET, namaDokter, ruang);
                } else if (kosong && isDokterSudahAssign(denah, namaDokter)) {
                    char ruangan_asal[10];
                    getRuanganDokter(denah, namaDokter, ruangan_asal);
                    printf(BLUE "Dokter %s sudah diassign ke ruangan %s!\n\n" RESET, namaDokter, ruangan_asal);
                } else if (!kosong && !isDokterSudahAssign(denah, namaDokter)) {
                    printf(BLUE "Ruangan %s sudah ditempati dokter %s!\n" RESET, ruang, denah->data[row][col].namaDokter);
                    printf(RED "Silakan cari ruangan lain untuk dokter %s.\n\n" RESET, namaDokter);
                } else if (!kosong && isDokterSudahAssign(denah, namaDokter)) {
                    char ruangan_asal[10];
                    getRuanganDokter(denah, namaDokter, ruangan_asal);

                    printf(BLUE "Dokter %s sudah diassign ke ruangan %s!\n" RESET, namaDokter, ruangan_asal);
                    printf(RED "Ruangan %s juga sudah ditempati dokter %s!\n\n" RESET, ruang, denah->data[row][col].namaDokter);
                }
            } else {
                printf(RED "Nama ruangan tidak valid!\n\n" RESET);
            }
        } else {
            printf(RED "Anda bukan manager! Tidak bisa assign dokter!\n\n" RESET);
        }
    } else {
        printf(RED "Login sebagai Manager terlebih dahulu!\n\n" RESET);
    }
}

void tambahDokter(UserList *list, User *current_user, Set *set, boolean *isLogin) {
    if (*isLogin) {

        if (current_user->role == ROLE_MANAGER) {
            printf(CYAN BOLD "=== TAMBAH DOKTER ===\n" RESET);
            char username[100], password[100];
            
            printf(YELLOW "Username: " RESET);
            scanf("%s", username);
            printf(YELLOW "Password: " RESET);
            scanf("%s", password);
            
            User *temp_user = findUser(list, username);
            
            char usernameTemp[100];
            strcpy(usernameTemp, username);
            toLower(username);
            if (isUsernameUnique(*set, username)) {
                insertSet(set, username);
    
                User new_user;
                CreateUser(list, &new_user, usernameTemp, password, 1);
                AddUser(list, &new_user);
                
                printf(GREEN BOLD"Dokter %s berhasil ditambahkan!\n\n" RESET, usernameTemp);
            } else {
                if (temp_user != NULL) {
                    if (temp_user->role == ROLE_DOKTER) {
                        printf(YELLOW "Sudah ada Dokter bernama %s!\n\n" RESET, usernameTemp);
                    } else {
                        printf(RED "Sudah ada User bernama %s!\n\n" RESET, usernameTemp);
                    }
                }
            }
        } else {
            printf(RED "Anda bukan manager! Tidak bisa tambah dokter!\n\n" RESET);
        }
    } else {
        printf(RED "Login sebagai Manager terlebih dahulu!\n\n" RESET);
    }
}

