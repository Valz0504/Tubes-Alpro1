#include <stdio.h>
#include "../header/user.h"

void cariUser(UserList *dataBaseUser, User *current_user, boolean *isLogin) {
    if (!(*isLogin)) {
        printf("Login sebagai Manager terlebih dahulu!\n\n");
        return;
    }

    if (current_user->role == ROLE_MANAGER) {
        printf("Cari berdasarkan?\n");
        printf("1. ID\n");
        printf("2. Nama\n");
        printf(">> Pilihan: ");
        
        int pilihan;
        scanf("%d", &pilihan);

        User *u;
        switch (pilihan) {
            case 1:
                int nomor_id;
                printf("\n>> Masukkan nomor ID user: ");
                scanf("%d", &nomor_id);

                u = findUserByID(dataBaseUser, nomor_id);
                if (u == NULL) {
                    printf("Tidak ditemukan pengguna dengan ID %d\n\n", nomor_id);
                } else {
                    printf("\nMenampilkan pengguna dengan nomor ID %d...\n", nomor_id);
                    printf("ID |    Nama    |    Role    |    Penyakit\n");
                    printf("------------------------------------------\n");
                    if (u->role == ROLE_PASIEN) {
                        printf("%d |  %s      |  %s      |  %s\n\n", nomor_id, u->username, "Pasien", u->riwayat_penyakit);
                    } else if (u->role == ROLE_DOKTER) {
                        printf("%d |  %s      |  %s      |    -\n\n", nomor_id, u->username, "Dokter");
                    } else {
                        printf("%d |  %s      |  %s      |    -\n\n", nomor_id, u->username, "Manager");
                    }
                }
                break;
            
            case 2:
                char username[100];
                printf("\n>> Masukkan nama user: ");
                scanf("%s", username);

                u = findUser(dataBaseUser, username);
                if (u == NULL) {
                    printf("Tidak ditemukan pengguna dengan nama %s\n\n", username);
                } else {
                    printf("\nMenampilkan pengguna dengan username %s...\n", username);
                    printf("ID |    Nama    |    Role    |    Penyakit\n");
                    printf("------------------------------------------\n");
                    if (u->role == ROLE_PASIEN) {
                        printf("%d |  %s      |  %s      |  %s\n\n", u->id, u->username, "Pasien", u->riwayat_penyakit);
                    } else {
                        printf("%d |  %s      |  %s      |    -\n\n", u->id, u->username, "Dokter");
                    }
                }
                break;
            
            default:
                printf("Pilihan tidak valid!\n\n");
                break;
        }
    } else {
        printf("Anda bukan manager! Tidak bisa cari user!\n\n");
    }
}

