#include <stdio.h>
#include <string.h>
#include "../header/matrix.h"

void CreateMatrix(int rows, int cols, int kapasitas, Matrix *M) {
    M->rows = rows;
    M->cols = cols;
    M->kapasitasRuangan = kapasitas;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            M->data[i][j].serving = FALSE;
            strcpy(M->data[i][j].namaDokter, "");
            initQueue(&(M->data[i][j].antrian));
        }
    }
}

boolean isRuanganKosong(Ruangan r) {
    return strcmp(r.namaDokter, "") == 0;
}

boolean getPosisiRuangan(Matrix *denah, char ruang[], int *row, int *col) {
    if (strlen(ruang) < 2 || strlen(ruang) > 3) return FALSE;

    char first_char = ruang[0];
    if (first_char < 'A' || first_char > 'Z') return FALSE;

    *row = first_char - 'A'; 

    int col_temp = atoi(&ruang[1]);
    if (col_temp < 1 || col_temp > denah->cols) return FALSE;

    *col = col_temp - 1;

    return TRUE;
}


boolean isDokterSudahAssign(Matrix *denah, char namaDokter[]) {
    for (int i = 0; i < denah->rows; i++) {
        for (int j = 0; j < denah->cols; j++) {
            if (strcmp(denah->data[i][j].namaDokter, namaDokter) == 0) {
                return TRUE;
            }
        }
    }
    return FALSE;
}

void getRuanganDokter(Matrix *denah, char namaDokter[], char *ruangan) {
    for (int i = 0; i < denah->rows; i++) {
        for (int j = 0; j < denah->cols; j++) {
            if (strcmp(denah->data[i][j].namaDokter, namaDokter) == 0) {
                ruangan[0] = 'A' + i;
                sprintf(ruangan + 1, "%d", j + 1);
                return;
            }
        }
    }
    ruangan[0] = '\0';
}