#include <stdio.h>
#include "../header/user.h"

void printUserTableHeader() {
    printf(BLUE BOLD "+-----+----------------------+-----------+----------------------+\n" RESET);
    printf(BLUE BOLD "| ID  | Nama                 | Role      | Penyakit             |\n" RESET);
    printf(BLUE BOLD "+-----+----------------------+-----------+----------------------+\n" RESET);
}

void printUserTableRow(User *u) {
    printf("| %-3d | %-20s | %-9s | %-20s |\n",
        u->id,
        u->username,
        u->role == ROLE_PASIEN ? "Pasien" : (u->role == ROLE_DOKTER ? "Dokter" : "Manager"),
        u->role == ROLE_PASIEN ? u->riwayat_penyakit : "-"
    );
}

void printPasienTableHeader() {
    printf(BLUE BOLD "+-----+----------------------+----------------------+\n" RESET);
    printf(BLUE BOLD "| ID  | Nama                 | Penyakit             |\n" RESET);
    printf(BLUE BOLD "+-----+----------------------+----------------------+\n" RESET);
}
void printPasienTableRow(User *u) {
    printf("| %-3d | %-20s | %-20s |\n", u->id, u->username, u->riwayat_penyakit);
}

void printDokterTableHeader() {
    printf(BLUE BOLD "+-----+----------------------+\n" RESET);
    printf(BLUE BOLD "| ID  | Nama                 |\n" RESET);
    printf(BLUE BOLD "+-----+----------------------+\n" RESET);
}
void printDokterTableRow(User *u) {
    printf("| %-3d | %-20s |\n", u->id, u->username);
}



void cariUser(UserList *dataBaseUser, User *current_user, boolean *isLogin) {
    if (!(*isLogin)) {
        printf(RED "Login sebagai Manager terlebih dahulu!\n\n" RESET);
        return;
    }

    if (current_user->role == ROLE_MANAGER) {
        printf(CYAN "Cari berdasarkan?\n" RESET);
        printf(GRAY "1. ID\n2. Nama\n" RESET);
        printf(GRAY ">> Pilihan: " RESET);

        int pilihan;
        scanf("%d", &pilihan);

        User *u;
        switch (pilihan) {
            case 1: {
                int nomor_id;
                printf(GRAY "\n>> Masukkan nomor ID user: " RESET);
                scanf("%d", &nomor_id);

                u = findUserByID(dataBaseUser, nomor_id);
                if (u == NULL) {
                    printf(RED "Tidak ditemukan pengguna dengan ID %d\n\n" RESET, nomor_id);
                } else {
                    printf(GREEN "\nMenampilkan pengguna dengan nomor ID %d...\n" RESET, nomor_id);
                    printUserTableHeader();
                    printUserTableRow(u);
                    printf(BLUE BOLD "+-----+----------------------+-----------+----------------------+\n\n" RESET);
                }
                break;
            }
            case 2: {
                char username[100];
                printf(GRAY "\n>> Masukkan nama user: " RESET);
                scanf("%s", username);

                u = findUser(dataBaseUser, username);
                if (u == NULL) {
                    printf(RED "Tidak ditemukan pengguna dengan nama %s\n\n" RESET, username);
                } else {
                    printf(GREEN "\nMenampilkan pengguna dengan username %s...\n" RESET, username);
                    printUserTableHeader();
                    printUserTableRow(u);
                    printf(BLUE BOLD "+-----+----------------------+-----------+----------------------+\n\n" RESET);
                }
                break;
            }
            default:
                printf(RED "Pilihan tidak valid!\n\n" RESET);
                break;
        }
    } else {
        printf(RED "Anda bukan manager! Tidak bisa cari user!\n\n" RESET);
    }
}

