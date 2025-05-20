#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "../header/user.h"
#include "../header/matrix.h"
#include "../header/queue.h"
#include "../header/boolean.h"


#define initialCap 10
#define maxChar 100
#define MAX_RELASI 1000


void loadDataUser(const char *filename, UserList *userList, Set *set) {
    
    FILE *fileUser = fopen(filename, "r");
    if (fileUser == NULL) {
        perror("Gagal membuka file User!\n");
        return;
    }

    userList->data = (User *)malloc(initialCap * sizeof(User));
    userList->Neff = 0;
    userList->capacity = initialCap;

    char line[1024];
    fgets(line, sizeof(line), fileUser); // Lewati header

    while (fgets(line, sizeof(line), fileUser)) {
        User u;
        char buffer[128];
        int idx = 0, field = 0, i = 0;

        memset(&u, 0, sizeof(User)); // Inisialisasi semua field jadi nol

        while (line[i] != '\0' && line[i] != '\n') {
            if (line[i] == ';') {
                buffer[idx] = '\0';

                switch (field) {
                    case 0: u.id = atoi(buffer); break;
                    case 1: 
                        strncpy(u.username, buffer, sizeof(u.username)); 
                        insertSet(set, buffer);
                        break;
                    case 2: strncpy(u.password, buffer, sizeof(u.password)); break;
                    case 3: 
                        if (strcmp(buffer, "ROLE_PASIEN") == 0) {
                            u.role = ROLE_PASIEN;
                            break;
                        } else if (strcmp(buffer, "ROLE_DOKTER") == 0) {
                            u.role = ROLE_DOKTER;
                            break;
                        } else if (strcmp(buffer, "ROLE_MANAGER") == 0) {
                            u.role = ROLE_MANAGER;
                            break;
                        }
                    case 4: strncpy(u.riwayat_penyakit, buffer, sizeof(u.riwayat_penyakit)); break;
                    case 5: u.suhu_tubuh = atof(buffer); break;
                    case 6: u.tekanan_darah_sistolik = atoi(buffer); break;
                    case 7: u.tekanan_darah_diastolik = atoi(buffer); break;
                    case 8: u.detak_jantung = atoi(buffer); break;
                    case 9: u.saturasi_oksigen = atof(buffer); break;
                    case 10: u.kadar_gula_darah = atoi(buffer); break;
                    case 11: u.berat_badan = atof(buffer); break;
                    case 12: u.tinggi_badan = atoi(buffer); break;
                    case 13: u.kadar_kolesterol = atoi(buffer); break;
                    case 14: u.kadar_kolesterol_Ldl = atoi(buffer); break;
                    case 15: u.trombosit = atoi(buffer); break;
                }

                field++;
                idx = 0;
            } else {
                buffer[idx++] = line[i];
            }
            i++;
        }

        // Ambil field terakhir (setelah koma terakhir)
        buffer[idx] = '\0';
        if (field == 15) u.trombosit = atoi(buffer);

        if (userList->Neff >= userList->capacity) {
            userList->capacity *= 2;
            userList->data = (User *)realloc(userList->data, userList->capacity * sizeof(User));
        }
        
        initStack(&u.perut);
        userList->data[userList->Neff++] = u;
    }

    fclose(fileUser);
}

