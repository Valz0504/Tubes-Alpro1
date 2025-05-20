#include <stdio.h>
#include <string.h>
#include "../header/matrix.h"
#include "../header/queue.h"

void lihatRuangan(Matrix denah) {
    char koderuangan[5];
    int row, col;

    scanf("%s", koderuangan);

    if (!getPosisiRuangan(&denah, koderuangan, &row, &col) || row >= denah.rows || col >= denah.cols) {
        printf("Ruangan tidak ditemukan\n");
        return;
    }

    printf("\n--- Detail Ruangan %s ---\n", koderuangan);
    printf("Kapasitas : %d\n", denah.kapasitasRuangan);
    printf("Dokter    : %s\n", strlen(denah.data[row][col].nama_dokter) > 0 ? denah.data[row][col].nama_dokter : "-");
    
    printf("Pasien di dalam ruangan:\n");
    if (denah.data[row][col].antrian.head == NULL) {
        printf("Tidak ada pasien di dalam ruangan saat ini.\n");
    } 
    else {
        int no = 1;
        Node *curr = denah.data[row][col].antrian.head;
        while (curr != NULL) {
            printf("%d. %d\n", no++, curr->info);
            curr = curr->next;
        }
    }
}