#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "../header/user.h"

int folder_exist(const char *folderPath) {//cari keberadaan folder
    struct stat st;
    return (stat(folderPath, &st) == 0 && S_ISDIR(st.st_mode));
}

int file_exist(const char *folderPath) {//cari keberadaan file
    DIR *dir = opendir(folderPath);
    if (!dir) {
        return 0;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        closedir(dir);
        return 1;
    }

    closedir(dir);
    return 0;
}
int folder(const char *folderName){//membuat folder
    if (mkdir(folderName, 0777) == 0) {
        return 0;
    } 
    else {
        perror(RED "Gagal membuat folder" RESET);
        return -1;
    }
}
void FileUser(const char *filePath, UserList *users){// membuat/overwrite file user
    FILE *fp = fopen(filePath, "w");
    if (!fp) {
        printf(RED "Gagal membuat file di path: %s\n" RESET, filePath);
        return;
    }
    char peran[100];
    fprintf(fp,
        "id,username,password,role,riwayat_penyakit,suhu_tubuh,"
        "tekanan_darah_sistolik,tekanan_darah_diastolik,detak_jantung,"
        "saturasi_oksigen,kadar_gula_darah,berat_badan,tinggi_badan,"
        "kadar_kolesterol,kadar_kolesterol_ldl,trombosit\n");
    for (int i = 0; i < users->Neff; i++) {
        User u = users->data[i];
        if (u.role == 0) {
            strcpy(peran, "pasien");
            fprintf(fp,
                "%d;%s;%s;%s;%d;%s;%.1f;%d;%d;%d;%.1f;%d;%.1f;%d;%d;%d;%d\n",
                u.id, u.username, u.password, peran, u.aura, u.riwayatPenyakit,
                u.suhuTubuh, u.tekananDarahSistolik, u.tekananDarahDiastolik,
                u.detakJantung, u.saturasiOksigen, u.kadarGulaDarah,
                u.beratBadan, u.tinggiBadan, u.kadarKolesterol,
                u.trombosit, u.nyawa
            );
        } 
        else if (u.role == 1) {
            strcpy(peran, "dokter");
            fprintf(fp,
                "%d;%s;%s;%s;%d;;;;;;;;;\n",
                u.id, u.username, u.password, peran, u.aura
            );
        } 
        else if (u.role == 2) {
            strcpy(peran, "manager");
            fprintf(fp,
                "%d;%s;%s;%s;;;;;;;;;;\n",
                u.id, u.username, u.password, peran
            );
        }

    }
    fclose(fp);
}
void FileObat(const char *filePath, ObatList *obat){// membuat/overwrite file obat
    FILE *fp = fopen(filePath, "w");
    if (fp == NULL) {
        printf(RED "Gagal membuat file di path: %s\n" RESET, filePath);
        return;
    }
    fprintf(fp,
        "obat_id,nama_obat\n");
    for(int i = 0; i < obat->Neff; i++){
        Obat o = obat->data[i];
        fprintf(fp, "%d;%s\n", o.id, o.nama);
    }
    fclose(fp);
}
void FilePenyakit(const char *filePath, PenyakitList *sakit){// membuat/overwrite file penyakit
    FILE *fp = fopen(filePath, "w");
    if (fp == NULL) {
        printf(RED "Gagal membuat file di path: %s\n" RESET, filePath);
        return;
    }
    fprintf(fp, "id,nama,suhuTubuhMin,suhuTubuhMax,tekananSistolikMin,tekananSistolikMax,"
        "tekananDiastolikMin,tekananDiastolikMax,detakJantungMin,detakJantungMax,saturasiMin,saturasiMax,kadarGulaMin,"
        "kadarGulaMax,beratBadanMin,beratBadanMax,tinggiBadanMin,tinggiBadanMax,kolesterolMin,"
        "kolesterolMax,trombositMin,trombositMax\n");
    for(int i = 0; i < sakit->Neff; i++){
        Penyakit S = sakit->data[i];
        fprintf(fp, "%d;%s;%f;%f;%d;%d;%d;%d;%d;%d;%f;%f;%d;%d;%f;%f;%d;%d;%d;%d;%d;%d\n",
             S.id, S.nama, S.suhuTubuhMin, S.suhuTubuhMax, S.tekananSistolikMin
            , S.tekananSistolikMax, S.tekananDiastolikMin, S.tekananDiastolikMax
            , S.detakJantungMin, S.detakJantungMax, S.saturasiMin, S.saturasiMax
            , S.kadarGulaMin, S.kadarGulaMax, S.beratBadanMin, S.beratBadanMax
            , S.tinggiBadanMin, S.tinggiBadanMax, S.kolesterolMin, S.kolesterolMax
            , S.trombositMin, S.trombositMax);
    }
    fclose(fp);
}
void FileObat_Penyakit(const char *filePath, Obat_PenyakitList *obat_penyakit) {
    FILE *fp = fopen(filePath, "w");
    if (fp == NULL) {
        printf(RED "Gagal membuat file di path: %s\n" RESET, filePath);
        return;
    }

    fprintf(fp, "idObat;idPenyakit;urutanMinum\n");

    for (int i = 0; i < obat_penyakit->length; i++) {
        MapEntryList *entry = &obat_penyakit->buffer[i];
        for (int j = 0; j < entry->jumlahObat; j++) {
            int idObat = entry->urutanObat[j];
            int idPenyakit = entry->idPenyakit;
            int urutanMinum = j + 1;
            fprintf(fp, "%d;%d;%d\n", idObat, idPenyakit, urutanMinum);
        }
    }

    fclose(fp);
}

