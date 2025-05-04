#include "header/set.h"

void initSet(Set *set, int capacity) {
    set->unique_username = (char**) malloc(sizeof(char*) * capacity);
    set->size = 0;
    set->capacity = capacity;

}

boolean isUsernameUnique(Set s, char name[]) {
    for (int i = 0; i < s.size; i++) {
        if (strcmp(s.unique_username[i], name) == 0) {
            return FALSE;
        }
    }
    return TRUE;
}

void insertSet(Set *s, char name[]) {
    if (s->size == s->capacity) {
        s->capacity *= 2;
        s->unique_username = (char **) realloc(s->unique_username, sizeof(char*) * s->capacity);
    }
    s->unique_username[s->size] = malloc(strlen(name) + 1);
    strcpy(s->unique_username[s->size], name);
    s->size += 1;
}