void loadDataPenyakit(const char *filename, PenyakitList *listPenyakit) {
    FILE *filePenyakit = fopen(filename, "r");
    if (filePenyakit == NULL) {
        printf("Gagal membuka file penyakit!");
        return;
    }

    listPenyakit->capacity = 10;
    listPenyakit->Neff = 0;
    listPenyakit->data = malloc(listPenyakit->capacity * sizeof(Penyakit));

    char line[1024];
    fgets(line, sizeof(line), filePenyakit); 
    while (fgets(line, sizeof(line), filePenyakit)) {
        if (listPenyakit->Neff >= listPenyakit->capacity) {
            listPenyakit->capacity *= 2;
            listPenyakit->data = realloc(listPenyakit->data, listPenyakit->capacity * sizeof(Penyakit));
        }

        Penyakit *p = &listPenyakit->data[listPenyakit->Neff];
        char buffer[128];
        int idx = 0, field = 0, i = 0;

        memset(p, 0, sizeof(Penyakit));

        while (line[i] != '\0' && line[i] != '\n') {
            if (line[i] == ';') {
                buffer[idx] = '\0';

                switch (field) {
                    case 0: p->id = atoi(buffer); break;
                    case 1: strncpy(p->nama, buffer, sizeof(p->nama)); break;
                    case 2: p->suhu_tubuh_Min = atof(buffer); break;
                    case 3: p->suhu_tubuh_Max = atof(buffer); break;
                    case 4: p->tekanan_sistolik_Min = atoi(buffer); break;
                    case 5: p->tekanan_sistolik_Max = atoi(buffer); break;
                    case 6: p->tekanan_diastolik_Min = atoi(buffer); break;
                    case 7: p->tekanan_diastolik_Max = atoi(buffer); break;
                    case 8: p->detak_jantung_Min = atoi(buffer); break;
                    case 9: p->detak_jantung_Max = atoi(buffer); break;
                    case 10: p->saturasi_Min = atof(buffer); break;
                    case 11: p->saturasi_Max = atof(buffer); break;
                    case 12: p->kadar_gula_Min = atoi(buffer); break;
                    case 13: p->kadar_gula_Max = atoi(buffer); break;
                    case 14: p->berat_badan_Min = atof(buffer); break;
                    case 15: p->berat_badan_Max = atof(buffer); break;
                    case 16: p->tinggi_badan_Min = atoi(buffer); break;
                    case 17: p->tinggi_badan_Max = atoi(buffer); break;
                    case 18: p->kolesterol_Min = atoi(buffer); break;
                    case 19: p->kolesterol_Max = atoi(buffer); break;
                    case 20: p->trombosit_Min = atoi(buffer); break;
                }

                field++;
                idx = 0;
            } else {
                buffer[idx++] = line[i];
            }
            i++;
        }

        // Field terakhir (trombosit_Max)
        buffer[idx] = '\0';
        if (field == 21) p->trombosit_Max = atoi(buffer);

        listPenyakit->Neff++;
    }

    fclose(filePenyakit);
}


void loadDataObat(const char *fileName, ObatList *listObat){
    FILE *fileObat = fopen(fileName, "r");
    if (fileObat == NULL) {
        perror("Gagal membuka file obat");
        return;
    }

    listObat->capacity = initialCap;
    listObat->Neff = 0;
    listObat->data = malloc(listObat->capacity * sizeof(Obat));

    char line[256];

    fgets(line, sizeof(line), fileObat);  // Lewati header jika ada

    while (fgets(line, sizeof(line), fileObat)) {
        if (listObat->Neff >= listObat->capacity) {
            listObat->capacity *= 2;
            listObat->data = realloc(listObat->data, listObat->capacity * sizeof(Obat));
        }

        Obat o;
        char buffer[128];
        int i = 0, j = 0, field = 0;

        while (line[i] != '\0' && line[i] != '\n') {
            if (line[i] == ';') {
                buffer[j] = '\0';
                // o.id = atoi(buffer);  // field pertama: id
                // field++;
                // j = 0;

                if (field == 0) {
                    o.id = atoi(buffer);
                } else if (field == 1) {
                    strncpy(o.nama, buffer, sizeof(o.nama));
                }

                field++;
                j = 0;
            } else {
                buffer[j++] = line[i];
            }
            i++;
        }

        buffer[j] = '\0';
        if (field == 1) {
            strncpy(o.nama, buffer, sizeof(o.nama));
        }

        listObat->data[listObat->Neff++] = o;
    }

    fclose(fileObat);
}

