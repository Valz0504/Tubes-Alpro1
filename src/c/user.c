#include "header/user.h"
#include <string.h>
#include <stdlib.h>

#define true 1
#define false 0

User* findUser(UserList *l, char username[]) {
    for (int i = 0; i < l->Neff; i++) {
        if (strcmp(l->data[i].username, username) == 0) {
            return &l->data[i];
        }
    }
    return NULL;
}

void expandList(UserList *l, int num) {
    l->capacity += num;
    l->data = (User*) realloc(l->data, (l->capacity)*sizeof(User));
}

void AddUser(UserList *l, User u) {
    if (l->Neff == l->capacity) {
        expandList(&l, 1);
    }
    l->data[l->Neff] = u;
    l->Neff += 1;
}

boolean isUsernameExist(UserList l, char username[]) {
    for (int i = 0; i < l.Neff; i++) {
        if (strcmp(l.data[i].username, username) == 0) {
            return true;
        }
    }
    return false;
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