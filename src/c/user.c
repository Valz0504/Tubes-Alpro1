#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../header/user.h"

#define true 1
#define false 0

void CreateUser(UserList *l, User *u, char name[], char pass[], Role role) {
    u->id = l->Neff + 1;
    strcpy(u->username, name);
    strcpy(u->password, pass);
    u->role = role;
    strcpy(u->riwayat_penyakit, "-");
    u->suhu_tubuh = 0.0;
    u->tekanan_darah_sistolik = -1;
    u->tekanan_darah_diastolik = -1;
    u->detak_jantung = -1;
    u->saturasi_oksigen = 0.0;
    u->kadar_gula_darah = -1;
    u->berat_badan = 0.0;
    u->tinggi_badan = -1;
    u->kadar_kolesterol = -1;
    u->kadar_kolesterol_Ldl = -1;
    u->trombosit = -1;
}

void CreateListDin(UserList *l, int capacity) {
    l->Neff = 0;
    l->capacity = capacity;
    l->data = (User*) malloc(capacity*sizeof(User));
}

void dealocateListDin(UserList *l) {
    free(l->data);
    l->Neff = 0;
    l->capacity = 0;
}

void expandList(UserList *l, int num) {
    l->capacity *= num;
    l->data = (User*) realloc(l->data, (l->capacity)*sizeof(User));
}

void copyList(UserList lIn, UserList *lOut) {
    CreateListDin(lOut, lIn.capacity);
    lOut->Neff = lIn.Neff;
    for (int i = 0; i < lIn.Neff; i++) {
        lOut->data[i] = lIn.data[i];
    }
}

void sortListByUsername(UserList *l, boolean asc) {
    for (int i = 0; i < l->Neff; i++) {
        for (int j = 0; j < l->Neff-i-1; j++) {
            boolean kondisi;
            if (asc) {
                kondisi = strcmp(l->data[j].username, l->data[j+1].username) > 0;
            } else {
                kondisi = strcmp(l->data[j].username, l->data[j+1].username) < 0;
            }

            if (kondisi) {
                User temp = l->data[j];
                l->data[j] = l->data[j + 1];
                l->data[j + 1] = temp;
            }
        }
    }
}

User* findUser(UserList *l, char username[]) {
    for (int i = 0; i < l->Neff; i++) {
        if (strcmp(l->data[i].username, username) == 0) {
            return &l->data[i];
        }
    }
    return NULL;
}
// User* findUserByID(UserList *l, int id) {
//     int left = 0, right = l->Neff;
//     while (left <= right) {
//         int mid = (left + right) / 2;
//         if (id > l->data[mid].id) {
//             left = mid + 1;
//         } else if (id < l->data[mid].id) {
//             right = mid - 1;
//         } else {
//             return &l->data[mid];
//         }
//     }
//     return NULL;
// }

User* findUserByID(UserList *l, int id) {
    int left = 0, right = l->Neff - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (id > l->data[mid].id) {
            left = mid + 1;
        } else if (id < l->data[mid].id) {
            right = mid - 1;
        } else {
            return &l->data[mid];
        }
    }
    return NULL;
}


boolean isUsernameExist(UserList l, char username[]) {
    for (int i = 0; i < l.Neff; i++) {
        if (strcmp(l.data[i].username, username) == 0) {
            return true;
        }
    }
    return false;
}

void AddUser(UserList *l, User u) {
    if (l->Neff == l->capacity) {
        expandList(l, 2);
    }
    l->data[l->Neff] = u;
    l->Neff += 1;
}

char* roleToStr(Role role) {
    switch (role) {
        case ROLE_PASIEN: return "Pasien";
        case ROLE_DOKTER: return "Dokter";
        case ROLE_MANAGER: return "Manager";
    }
    return "Unknown";
}

void toLower(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] += 32;
        }
    }
}

void insertLast(Inventory *inventory, int id) {
    inventory->obat[inventory->jumlahObat] = id;
    inventory->jumlahObat += 1;
}

void deleteAt(Inventory *inventory, int *id, int idx) {
    *id = inventory->obat[idx];
    for (int i = idx; i < inventory->jumlahObat -1; i++) {
        inventory->obat[i] = inventory->obat[i+1];
    }
    inventory->jumlahObat -= 1;
}

// Tambahan untuk config
void sortUserListByID(UserList *l) {
    for (int i = 0; i < l->Neff - 1; i++) {
        for (int j = i + 1; j < l->Neff; j++) {
            if (l->data[i].id > l->data[j].id) {
                User temp = l->data[i];
                l->data[i] = l->data[j];
                l->data[j] = temp;
            }
        }
    }
}