void loadDataObatPenyakit(const char *filename, Obat_PenyakitList *relasiList) {
    FILE *fileOP = fopen(filename, "r");
    if (fileOP == NULL) {
        perror("Gagal membuka file obat-penyakit");
        return;
    }

    relasiList->data = malloc(initialCap * sizeof(Obat_Penyakit));
    relasiList->Neff = 0;
    relasiList->capacity = initialCap;

    char line[256];
    fgets(line, sizeof(line), fileOP);  // Lewati header

    while (fgets(line, sizeof(line), fileOP)) {
        Obat_Penyakit r;
        char buffer[64];
        int i = 0, j = 0, field = 0;

        while (line[i] != '\0' && line[i] != '\n') {
            if (line[i] == ';') {
                buffer[j] = '\0';
                if (field == 0) r.id_obat = atoi(buffer);
                else if (field == 1) r.id_penyakit = atoi(buffer);
                field++;
                j = 0;
            } else {
                buffer[j++] = line[i];
            }
            i++;
        }

        buffer[j] = '\0';
        if (field == 2) r.urutan_minum = atoi(buffer);

        // Tambah ke list
        if (relasiList->Neff >= relasiList->capacity) {
            relasiList->capacity *= 2;
            relasiList->data = realloc(relasiList->data, relasiList->capacity * sizeof(Obat_Penyakit));
        }

        relasiList->data[relasiList->Neff++] = r;
    }

    fclose(fileOP);
}

User* findUserById(UserList *userList, int id) {
    for (int i = 0; i < userList->Neff; i++) {
        if (userList->data[i].id == id) {
            return &(userList->data[i]);
        }
    }
    return NULL;  // Tidak ditemukan
}

void loadConfig(const char *filename, Matrix *denah, UserList *userList){
    FILE *fileConfig = fopen(filename, "r");
    if (fileConfig == NULL) {
        printf("Error: Tidak dapat membuka file %s\n", filename);
        return;
    }

    int rows, cols;
    fscanf(fileConfig, "%d %d\n", &rows, &cols);
    denah->rows = rows;
    denah->cols = cols;

    // Baca kapasitas maksimal pasien per ruangan
    int kapasitas;
    fscanf(fileConfig, "%d\n", &kapasitas);
    denah->kapasitasRuangan = kapasitas;

    // Inisialisasi seluruh matrix ruangan
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            denah->data[i][j].nama_dokter[0] = '\0'; // kosongkan nama dokter
            initQueue(&(denah->data[i][j].antrian)); // inisialisasi antrian pasien
        }
    }

    // Baca data antrian per ruangan sebanyak rows*cols baris
    for (int i = 0; i < rows * cols; i++) {
        int dokterId;
        // Cek apakah baris kosong atau hanya 0 (tidak ada dokter & pasien)
        char line[256];
        if (fgets(line, sizeof(line), fileConfig) == NULL) break;

        // Hilangkan newline jika ada
        line[strcspn(line, "\r\n")] = 0;

        // Kalau baris "0" berarti tidak ada dokter & pasien
        if (strcmp(line, "0") == 0) {
            // Ruangan i tanpa dokter dan pasien
            int r = i / cols;
            int c = i % cols;
            denah->data[r][c].nama_dokter[0] = '\0';
            // antrian sudah kosong karena diinisialisasi sebelumnya
            continue;
        }

        // Kalau tidak 0, parse data dokter dan pasien
        char *token = strtok(line, " ");
        if (token == NULL) continue;
        dokterId = atoi(token);

        // Simpan dokter ID sebagai string ke nama_dokter
        int r = i / cols;
        int c = i % cols;
        sprintf(denah->data[r][c].nama_dokter, "Dokter%d", dokterId);

        // Sisa token adalah id pasien, masukkan ke antrian
        while ((token = strtok(NULL, " ")) != NULL) {
            int pasienId = atoi(token);
            enqueue(&(denah->data[r][c].antrian), pasienId);
        }
    }

    // Baris berikutnya: banyak pasien yang mempunyai inventory obat
    int jumlahPasienInventory = 0;
    fscanf(fileConfig, "%d\n", &jumlahPasienInventory);

    // Untuk setiap pasien inventory, baca id pasien dan daftar obat
    // (kalau mau disimpan ke struktur data pasien, di luar scope prosedur ini)
    for (int i = 0; i < jumlahPasienInventory; i++) {
    char line[256];
    if (fgets(line, sizeof(line), fileConfig) == NULL) break;
    line[strcspn(line, "\r\n")] = 0;

    char *token = strtok(line, " ");
    if (token == NULL) continue;
    int pasienId = atoi(token);

    // Cari User sesuai pasienId
    User *user = findUserById(userList, pasienId);
    if (user == NULL) continue; // pasien tidak ditemukan, skip

    user->inventory.jumlahObat = 0;
    while ((token = strtok(NULL, " ")) != NULL) {
        int idObat = atoi(token);
        user->inventory.obat[user->inventory.jumlahObat++] = idObat;
    }
}

    fclose(fileConfig);
}
// void loadDataConfig(const char *filename, Matrix *rumahSakit, Inventory *daftarInventory, int *jumlahInventory) {
//     FILE *fileConfig = fopen(filename, "r");
//     if (!fileConfig) {
//         printf("Gagal membuka file konfigurasi.\n");
//         return;
//     }

