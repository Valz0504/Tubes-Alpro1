#include <stdio.h>
#include <stdlib.h>
#include "../header/map.h"

void initObatPenyakitList(Obat_PenyakitList *list) {
    for (int i = 0; i < CAPACITY; i++) {
        list->buffer[i].idPenyakit = -1;
        list->buffer[i].jumlahObat = 0;
        list->buffer[i].urutanObat = malloc(CAPACITY * sizeof(int));
    }
}

int getMapIndexByPenyakit(Obat_PenyakitList *list, int idPenyakit) {
    for (int i = 0; i < list->length; i++) {
        if (list->buffer[i].idPenyakit == idPenyakit) return i;
    }
    return -1;
}
