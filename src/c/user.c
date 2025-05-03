#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "header/user.h"

#define true 1
#define false 0

void CreateUser(UserList *l, User *u, char name[], char pass[], Role role) {
    u->id = l->Neff;
    strcpy(u->username, name);
    strcpy(u->password, pass);
    u->role = role;
    strcpy(u->riwayat_penyakit, "-");
    u->suhu_tubuh = 0.0;
    u->tekanan_darah_tistolik = -1;
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
    l->capacity += num;
    l->data = (User*) realloc(l->data, (l->capacity)*sizeof(User));
}

void copyList(UserList lIn, UserList *lOut) {
    CreateListDin(lOut, lIn.capacity);
    lOut->Neff = lIn.Neff;
    for (int i = 0; i < lIn.Neff; i++) {
        lOut->data[i] = lIn.data[i];
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
        expandList(l, 1);
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
}

void SetUsername(User *u, char name[]); 
void SetPassword(User *u, char pass[]);

void SetNewPassword(UserList *l, char username[], char pass[]) {
    for (int i = 0; i < l->Neff; i++) {
        if (strcmp(l->data[i].username, username) == 0) {
            strcpy(l->data[i].password, pass);
        }
    }
}


