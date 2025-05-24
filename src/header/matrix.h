#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>
#include "boolean.h"
#include "queue.h"

#define MAX_ROWS 30
#define MAX_COLS 30

typedef struct {
    char nama_dokter[100];
    Queue antrian;
} Ruangan;

typedef struct
{
  Ruangan data[MAX_ROWS][MAX_COLS];
  int rows;
  int cols;
  int kapasitasRuangan;
  int kapasitasLuar;
} Matrix;

void CreateMatrix(int rows, int cols, int kapasitas, Matrix *M);
boolean isRuanganKosong(Ruangan r);
boolean getPosisiRuangan(Matrix *denah, char ruang[], int *row, int *col);
boolean isDokterSudahAssign(Matrix *denah, char nama_dokter[]);
void getRuanganDokter(Matrix *denah, char nama_dokter[], char *ruangan);

#endif