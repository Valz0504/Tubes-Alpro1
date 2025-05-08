/* File : set.h */
/* Deskripsi : Berisi ADT Set */

#ifndef SET_H
#define SET_H

#include <string.h>
#include <stdlib.h>
#include "boolean.h"

/* --- Struct Set --- */
typedef struct 
{
    char **unique_username;
    int size;
    int capacity;
} Set;

void initSet(Set *set, int capacity);
boolean isUsernameUnique(Set s, char name[]); /* DeNis == denis */
void insertSet(Set *s, char name[]);

#endif