void FileConfig(const char *filePath, Matrix *Hospital, UserList *dataBaseUser){ // membuat/overwrite file config
    FILE *fp = fopen(filePath, "w");
    if (fp == NULL) {
        printf(RED "Gagal membuat file di path: %s\n" RESET, filePath);
        return;
    }
    int dokter;
    fprintf(fp, "%d %d\n", Hospital->rows, Hospital->cols);
    fprintf(fp, "%d %d\n", Hospital->kapasitasRuangan, Hospital->kapasitasLuar);
    for(int i = 0; i < Hospital->rows; i++){
        for(int j = 0; j < Hospital->cols ; j++){
            // Tulis dokter
            User *I = findUser(dataBaseUser, Hospital->data[i][j].namaDokter);
            if(I != NULL){
                fprintf(fp, "%d ", I->id);
                dokter = I->id;
            } else {
                fprintf(fp, "%d ", 0);
                dokter = 0;
            }
            // Tulis antrian pasien (jika ada dokter)
            if(dokter != 0){
                Node *A = Hospital->data[i][j].antrian.head;
                while(A != NULL){
                    fprintf(fp, "%d ", A->info);
                    A = A->next;
                }
            }
            fprintf(fp, "\n");
        }
    }

    // save state inventory
    int x = 0;
    for (int i = 0; i < dataBaseUser->Neff; i++) {
        if (dataBaseUser->data[i].inventory.jumlahObat > 0) x++;
    }

    fprintf(fp, "%d\n", x);
    for (int i = 0; i < dataBaseUser->Neff; i++) {
        if (dataBaseUser->data[i].inventory.jumlahObat > 0) {
            fprintf(fp, "%d ", dataBaseUser->data[i].id);

            for (int j = 0; j < dataBaseUser->data[i].inventory.jumlahObat; j++) {
                fprintf(fp, "%d ", dataBaseUser->data[i].inventory.obat[j]);
            }
            fprintf(fp, "\n");
        }
    }

    // save state perut
    int y = 0;
    for (int i = 0; i < dataBaseUser->Neff; i++) {
        if (dataBaseUser->data[i].perut.length > 0) y++;
    }

    fprintf(fp, "%d\n", y);
    for (int i = 0; i < dataBaseUser->Neff; i++) {
        if (dataBaseUser->data[i].perut.length > 0) {
            fprintf(fp, "%d ", dataBaseUser->data[i].id);
            int val;
            while (dataBaseUser->data[i].perut.length > 0) {
                pop(&dataBaseUser->data[i].perut, &val);
                fprintf(fp, "%d ", val);
            }
            fprintf(fp, "\n");
        }
    }

    fclose(fp);
}


void SAVE(UserList *user1, ObatList *Obat, PenyakitList *sakit, Obat_PenyakitList *obat_penyakit, Matrix *Hospital){
    char nama_folder[50];
    char pathUser[256];
    char base[50] = "./data";
    char FullFolder[256];
    char pathObat[256];
    char pathPenyakit[256];
    char pathObatPenyakit[256];
    char pathConfig[256];
    printf(CYAN BOLD "Masukkan nama folder: " RESET);
    scanf("%s", nama_folder);
    snprintf(FullFolder, sizeof(FullFolder), "%s/%s", base, nama_folder);
    snprintf(pathUser, sizeof(pathUser), "%s/%s/user.csv", base, nama_folder); // buat path filenya
    snprintf(pathObat, sizeof(pathObat), "%s/%s/obat.csv", base, nama_folder);
    snprintf(pathPenyakit, sizeof(pathPenyakit), "%s/%s/penyakit.csv", base, nama_folder);
    snprintf(pathObatPenyakit, sizeof(pathObatPenyakit), "%s/%s/obat_penyakit.csv", base, nama_folder);
    snprintf(pathConfig, sizeof(pathConfig), "%s/%s/config.txt", base, nama_folder);
    
    printf(CYAN "\nSaving...\n\n" RESET);

    if(folder_exist(FullFolder) == 1 && file_exist(FullFolder) == 1){
        printf(YELLOW "Folder sudah ada, file lama akan di-overwrite.\n" RESET);
        printf(GRAY "Membuat folder data/%s (sudah ada)\n" RESET, nama_folder);
        FileUser(pathUser, user1);
        FileConfig(pathConfig, Hospital, user1);
        printf(GREEN BOLD"Berhasil menyimpan data di folder " CYAN "data/%s\n\n" RESET, nama_folder);
    }
    else if (folder_exist(FullFolder) == 1 && file_exist(FullFolder) == 0){
        printf(GRAY "Membuat folder data/%s (sudah ada)\n" RESET, nama_folder);
        FileUser(pathUser, user1);
        FileObat(pathObat, Obat);
        FilePenyakit(pathPenyakit, sakit);
        FileObat_Penyakit(pathObatPenyakit, obat_penyakit);
        FileConfig(pathConfig, Hospital, user1);
        printf(GREEN BOLD"Berhasil menyimpan data di folder " CYAN "data/%s\n\n" RESET, nama_folder);
    }
    else{
        printf(GRAY "Membuat folder data/%s\n" RESET, nama_folder);
        folder(FullFolder);
        FileUser(pathUser, user1);
        FileObat(pathObat, Obat);
        FilePenyakit(pathPenyakit, sakit);
        FileObat_Penyakit(pathObatPenyakit, obat_penyakit);
        FileConfig(pathConfig, Hospital, user1);
        printf(GREEN BOLD"Berhasil menyimpan data di folder " CYAN "data/%s\n\n" RESET, nama_folder);
    }
}