#include <stdio.h>
#include <string.h>
#include "../header/user.h"
#include "../header/penyakit.h"
#include "../header/matrix.h"

void EXIT(UserList *databaseuser, ObatList *DataObat, PenyakitList *Datapenyakit, Obat_PenyakitList *Data_obat_penyakit, Matrix *Hospital, boolean *run_program){
    char input[100];
    do {
        printf("Apakah Anda mau melakukan penyimpanan file yang sudah diubah? (y/n) ");
        scanf("%s", input);
        toLower(input);
    } while (strcmp(input, "y") != 0 && strcmp(input, "n") != 0);
    if(strcmp(input, "y") == 0){
        SAVE(databaseuser, DataObat, Datapenyakit, Data_obat_penyakit, Hospital);
        *run_program = FALSE;
        return;
    }
    *run_program = FALSE;
}