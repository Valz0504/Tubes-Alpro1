#ifndef MAP_H
#define MAP_H

#define MAX_MAP_SIZE 100
#define KEY_MAX_LENGTH 100
#define MAX_OBAT_PER_PENYAKIT 10
#define MAX_OBAT_NAME_LENGTH 100

typedef struct {
    char key[100]; // nama penyakit
    char obat[MAX_OBAT_PER_PENYAKIT][MAX_OBAT_NAME_LENGTH]; // daftar obat
    int jumlah_obat;
} MapEntry;

typedef struct {
    MapEntry entries[MAX_MAP_SIZE];
    int size;
} Map;

void createMap(Map *m);
void insertObat(Map *m, const char *penyakit, const char *obat);
int getObatForPenyakit(Map *m, const char *penyakit, char result[][MAX_OBAT_NAME_LENGTH], int *jumlah);
int isKeyInMap(Map *m, const char *key);

#endif
