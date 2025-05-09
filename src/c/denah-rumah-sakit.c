#include <stdio.h>
#include <string.h>
#include "../header/user.h"

void denahRumahSakit(Matrix M) {
    printf("== Denah Rumah Sakit ==\n\n");

    // Header kolom
    printf("    ");
    for (int col = 0; col < M.cols; col++) {
        printf("     %d     ", col + 1);
    }
    printf("\n");

    // Garis atas
    printf("   ");
    for (int col = 0; col < M.cols; col++) {
        printf("-----------");
    }
    printf("-\n");

    for (int row = 0; row < M.rows; row++) {
        printf(" %c |", 'A' + row);
        for (int col = 0; col < M.cols; col++) {
            printf("   %c%d     |", 'A' + row, col + 1);
        }
        printf("\n");

        // Garis bawah tiap baris
        printf("   ");
        for (int col = 0; col < M.cols; col++) {
            printf("-----------");
        }
        printf("-\n");
    }
}