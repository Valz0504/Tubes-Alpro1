#include <string.h>
#include <stdlib.h>
#include "../header/penyakit.h"

Obat *getObatbyId(ObatList *dataObat, int id) {
    for (int i = 0; i < dataObat->Neff; i++) {
        if (dataObat->data[i].id == id) {
            return &dataObat->data[i];
        }
    }
    return NULL;
}

int getIDPenyakit(PenyakitList *dataPenyakit, char penyakit[]) {
    for (int i = 0; i < dataPenyakit->Neff; i++) {
        if (strcmp(dataPenyakit->data[i].nama, penyakit) == 0) {
            return dataPenyakit->data[i].id;
        }
    }
    return -1;
}