void cariPasien(UserList *dataBaseUser, User *current_user, boolean *isLogin) {
    if (!(*isLogin)) {
        printf("Login sebagai Manager terlebih dahulu!\n\n");
        return;
    }

    if (current_user->role == ROLE_MANAGER) {
        printf("Cari berdasarkan?\n");
        printf("1. ID\n");
        printf("2. Nama\n");
        printf("3. Penyakit\n");
        printf(">> Pilihan: ");
        
        int pilihan;
        scanf("%d", &pilihan);

        User *u;

        switch (pilihan) {
            case 1:
                int nomor_id;
                printf("\n>> Masukkan nomor ID user: ");
                scanf("%d", &nomor_id);

                u = findUserByID(dataBaseUser, nomor_id);
                if (u == NULL) {
                    printf("Tidak ditemukan pasien dengan ID %d\n\n", nomor_id);
                } else {
                    if (u->role == ROLE_PASIEN) {
                        printf("\nMenampilkan pasien dengan nomor ID %d...\n", nomor_id);
                        printf("ID |    Nama    |    Role    |    Penyakit\n");
                        printf("------------------------------------------\n");
                        printf("%d |  %s      |  %s      |  %s\n\n", nomor_id, u->username, "Pasien", u->riwayat_penyakit);
                    } else {
                        printf("Tidak ada pasien dengan ID %d\n\n", nomor_id);
                    }
                }            
                break;
            case 2:
                char username[100];
                printf("\n>> Masukkan nama user: ");
                scanf("%s", username);

                u = findUser(dataBaseUser, username);
                if (u == NULL) {
                    printf("Tidak ditemukan pasien dengan nama %s\n\n", username);
                } else {
                    if (u->role == ROLE_PASIEN) {
                        printf("\nMenampilkan pasien dengan username %s...\n", username);
                        printf("ID |    Nama    |    Role    |    Penyakit\n");
                        printf("------------------------------------------\n");
                        printf("%d |  %s      |  %s      |  %s\n\n", u->id, u->username, "Pasien", u->riwayat_penyakit);
                    } else {
                        printf("Tidak ada pasien dengan nama %s\n\n", username);
                    }
                }            
                break;
            case 3: // cari berdasarkan penyakit
                char penyakit[100];
                printf("\n>> Masukkan nama penyakit: ");
                scanf("%s", penyakit);
                        
                printf("Urutkan berdasarkan?\n");
                printf("1. ID\n");
                printf("2. Nama\n");
                printf(">> Pilihan: ");
                
                int pil, urut;
                scanf("%d", &pil); 
                boolean found = FALSE;
                switch (pil) {
                    case 1:
                        printf("Urutkan sort ID?\n");
                        printf("1. ASC\n");
                        printf("2. DESC\n");
                        printf(">> Pilihan: ");

                        scanf("%d", &urut);
                        switch (urut) {
                            case 1:
                                printf("\nMenampilkan pasien dengan penyakit %s dengan ID terurut ascendant...\n", penyakit);
                                for (int i = 0; i < dataBaseUser->Neff; i++) {
                                    if (strcmp(dataBaseUser->data[i].riwayat_penyakit, penyakit) == 0) {
                                        found = TRUE;
                                        printf("ID |    Nama    |    Penyakit   \n");
                                        printf("----------------------------\n");
                                        printf("%d |  %s      |  %s      \n\n", dataBaseUser->data[i].id, dataBaseUser->data[i].username, penyakit);
                                    }
                                }
                                if (!found) {
                                    printf("Tidak ada pasien dengan riwayat penyakit %s\n\n", penyakit);
                                }                               
                                break;
                            case 2:
                                printf("\nMenampilkan pasien dengan penyakit %s dengan ID terurut ascendant...\n", penyakit);
                                for (int i = dataBaseUser->Neff; i >= 0; i--) {
                                    if (strcmp(dataBaseUser->data[i].riwayat_penyakit, penyakit) == 0) {
                                        found = TRUE;
                                        printf("ID |    Nama    |    Penyakit   \n");
                                        printf("----------------------------\n");
                                        printf("%d |  %s      |  %s      \n\n", dataBaseUser->data[i].id, dataBaseUser->data[i].username, penyakit);
                                    }
                                }
                                if (!found) {
                                    printf("Tidak ada pasien dengan riwayat penyakit %s\n\n", penyakit);
                                }  
                                break;
                            default:
                                printf("Pilihan tidak valid!\n\n");
                                break;
                        }

                        break;
                    case 2:
                        printf("Urutkan sort Nama?\n");
                        printf("1. ASC (A-Z)\n");
                        printf("2. DESC (Z-A)\n");
                        printf(">> Pilihan: ");

                        scanf("%d", &urut);
                        
                        UserList temp;
                        copyList(*dataBaseUser, &temp);
                        switch (urut) {
                            case 1:

                                sortListByUsername(&temp, TRUE);
                                printf("\nMenampilkan pasien dengan penyakit %s dengan Nama terurut ascendant...\n", penyakit);
                                for (int i = 0; i < temp.Neff; i++) {
                                    if (temp.data[i].role == ROLE_PASIEN && strcmp(temp.data[i].riwayat_penyakit, penyakit) == 0) {
                                        found = TRUE;
                                        printf("ID |    Nama    |    Penyakit   \n");
                                        printf("----------------------------\n");
                                        printf("%d |  %s      |  %s      \n\n", temp.data[i].id, temp.data[i].username, penyakit);
                                    }
                                }
                                if (!found) {
                                    printf("Tidak ada pasien dengan riwayat penyakit %s\n\n", penyakit);
                                }
                                break;
                            case 2:

                                sortListByUsername(&temp, FALSE);
                                printf("\nMenampilkan pasien dengan penyakit %s dengan Nama terurut descendant...\n", penyakit);
                                for (int i = 0; i < temp.Neff; i++) {
                                    if (temp.data[i].role == ROLE_PASIEN && strcmp(temp.data[i].riwayat_penyakit, penyakit) == 0) {
                                        found = TRUE;
                                        printf("ID |    Nama    |    Penyakit   \n");
                                        printf("----------------------------\n");
                                        printf("%d |  %s      |  %s      \n\n", temp.data[i].id, temp.data[i].username, penyakit);
                                    }
                                }
                                if (!found) {
                                    printf("Tidak ada pasien dengan riwayat penyakit %s\n\n", penyakit);
                                }
                                break;
                            default:
                                printf("Pilihan tidak valid!\n\n");
                                break;
                        }
                        break;
                    default:
                        printf("Pilihan tidak valid!\n\n");
                        break;
                }
                break;
            default:
                printf("Pilihan tidak valid!\n\n");
                break;
        }

    } else {
        printf("Anda bukan manager! Tidak bisa cari user!\n\n");
    }
}