//     // Baris 1: ukuran denah
//     rumahSakit->rows = readInt(fileConfig);
//     fgetc(fileConfig);  // Buang spasi
//     rumahSakit->cols = readInt(fileConfig);
    
//     // Baris 2: kapasitas ruangan
//     rumahSakit->kapasitasRuangan = readInt(fileConfig);

//     // Baris 3-8: ruangan
//     for (int i = 0; i < rumahSakit->rows * rumahSakit->cols; i++) {
//         int dokterId = readInt(fileConfig);

//         int row = i / rumahSakit->cols;
//         int col = i % rumahSakit->cols;

//         initQueue(&rumahSakit->data[row][col].antrian);

//         if (dokterId == 0) {
//             strcpy(rumahSakit->data[row][col].nama_dokter, "-");
//             while (fgetc(fileConfig) != '\n'); // Skip to next line
//             continue;
//         }

//         sprintf(rumahSakit->data[row][col].nama_dokter, "Dokter %d", dokterId);

//         int pasienId;
//         while ((pasienId = readInt(fileConfig)) != -1) {
//             enqueue(&rumahSakit->data[row][col].antrian, pasienId);

//             int c = fgetc(fileConfig);
//             if (c == '\n' || c == EOF) break;
//             else ungetc(c, fileConfig);  // Put back character to be read again
//         }
//     }

//     // Baris 9: jumlah inventory
//     *jumlahInventory = readInt(fileConfig);

//     // Baris 10+: daftar inventory
//     for (int i = 0; i < *jumlahInventory; i++) {
//         int pasienId = readInt(fileConfig);
//         daftarInventory[i].pasienId = pasienId;
//         daftarInventory[i].jumlahObat = 0;

//         while (1) {
//             int obatId = readInt(fileConfig);
//             if (obatId == -1) break;

//             daftarInventory[i].obat[daftarInventory[i].jumlahObat++] = obatId;

//             int c = fgetc(fileConfig);
//             if (c == '\n' || c == EOF) break;
//             else ungetc(c, fileConfig);  // Put back character to be read again
//         }
//     }

//     fclose(fileConfig);
//     printf("Data konfigurasi berhasil dimuat.\n");
// }

void LOAD(const char *folderName, UserList *userList, PenyakitList *penyakitList, ObatList *obatList, Obat_PenyakitList *relasiList, Set *nama_unik, Matrix *denah){
    char path[256];
    struct stat sb;

    // Bangun path lengkap: ./file/data 1
    snprintf(path, sizeof(path), "./file/%s", folderName);

    // Validasi apakah folder ada
    if (stat(path, &sb) != 0 || !S_ISDIR(sb.st_mode)) {
        printf("Folder '%s' tidak ditemukan di dalam folder 'file/'\n", folderName);
        return;
    }

    // Bangun path masing-masing file CSV
    char pathUser[300], pathPenyakit[300], pathObat[300], pathRelasi[300], pathConfig[300];

    snprintf(pathUser, sizeof(pathUser), "%s/user.csv", path);
    snprintf(pathPenyakit, sizeof(pathPenyakit), "%s/penyakit.csv", path);
    snprintf(pathObat, sizeof(pathObat), "%s/obat.csv", path);
    snprintf(pathRelasi, sizeof(pathRelasi), "%s/obat_penyakit.csv", path);
    snprintf(pathConfig, sizeof(pathConfig), "%s/config.txt", path);

    // Panggil prosedur pemrosesan masing-masing
    loadDataUser(pathUser, userList, nama_unik);
    loadDataPenyakit(pathPenyakit, penyakitList);
    loadDataObat(pathObat, obatList);
    loadDataObatPenyakit(pathRelasi, relasiList);
    loadConfig(pathConfig, denah, userList);
}