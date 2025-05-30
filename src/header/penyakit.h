/* File : penyakit.h */
/* Deskripsi : Berisi ADT penyakit,obat,obat-penyakit */

#ifndef PENYAKIT_H
#define PENYAKIT_H

#include "stack.h"
#include "boolean.h"

typedef struct {
    int id;
    char nama[100];
    float suhuTubuhMin;
    float suhuTubuhMax;
    int tekananSistolikMin;
    int tekananSistolikMax;
    int tekananDiastolikMin;
    int tekananDiastolikMax;
    int detakJantungMin;
    int detakJantungMax;
    float saturasiMin;
    float saturasiMax;
    int kadarGulaMin;
    int kadarGulaMax;
    float beratBadanMin;
    float beratBadanMax;
    int tinggiBadanMin;
    int tinggiBadanMax;
    int kolesterolMin;
    int kolesterolMax;
    int trombositMin;
    int trombositMax;
} Penyakit;

typedef struct 
{
    Penyakit *data;
    int Neff;
    int capacity;
} PenyakitList;

typedef struct {
    int id;
    char nama[100];
} Obat;

typedef struct 
{
    Obat *data;
    int Neff;
    int capacity;
} ObatList;

typedef struct {
    int pasienId;
    int obat[100];
    int jumlahObat;
} Inventory;


Obat *getObatbyId(ObatList *dataObat, int id);
int getIDPenyakit(PenyakitList *dataPenyakit, char penyakit[]);

#endif