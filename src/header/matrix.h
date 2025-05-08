#ifndef MATRIX_H
#define MATRIX_H

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
} Matrix;

void CreateMatrix(int rows, int cols, Matrix *M);
void denahRumahSakit(Matrix M); //denah rumah sakit

#endif