#ifndef LOAD_DATA_H
#define LOAD_DATA_H

#include "header/user.h"
#include "header/penyakit.h"

void loadDataUser(const char *filename, UserList *list);
void loadDataPenyakit(const char *filename, PenyakitList *list);
void loadDataObat(const char *filename, Obat *obatList);
void loadDataObatPenyakit(const char *filename, Obat_Penyakit *relasi);
void loadDataConfig();

#endif