#ifndef MAP_H
#define MAP_H

#include "boolean.h"
#include "queue.h"

#define CAPACITY 100
#define VAL_UNDEF -1

typedef struct {
    int id_penyakit;
    int *urutan_obat;
    int jumlah_obat;
} MapEntryList;

typedef struct {
    MapEntryList buffer[CAPACITY];
    int length;
} Obat_PenyakitList;

void initObatPenyakitList(Obat_PenyakitList *list);
int getMapIndexByPenyakit(Obat_PenyakitList *list, int idPenyakit);

#endif