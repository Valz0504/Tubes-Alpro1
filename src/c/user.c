#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../header/user.h"

#define true 1
#define false 0

void CreateUser(UserList *l, User *u, char name[], char pass[], Role role) {
    u->id = l->currMaxId + 1;
    strcpy(u->username, name);
    strcpy(u->password, pass);
    u->aura = 0;
    u->role = role;
    strcpy(u->riwayatPenyakit, "-");
    u->suhuTubuh = 0.0;
    u->tekananDarahSistolik = -1;
    u->tekananDarahDiastolik = -1;
    u->detakJantung = -1;
    u->saturasiOksigen = 0.0;
    u->kadarGulaDarah = -1;
    u->beratBadan = 0.0;
    u->tinggiBadan = -1;
    u->kadarKolesterol = -1;
    u->trombosit = -1;
    u->nyawa = 3;
    initStack(&u->perut);
    u->inventory.jumlahObat = 0;
    l->currMaxId++;
}

void deleteUser(UserList *l, User *u) {
    //cari indeks user di userList dulu
    int left = 0, right = l->Neff-1;
    int idx = -1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (l->data[mid].id < u->id) {
            left = mid + 1;
        } else if (l->data[mid].id > u->id) {
            right = mid - 1;
        } else {
            idx = mid;
            break;
        }
    }

    //hilangkan usernya dari list
    for (int i = idx; i < l->Neff - 1; i++) {
        l->data[i] = l->data[i+1];
    }
    l->Neff--;
}

void CreateListDin(UserList *l, int capacity) {
    l->Neff = 0;
    l->capacity = capacity;
    l->currMaxId = 0;
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
    lOut->currMaxId = lIn.currMaxId;
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

void sortListByID(UserList *l, boolean asc) {
    for (int i = 0; i < l->Neff - 1; i++) {
        for (int j = 0; j < l->Neff - i - 1; j++) {
            boolean kondisi;
            if (asc) {
                kondisi = (l->data[j].id > l->data[j+1].id);
            } else {
                kondisi = (l->data[j].id < l->data[j+1].id);
            }

            if (kondisi) {
                User temp = l->data[j];
                l->data[j] = l->data[j + 1];
                l->data[j + 1] = temp;
            }
        }
    }
}

void sortListByAura(UserList *l, boolean asc) {
    for (int i = 0; i < l->Neff - 1; i++) {
        for (int j = 0; j < l->Neff - i - 1; j++) {
            boolean kondisi;
            if (asc) {
                kondisi = (l->data[j].aura > l->data[j+1].aura);
            } else {
                kondisi = (l->data[j].aura < l->data[j+1].aura);
            }

            if (kondisi) {
                User temp = l->data[j];
                l->data[j] = l->data[j+1];
                l->data[j+1] = temp;
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
    User *u = findUser(&l, username);
    if (u != NULL) return TRUE;
    else return FALSE;
}

void AddUser(UserList *l, User *u) {
    if (l->Neff == l->capacity) {
        expandList(l, 2);
    }
    l->data[l->Neff] = *u;
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
