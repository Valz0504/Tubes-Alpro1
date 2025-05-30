#include "../header/set.h"

void initSet(Set *set, int capacity) {
    set->uniqueUsername = (char**) malloc(sizeof(char*) * capacity);
    set->size = 0;
    set->capacity = capacity;

}

boolean isUsernameUnique(Set s, char name[]) {
    for (int i = 0; i < s.size; i++) {
        if (strcmp(s.uniqueUsername[i], name) == 0) {
            return FALSE;
        }
    }
    return TRUE;
}

void insertSet(Set *s, char name[]) {
    if (s->size == s->capacity) {
        s->capacity *= 2;
        s->uniqueUsername = (char **) realloc(s->uniqueUsername, sizeof(char*) * s->capacity);
    }
    s->uniqueUsername[s->size] = malloc(strlen(name) + 1);
    strcpy(s->uniqueUsername[s->size], name);
    s->size += 1;
}