void cariDokter(UserList *dataBaseUser, User *current_user, boolean *isLogin) {
    if (!(*isLogin)) {
        printf("Login sebagai Manager terlebih dahulu!\n\n");
        return;
    }

    if (current_user->role == ROLE_MANAGER) {
        printf("Cari berdasarkan?\n");
        printf("1. ID\n");
        printf("2. Nama\n");
        printf(">> Pilihan: ");
        
        int pilihan;
        scanf("%d", &pilihan);

        User *u;
        switch (pilihan) {
            case 1:
                int nomor_id;
                printf("\n>> Masukkan nomor ID user: ");
                scanf("%d", &nomor_id);

                u = findUserByID(dataBaseUser, nomor_id);
                if (u == NULL) {
                    printf("Tidak ditemukan dokter dengan ID %d\n\n", nomor_id);
                } else {
                    if (u->role == ROLE_DOKTER) {
                        printf("\nMenampilkan pengguna dengan nomor ID %d...\n", nomor_id);
                        printf("ID |    Nama   \n");
                        printf("---------------\n");
                        printf("%d |  %s       \n\n", nomor_id, u->username);
                    } else {
                        printf("Tidak ditemukan dokter dengan ID %d\n\n", nomor_id);
                    }
                }
                break;
            
            case 2:
                char username[100];
                printf("\n>> Masukkan nama user: ");
                scanf("%s", username);

                u = findUser(dataBaseUser, username);
                if (u == NULL) {
                    printf("Tidak ditemukan dokter dengan nama %s\n\n", username);
                } else {
                    if (u->role == ROLE_DOKTER) {
                        printf("\nMenampilkan dokter dengan username %s...\n", username);
                        printf("ID |    Nama   \n");
                        printf("---------------\n");
                        printf("%d |  %s       \n\n", u->id, u->username);
                    } else {
                        printf("Tidak ditemukan dokter dengan nama %s\n\n", username);
                    }
                }
                break;
            
            default:
                printf("Pilihan tidak valid!\n\n");
                break;
        }
    } else {
        printf("Anda bukan manager! Tidak bisa cari user!\n\n");        
    }
}