#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "../header/user.h"
#include "../header/penyakit.h"
#include "../header/matrix.h"

int folder_exist(const char *folderPath) {//cari keberadaan folder
    struct stat st;
    return (stat(folderPath, &st) == 0 && S_ISDIR(st.st_mode));
}

int file_exist(const char *folderPath) {//cari keberadaan file
    DIR *dir = opendir(folderPath);
    if (!dir) {
        return 0; // Gagal buka folder
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        // Lewati "." dan ".."
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        closedir(dir);
        return 1; // Ada entri selain . dan ..
    }

    closedir(dir);
    return 0; // Folder kosong
}
int folder(const char *folderName){//membuat folder
    if (mkdir(folderName, 0777) == 0) {
        return 0;
    } 
    else {
        perror("Gagal membuat folder");
        return -1;
    }
}
void FileUser(const char *filePath, UserList *users){// membuat/overwrite file user
    FILE *fp = fopen(filePath, "w");
    if (!fp) {
        printf("Gagal membuat file di path: %s\n", filePath);
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
                "%d;%s;%s;%s;%s;%.1f;%d;%d;%d;%.1f;%d;%.1f;%d;%d;%d;%d\n",
                u.id, u.username, u.password, peran, u.riwayat_penyakit,
                u.suhu_tubuh, u.tekanan_darah_sistolik, u.tekanan_darah_diastolik,
                u.detak_jantung, u.saturasi_oksigen, u.kadar_gula_darah,
                u.berat_badan, u.tinggi_badan, u.kadar_kolesterol,
                u.kadar_kolesterol_Ldl, u.trombosit
            );
        } 
        else if (u.role == 1) {
            strcpy(peran, "dokter");
            fprintf(fp,
                "%d;%s;%s;%s\n",
                u.id, u.username, u.password, peran
            );
        } 
        else if (u.role == 2) {
            strcpy(peran, "manager");
            fprintf(fp,
                "%d;%s;%s;%s\n",
                u.id, u.username, u.password, peran
            );
        }

    }
    fclose(fp);
}
void FileObat(const char *filePath, ObatList *obat){// membuat/overwrite file obat
    FILE *fp = fopen(filePath, "w");
    if (fp == NULL) {
        printf("Gagal membuat file di path: %s\n", filePath);
        return;
    }
    fprintf(fp,
        "obat_id,nama_obat\n");
    for(int i = 0; i < obat->Neff; i++){
        Obat o = obat->data[i];
        fprintf(fp, "%d;%s;\n", o.id, o.nama);
    }
    fclose(fp);
}
void FilePenyakit(const char *filePath, PenyakitList *sakit){// membuat/overwrite file penyakit
    FILE *fp = fopen(filePath, "w");
    if (fp == NULL) {
        printf("Gagal membuat file di path: %s\n", filePath);
        return;
    }
    fprintf(fp, "id,nama,suhu_tubuh_Min,suhu_tubuh_Max,tekanan_sistolik_Min,tekanan_sistolik_Max,"
        "tekanan_diastolik_Min,tekanan_diastolik_Max,detak_jantung_Min,detak_jantung_Max,saturasi_Min,saturasi_Max,kadar_gula_Min,"
        "kadar_gula_Max,berat_badan_Min,berat_badan_Max,tinggi_badan_Min,tinggi_badan_Max,kolesterol_Min,"
        "kolesterol_Max,trombosit_Min,trombosit_Max\n");
    for(int i = 0; i < sakit->Neff; i++){
        Penyakit S = sakit->data[i];
        fprintf(fp, "%d;%s;%f;%f;%d;%d;%d;%d;%d;%d;%f;%f;%d;%d;%f;%f;%d;%d;%d;%d;%d;%d\n",
             S.id, S.nama, S.suhu_tubuh_Min, S.suhu_tubuh_Max, S.tekanan_sistolik_Min
            , S.tekanan_sistolik_Max, S.tekanan_diastolik_Min, S.tekanan_diastolik_Max
            , S.detak_jantung_Min, S.detak_jantung_Max, S.saturasi_Min, S.saturasi_Max
            , S.kadar_gula_Min, S.kadar_gula_Max, S.berat_badan_Min, S.berat_badan_Max
            , S.tinggi_badan_Min, S.tinggi_badan_Max, S.kolesterol_Min, S.kolesterol_Max
            , S.trombosit_Min, S.trombosit_Max);
    }
    fclose(fp);
}
void FileObat_Penyakit(const char *filePath, Obat_PenyakitList *obat_penyakit) {
    FILE *fp = fopen(filePath, "w");
    if (fp == NULL) {
        printf("Gagal membuat file di path: %s\n", filePath);
        return;
    }

    fprintf(fp, "idObat;idPenyakit;urutanMinum\n");

    for (int i = 0; i < obat_penyakit->length; i++) {
        MapEntryList *entry = &obat_penyakit->buffer[i];
        for (int j = 0; j < entry->jumlah_obat; j++) {
            int idObat = entry->urutan_obat[j];
            int idPenyakit = entry->id_penyakit;
            int urutanMinum = j + 1;
            fprintf(fp, "%d;%d;%d\n", idObat, idPenyakit, urutanMinum);
        }
    }

    fclose(fp);
}

