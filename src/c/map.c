#include <stdio.h>
#include <stdlib.h>
#include "../header/map.h"

void initObatPenyakitList(Obat_PenyakitList *list) {
    for (int i = 0; i < CAPACITY; i++) {
        list->buffer[i].id_penyakit = -1;
        list->buffer[i].jumlah_obat = 0;
        list->buffer[i].urutan_obat = malloc(CAPACITY * sizeof(int));
    }
}

int getMapIndexByPenyakit(Obat_PenyakitList *list, int idPenyakit) {
    for (int i = 0; i < list->length; i++) {
        if (list->buffer[i].id_penyakit == idPenyakit) return i;
    }
    return -1;
}
