/* File : set.h */
/* Deskripsi : Berisi ADT Set */

#ifndef SET_H
#define SET_H

#include "boolean.h"

/* --- Struct Set --- */
typedef struct 
{
    char unique_username[100][100];
    int size;
} Set;

boolean isUsernameUnique(Set s, char name[]); /* DeNis == denis */
void insertSet(Set *s, char name[]);

#endif