void cariPasien(UserList *dataBaseUser, User *current_user, boolean *isLogin) {
    if (!(*isLogin)) {
        printf(RED "Login sebagai Manager terlebih dahulu!\n\n" RESET);
        return;
    }

    if (current_user->role == ROLE_MANAGER) {
        printf(CYAN "Cari berdasarkan?\n" RESET);
        printf(GRAY "1. ID\n2. Nama\n3. Penyakit\n" RESET);
        printf(GRAY ">> Pilihan: " RESET);

        int pilihan;
        scanf("%d", &pilihan);

        User *u;

        switch (pilihan) {
            case 1: {
                int nomor_id;
                printf(GRAY "\n>> Masukkan nomor ID user: " RESET);
                scanf("%d", &nomor_id);

                u = findUserByID(dataBaseUser, nomor_id);
                if (u == NULL) {
                    printf(RED "Tidak ditemukan pasien dengan ID %d\n\n" RESET, nomor_id);
                } else {
                    if (u->role == ROLE_PASIEN) {
                        printf(GREEN "\nMenampilkan pasien dengan nomor ID %d...\n" RESET, nomor_id);
                        printPasienTableHeader();
                        printPasienTableRow(u);
                        printf(BLUE BOLD "+-----+----------------------+----------------------+\n\n" RESET);
                    } else {
                        printf(RED "Tidak ada pasien dengan ID %d\n\n" RESET, nomor_id);
                    }
                }
                break;
            }
            case 2: {
                char username[100];
                printf(GRAY "\n>> Masukkan nama user: " RESET);
                scanf("%s", username);

                u = findUser(dataBaseUser, username);
                if (u == NULL) {
                    printf(RED "Tidak ditemukan pasien dengan nama %s\n\n" RESET, username);
                } else {
                    if (u->role == ROLE_PASIEN) {
                        printf(GREEN "\nMenampilkan pasien dengan username %s...\n" RESET, username);
                        printPasienTableHeader();
                        printPasienTableRow(u);
                        printf(BLUE BOLD "+-----+----------------------+----------------------+\n\n" RESET);
                    } else {
                        printf(RED "Tidak ada pasien dengan nama %s\n\n" RESET, username);
                    }
                }
                break;
            }
            case 3: { // cari berdasarkan penyakit
                char penyakit[100];
                printf(GRAY "\n>> Masukkan nama penyakit: " RESET);
                scanf("%s", penyakit);

                printf(CYAN "Urutkan berdasarkan?\n" RESET);
                printf(GRAY "1. ID\n2. Nama\n" RESET);
                printf(GRAY ">> Pilihan: " RESET);

                int pil, urut;
                scanf("%d", &pil);
                boolean found = FALSE;
                switch (pil) {
                    case 1:
                        printf(CYAN "Urutkan sort ID?\n" RESET);
                        printf(GRAY "1. ASC\n2. DESC\n" RESET);
                        printf(GRAY ">> Pilihan: " RESET);

                        scanf("%d", &urut);
                        switch (urut) {
                            case 1:
                                printf(GREEN "\nMenampilkan pasien dengan penyakit %s dengan ID terurut ascendant...\n" RESET, penyakit);
                                printPasienTableHeader();
                                for (int i = 0; i < dataBaseUser->Neff; i++) {
                                    if (dataBaseUser->data[i].role == ROLE_PASIEN && strcmp(dataBaseUser->data[i].riwayat_penyakit, penyakit) == 0) {
                                        found = TRUE;
                                        printPasienTableRow(&dataBaseUser->data[i]);
                                    }
                                }
                                printf(BLUE BOLD "+-----+----------------------+----------------------+\n" RESET);
                                if (!found) {
                                    printf(RED "Tidak ada pasien dengan riwayat penyakit %s\n\n" RESET, penyakit);
                                }
                                break;
                            case 2:
                                printf(GREEN "\nMenampilkan pasien dengan penyakit %s dengan ID terurut descendant...\n" RESET, penyakit);
                                printPasienTableHeader();
                                for (int i = dataBaseUser->Neff - 1; i >= 0; i--) {
                                    if (dataBaseUser->data[i].role == ROLE_PASIEN && strcmp(dataBaseUser->data[i].riwayat_penyakit, penyakit) == 0) {
                                        found = TRUE;
                                        printPasienTableRow(&dataBaseUser->data[i]);
                                    }
                                }
                                printf(BLUE BOLD "+-----+----------------------+----------------------+\n" RESET);
                                if (!found) {
                                    printf(RED "Tidak ada pasien dengan riwayat penyakit %s\n\n" RESET, penyakit);
                                }
                                break;
                            default:
                                printf(RED "Pilihan tidak valid!\n\n" RESET);
                                break;
                        }
                        break;
                    case 2:
                        printf(CYAN "Urutkan sort Nama?\n" RESET);
                        printf(GRAY "1. ASC (A-Z)\n2. DESC (Z-A)\n" RESET);
                        printf(GRAY ">> Pilihan: " RESET);

                        scanf("%d", &urut);

                        UserList temp;
                        copyList(*dataBaseUser, &temp);
                        switch (urut) {
                            case 1:
                                sortListByUsername(&temp, TRUE);
                                printf(GREEN "\nMenampilkan pasien dengan penyakit %s dengan Nama terurut ascendant...\n" RESET, penyakit);
                                printPasienTableHeader();
                                for (int i = 0; i < temp.Neff; i++) {
                                    if (temp.data[i].role == ROLE_PASIEN && strcmp(temp.data[i].riwayat_penyakit, penyakit) == 0) {
                                        found = TRUE;
                                        printPasienTableRow(&temp.data[i]);
                                    }
                                }
                                printf(BLUE BOLD "+-----+----------------------+----------------------+\n" RESET);
                                if (!found) {
                                    printf(RED "Tidak ada pasien dengan riwayat penyakit %s\n\n" RESET, penyakit);
                                }
                                break;
                            case 2:
                                sortListByUsername(&temp, FALSE);
                                printf(GREEN "\nMenampilkan pasien dengan penyakit %s dengan Nama terurut descendant...\n" RESET, penyakit);
                                printPasienTableHeader();
                                for (int i = 0; i < temp.Neff; i++) {
                                    if (temp.data[i].role == ROLE_PASIEN && strcmp(temp.data[i].riwayat_penyakit, penyakit) == 0) {
                                        found = TRUE;
                                        printPasienTableRow(&temp.data[i]);
                                    }
                                }
                                printf(BLUE BOLD "+-----+----------------------+----------------------+\n" RESET);
                                if (!found) {
                                    printf(RED "Tidak ada pasien dengan riwayat penyakit %s\n\n" RESET, penyakit);
                                }
                                break;
                            default:
                                printf(RED "Pilihan tidak valid!\n\n" RESET);
                                break;
                        }
                        break;
                    default:
                        printf(RED "Pilihan tidak valid!\n\n" RESET);
                        break;
                }
                break;
            }
            default:
                printf(RED "Pilihan tidak valid!\n\n" RESET);
                break;
        }

    } else {
        printf(RED "Anda bukan manager! Tidak bisa cari pasien!\n\n" RESET);
    }
}

