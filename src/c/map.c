#include <stdio.h>
#include <string.h>
#include "map.h"

void createMap(Map *m) {
    m->size = 0;
}

int isKeyInMap(Map *m, const char *key) {
    for (int i = 0; i < m->size; ++i) {
        if (strcmp(m->entries[i].key, key) == 0) {
            return 1;
        }
    }
    return 0;
}

void insertObat(Map *m, const char *penyakit, const char *obat) {
    for (int i = 0; i < m->size; ++i) {
        if (strcmp(m->entries[i].key, penyakit) == 0) {
            if (m->entries[i].jumlah_obat < MAX_OBAT_PER_PENYAKIT) {
                strncpy(m->entries[i].obat[m->entries[i].jumlah_obat], obat, MAX_OBAT_NAME_LENGTH - 1);
                m->entries[i].obat[m->entries[i].jumlah_obat][MAX_OBAT_NAME_LENGTH - 1] = '\0';
                m->entries[i].jumlah_obat++;
            }
            return;
        }
    }

    if (m->size < MAX_MAP_SIZE) {
        strncpy(m->entries[m->size].key, penyakit, sizeof(m->entries[m->size].key) - 1);
        m->entries[m->size].key[sizeof(m->entries[m->size].key) - 1] = '\0';

        strncpy(m->entries[m->size].obat[0], obat, MAX_OBAT_NAME_LENGTH - 1);
        m->entries[m->size].obat[0][MAX_OBAT_NAME_LENGTH - 1] = '\0';

        m->entries[m->size].jumlah_obat = 1;
        m->size++;
    }
}

int getObatForPenyakit(Map *m, const char *penyakit, char result[][MAX_OBAT_NAME_LENGTH], int *jumlah) {
    for (int i = 0; i < m->size; ++i) {
        if (strcmp(m->entries[i].key, penyakit) == 0) {
            *jumlah = m->entries[i].jumlah_obat;
            for (int j = 0; j < *jumlah; ++j) {
                strncpy(result[j], m->entries[i].obat[j], MAX_OBAT_NAME_LENGTH - 1);
                result[j][MAX_OBAT_NAME_LENGTH - 1] = '\0';
            }
            return 1;
        }
    }
    *jumlah = 0;
    return 0;
}
