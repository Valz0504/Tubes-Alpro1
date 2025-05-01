/* File : set.h */
/* Deskripsi : Berisi ADT Set */

#ifndef SET_H
#define SET_H

#include "boolean.h"

#define MAX_SET_SIZE 100

/* --- Struct Set --- */
typedef struct 
{
    char unique_username[MAX_SET_SIZE][100];
    int size;
} Set;


boolean isUsernameUnique(Set s, char name[]);
void insertSet(Set *s, char name[]);

#endif