void cariDokter(UserList *dataBaseUser, User *current_user, boolean *isLogin) {
    if (!(*isLogin)) {
        printf(RED "Login sebagai Manager terlebih dahulu!\n\n" RESET);
        return;
    }

    if (current_user->role == ROLE_MANAGER) {
        printf(CYAN "Cari berdasarkan?\n" RESET);
        printf(GRAY "1. ID\n2. Nama\n" RESET);
        printf(GRAY ">> Pilihan: " RESET);

        int pilihan;
        scanf("%d", &pilihan);

        User *u;
        switch (pilihan) {
            case 1: {
                int nomor_id;
                printf(GRAY "\n>> Masukkan nomor ID user: " RESET);
                scanf("%d", &nomor_id);

                u = findUserByID(dataBaseUser, nomor_id);
                if (u == NULL) {
                    printf(RED "Tidak ditemukan dokter dengan ID %d\n\n" RESET, nomor_id);
                } else {
                    if (u->role == ROLE_DOKTER) {
                        printf(GREEN "\nMenampilkan dokter dengan nomor ID %d...\n" RESET, nomor_id);
                        printDokterTableHeader();
                        printDokterTableRow(u);
                        printf(BLUE BOLD "+-----+----------------------+\n\n" RESET);
                    } else {
                        printf(RED "Tidak ditemukan dokter dengan ID %d\n\n" RESET, nomor_id);
                    }
                }
                break;
            }
            case 2: {
                char username[100];
                printf(GRAY "\n>> Masukkan nama user: " RESET);
                scanf("%s", username);

                u = findUser(dataBaseUser, username);
                if (u == NULL) {
                    printf(RED "Tidak ditemukan dokter dengan nama %s\n\n" RESET, username);
                } else {
                    if (u->role == ROLE_DOKTER) {
                        printf(GREEN "\nMenampilkan dokter dengan username %s...\n" RESET, username);
                        printDokterTableHeader();
                        printDokterTableRow(u);
                        printf(BLUE BOLD "+-----+----------------------+\n\n" RESET);
                    } else {
                        printf(RED "Tidak ditemukan dokter dengan nama %s\n\n" RESET, username);
                    }
                }
                break;
            }
            default:
                printf(RED "Pilihan tidak valid!\n\n" RESET);
                break;
        }
    } else {
        printf(RED "Anda bukan manager! Tidak bisa cari dokter!\n\n" RESET);
    }
}