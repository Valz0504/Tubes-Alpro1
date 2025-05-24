#include <stdio.h>
#include <string.h>
#include "../header/user.h"

void denahRumahSakit(Matrix M) {
    printf(CYAN BOLD "== Denah Rumah Sakit ==\n\n" RESET);

    // Header kolom
    printf("   ");
    for (int col = 0; col < M.cols; col++) {
        printf(BLUE BOLD "     %d     " RESET, col + 1);
    }
    printf("\n");

    // Garis atas
    printf("   ");
    for (int col = 0; col < M.cols; col++) {
        printf(BLUE "-----------" RESET);
    }
    printf(BLUE "-\n" RESET);

    for (int row = 0; row < M.rows; row++) {
        printf(GRAY BOLD " %c " RESET "|", 'A' + row);
        for (int col = 0; col < M.cols; col++) {
            printf(GRAY "   %c%d     " RESET "|", 'A' + row, col + 1);
        }
        printf("\n");

        // Garis bawah tiap baris
        printf("   ");
        for (int col = 0; col < M.cols; col++) {
            printf(BLUE "-----------" RESET);
        }
        printf(BLUE "-\n" RESET);
    }
}