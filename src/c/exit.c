#include <stdio.h>
#include <string.h>
#include "../header/user.h"

void EXIT(UserList *databaseuser, ObatList *DataObat, PenyakitList *Datapenyakit, Obat_PenyakitList *Data_obat_penyakit, Matrix *Hospital, boolean *run_program){
    char input[100];
    do {
        printf(CYAN "Apakah Anda mau melakukan penyimpanan file yang sudah diubah? (" GREEN "y" RESET CYAN "/" RED "n" RESET CYAN ") " RESET);
        scanf("%s", input);
        toLower(input);
        if (strcmp(input, "y") != 0 && strcmp(input, "n") != 0) {
            printf(RED "Masukan anda belum benar, coba lagi!\n\n" RESET);
        }
    } while (strcmp(input, "y") != 0 && strcmp(input, "n") != 0);

    if(strcmp(input, "y") == 0){
        printf(GREEN BOLD"Menyimpan data ke file...\n" RESET);
        SAVE(databaseuser, DataObat, Datapenyakit, Data_obat_penyakit, Hospital);
        printf(GREEN BOLD"Data berhasil disimpan. Sampai jumpa!\n\n" RESET);
        *run_program = FALSE;
        return;
    }
    printf(YELLOW "Data tidak disimpan. Sampai jumpa!\n\n" RESET);
    *run_program = FALSE;
}