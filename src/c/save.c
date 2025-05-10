#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <direct.h>
#include <sys/stat.h>
#include "user.h"

int folder_exist(const char *folderPath) {//cari keberadaan folder
    struct stat st;
    return (stat(folderPath, &st) == 0 && S_ISDIR(st.st_mode));
}
int file_exist(const char *folderPath) {//cari keberadaan file
    DIR *dir = opendir(folderPath);
    if (dir == NULL) {
        return 0; // Gagal buka folder
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        // Lewati "." dan ".."
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            closedir(dir);
            return 1; // Ada entri selain . dan ..
        }
    }

    closedir(dir);
    return 0; // Folder kosong
}
void folder(const char *folderName){//membuat folder
    if (_mkdir(folderName) == 0) {
        printf("Folder '%s' berhasil dibuat.\n", folderName);
        return 0;
    } 
    else {
        perror("Gagal membuat folder");
        return -1;
    }
}
void FileUser(const char *filePath, UserList *users){// membuat/overwrite file user
    FILE *fp = fopen(filePath, "w");
    if (fp == NULL) {
        printf("Gagal membuat file di path: %s\n", filePath);
        return 0;
    }
    fprintf(fp,
        "id,username,password,role,riwayat_penyakit,suhu_tubuh,"
        "tekanan_darah_sistolik,tekanan_darah_diastolik,detak_jantung,"
        "saturasi_oksigen,kadar_gula_darah,berat_badan,tinggi_badan,"
        "kadar_kolesterol,kadar_kolesterol_ldl,trombosit\n");
    for (int i = 0; i < users.Neff; i++) {
        User u = userList.data[i];
        fprintf(fp,
            "%d,%s,%s,%d,%s,%.1f,%d,%d,%d,%.1f,%d,%.1f,%d,%d,%d,%d\n",
            u.id, u.username, u.password, u.role, u.riwayat_penyakit,
            u.suhu_tubuh, u.tekanan_darah_sistolik, u.tekanan_darah_diastolik,
            u.detak_jantung, u.saturasi_oksigen, u.kadar_gula_darah,
            u.berat_badan, u.tinggi_badan, u.kadar_kolesterol,
            u.kadar_kolesterol_Ldl, u.trombosit
        );
    }
    fclose(fp);
}
void FileObat(const char *filePath, ObatList *obat){// membuat/overwrite file obat
    FILE *fp = fopen(filePath, "w");
    if (fp == NULL) {
        printf("Gagal membuat file di path: %s\n", filePath);
        return 0;
    }
    fprintf(fp,
        "obat_id,nama_obat\n");
    for(int i = 0; i < obat.Neff; i++){
        Obat o = ObatList.data[i];
        fprintf(fp, "%d,%s\n", o.id, o.nama);
    }
    fclose(fp);
}
void FilePenyakit(const char *filePath, PenyakitList *sakit){// membuat/overwrite file penyakit
    FILE *fp = fopen(filePath, "w");
    if (fp == NULL) {
        printf("Gagal membuat file di path: %s\n", filePath);
        return 0;
    }
    fprintf(fp, "id,nama,suhu_tubuh_Min,suhu_tubuh_Max,tekanan_sistolik_Min,tekanan_sistolik_Max,
        tekanan_diastolik_Min,tekanan_diastolik_Max,detak_jantung_Min,detak_jantung_Max,saturasi_Min,saturasi_Max,kadar_gula_Min,
        kadar_gula_Max,berat_badan_Min,berat_badan_Max,tinggi_badan_Min,tinggi_badan_Max,kolesterol_Min,
        kolesterol_Max,trombosit_Min,trombosit_Max\n");
    for(int i = 0; i < sakit.Neff; i++){
        Penyakit S = sakit.data[i];
        fprintf(fp, "%d,%s,%f,%f,%d,%d,%d,%d,%d,%d,%f,%f,%d,%d,%f,%f,%d,%d,%d,%d,%d,%d\n",
             S.id, S.nama, S.suhu_tubuh_Min, S.suhu_tubuh_Max, S.tekanan_sistolik_Min
            , S.tekanan_sistolik_Max, S.tekanan_diastolik_Min, S.tekanan_diastolik_Max
            , S.detak_jantung_Min, S.detak_jantung_Max, S.saturasi_Min, S.saturasi_Max
            , S.kadar_gula_Min, S.kadar_gula_Max, S.berat_badan_Min, S.berat_badan_Max
            , S.tinggi_badan_Min, S.tinggi_badan_Max, S.kolesterol_Min, S.kolesterol_Max
            , S.trombosit_Min, S.trombosit_Max);
    }
    fclose(fp);
}
void FileObat_Penyakit(const char *filePath, Obat_PenyakitList *obat_penyakit){// membuat/overwrite file obat-penyakit
    FILE *fp = fopen(filePath, "w");
    if (fp == NULL) {
        printf("Gagal membuat file di path: %s\n", filePath);
        return 0;
    }
    fprintf(fp, "obat_id,penyakit_id,urutan_minum\n");
    for(int i = 0; i <obat_penyakit.Neff; i++){
        Obat_Penyakit OP = obat_penyakit.data[i];
        fprintf(fp, "%d,%d,%d\n", OP.id_obat, OP.id_penyakit, OP.urutan_minum);
    }
    fclose(fp);
}
void FileConfig(const char *filePath){ //BELUM SELESAI, belum ada data ruangan? // membuat/overwrite file config
    FILE *fp = fopen(filePath, "w");
    if (fp == NULL) {
        printf("Gagal membuat file di path: %s\n", filePath);
        return 0;
    }
    
    fclose(fp);
}

void SAVE(User *current_user, UserList *user1, ObatList *Obat, PenyakitList *sakit, Obat_PenyakitList *obat_penyakit){//obatlist, dll perlu tidak?
    char nama_folder[50];
    char file_user[50] = "user.csv";
    char file_obat[50] = "obat.csv";
    char file_penyakit[50] = "penyakit.csv";
    char file_obatpenyakit[50] = "obat_penyakit.csv";
    char file_config[50] = "config.txt";
    char pathUser[50];
    char pathObat[50];
    char pathPenyakit[50];
    char pathObatPenyakit[50];
    char pathConfig[50];
    printf("Masukkan nama folder: ");
    scanf("%s", nama_folder);
    snprintf(pathUser, sizeof(pathUser), "%s/%s", nama_folder, file_user); // buat path filenya
    snprintf(pathObat, sizeof(pathObat), "%s/%s", nama_folder, file_obat);
    snprintf(pathPenyakit, sizeof(pathPenyakit), "%s/%s", nama_folder, file_penyakit);
    snprintf(pathObatPenyakit, sizeof(pathObatPenyakit), "%s/%s", nama_folder, file_obatpenyakit);
    snprintf(pathConfig, sizeof(pathConfig), "%s/%s", nama_folder, file_config);
    if(folder_exist(nama_folder) == 1 && file_exist(nama_folder) == 1){//butuh FileObat, dll tidak?
        printf("Saving...\n");
        printf("Membuat folder data...\n");
        folder(nama_folder);
        printf("Membuat folder data/%s\n", nama_folder);
        FileUser(pathUser, current_user);
        FileConfig(pathConfig);
        printf("Berhasil menyimpan data di folder data/%s!\n", nama_folder);
    }
    else if (folder_exist(nama_folder) == 1 && file_exist(nama_folder) == 0){
        printf("Saving...\n");
        FileUser(pathUser, current_user);
        FileObat(pathObat, obat);
        FilePenyakit(pathPenyakit, sakit);
        FileObat_Penyakit(pathObatPenyakit, obat_penyakit);
        FileConfig(pathConfig);
        printf("Berhasil menyimpan data di folder data/%s!\n", nama_folder);
    }
    else{
        printf("Saving...\n");
        folder(nama_folder);
        printf("Membuat folder data/%s\n", nama_folder);
        FileUser(pathUser, current_user);
        FileObat(pathObat, obat);
        FilePenyakit(pathPenyakit, sakit);
        FileObat_Penyakit(pathObatPenyakit, obat_penyakit);
        FileConfig(pathConfig);
        printf("Berhasil menyimpan data di folder data/%s!\n", nama_folder);
    }

}