int JmlhInventory_ada(UserList user1, int PasienObat[][100]){
    int Adainventory = 0;
    for(int x = 0; x < user1.Neff; x++){//ngeloop pasien
        Inventory Pasien = user1.data[x].inventory;
        if(Pasien.jumlahObat != 0){
            for(int j = 0; j <= Pasien.jumlahObat; j++){
                if(j == 0){
                    PasienObat[Adainventory][j] = user1.data[x].id;
                }
                else if(j-1 < Pasien.jumlahObat){
                    PasienObat[Adainventory][j] = Pasien.obat[j-1];
                }
                else{
                    break;
                }
            }
            for(int j = Pasien.jumlahObat+1; j < 100; j++){
                PasienObat[Adainventory][j] = 0;
            }
            Adainventory++;
        }  
    }

    return Adainventory;
}
int isiRuangan(Matrix Hospital, int i, int j){
    int count = 0;
    Node *A = Hospital.data[i][j].antrian.head;
    if(A != NULL){
        while(A != NULL){
            count++;
            A = A->next;
        }
    }
    return count;
}

void FileConfig(const char *filePath, Matrix *Hospital, UserList *user1){ //BELUM SELESAI, belum ada data ruangan? // membuat/overwrite file config
    FILE *fp = fopen(filePath, "w");
    if (fp == NULL) {
        printf(RED "Gagal membuat file di path: %s\n" RESET, filePath);
        return;
    }
    int terisi = 0;
    int nol = 0;
    int dokter;
    fprintf(fp, "%d %d\n", Hospital->rows, Hospital->cols);
    fprintf(fp, "%d\n", Hospital->kapasitasRuangan);
    for(int i = 0; i < Hospital->rows; i++){
        for(int j = 0; j < Hospital->cols ; j++){
            for(int k = 0; k < isiRuangan(*Hospital, i, j)+1 ; k++){
                if(k == 0){
                    User *I = findUser(user1, Hospital->data[i][j].nama_dokter);
                    if(I != NULL){
                        fprintf(fp, "%d ", I->id);
                        dokter = I->id;
                    }
                    else{
                        fprintf(fp, "%d ", nol);
                        dokter = 0;
                    }
                }
                else if(dokter != 0){
                    Node *A = Hospital->data[i][j].antrian.head;
                    if(A != NULL){
                        while(A != NULL){
                            fprintf(fp, "%d ", A->info);
                            A = A->next;
                        }
                    }
                    
                }
                terisi++;
            }
            fprintf(fp, "\n");
            terisi = 0;
        }
    }
    int PasienObat[100][100];
    int X = JmlhInventory_ada(*user1, PasienObat);
    
    fprintf(fp, "%d\n", X);
    for(int i = 0; i < X; i++){
        for(int j = 0; j < 100; j++){
            if(j == 0){
                fprintf(fp, "%d ", PasienObat[i][j]);
            }
            else{
                if(PasienObat[i][j] != 0){
                    fprintf(fp, "%d ", PasienObat[i][j]);
                    terisi++;
                }
            }
            
        }
        if(terisi > 0){
            fprintf(fp, "\n");
        }
        terisi = 0;
    }
    
    fclose(fp);
}


void SAVE(UserList *user1, ObatList *Obat, PenyakitList *sakit, Obat_PenyakitList *obat_penyakit, Matrix *Hospital){//obatlist, dll perlu tidak?
    char nama_folder[50];
    //char file_user[50] = "user.csv";
    //char file_obat[50] = "obat.csv";
    //char file_penyakit[50] = "penyakit.csv";
    //char file_obatpenyakit[50] = "obat_penyakit.csv";
    //char file_config[50] = "config.txt";
    char pathUser[256];
    char base[50] = "file";
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
        printf(GREEN "Berhasil menyimpan data di folder " CYAN "data/%s\n\n" RESET, nama_folder);
    }
    else if (folder_exist(FullFolder) == 1 && file_exist(FullFolder) == 0){
        printf(GRAY "Membuat folder data/%s (sudah ada)\n" RESET, nama_folder);
        FileUser(pathUser, user1);
        FileObat(pathObat, Obat);
        FilePenyakit(pathPenyakit, sakit);
        FileObat_Penyakit(pathObatPenyakit, obat_penyakit);
        FileConfig(pathConfig, Hospital, user1);
        printf(GREEN "Berhasil menyimpan data di folder " CYAN "data/%s\n\n" RESET, nama_folder);
    }
    else{
        printf(GRAY "Membuat folder data/%s\n" RESET, nama_folder);
        folder(FullFolder);
        FileUser(pathUser, user1);
        FileObat(pathObat, Obat);
        FilePenyakit(pathPenyakit, sakit);
        FileObat_Penyakit(pathObatPenyakit, obat_penyakit);
        FileConfig(pathConfig, Hospital, user1);
        printf(GREEN "Berhasil menyimpan data di folder " CYAN "data/%s\n\n" RESET, nama_folder);
    }
}