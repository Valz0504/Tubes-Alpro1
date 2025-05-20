#include <stdlib.h>
#include "../header/penyakit.h"

char* getObatName(ObatList *dataObat, int id) {
    for (int i = 0; i < dataObat->Neff; i++) {
        if (dataObat->data[i].id == id) {
            return dataObat->data[i].nama;
        }
    }
    return NULL;
}
