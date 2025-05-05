#ifndef LOAD_DATA_H
#define LOAD_DATA_H

#include "user.h"
#include "penyakit.h"

void loadDataUser(const char *filename, UserList *list);
void loadDataPenyakit(const char *filename, PenyakitList *list);
void loadDataObat(const char *filename, Obat *obatList, int *jumlahObat);
void loadDataObatPenyakit(const char *filename, Obat_Penyakit *relasi, int *jumlahRelasi);

#endif