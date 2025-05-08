#include "header/matrix.h"
#include <string.h>

void CreateMatrix(int rows, int cols, Matrix *M) {
    M->rows = rows;
    M->cols = cols;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            strcpy(M->data[i][j].nama_dokter, "");
            initQueue(&(M->data[i][j].antrian));
        }
    }
}