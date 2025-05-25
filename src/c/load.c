#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "../header/user.h"

#define initialCap 10
#define maxChar 100
#define MAX_RELASI 1000


void loadDataUser(const char *filename, UserList *userList, Set *set) {
    
    FILE *fileUser = fopen(filename, "r");
    if (fileUser == NULL) {
        perror(RED "Gagal membuka file User!\n" RESET);
        exit(1);
    }

    CreateListDin(userList, initialCap);

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
                    case 0: 
                        u.id = atoi(buffer);
                        if (u.id > userList->currMaxId) {
                            userList->currMaxId = u.id;
                        }
                        break;
                    case 1: 
                        strncpy(u.username, buffer, sizeof(u.username));
                        // u.username[sizeof(u.username)-1] = '\0';
                        // u.username[strcspn(u.username, "\r\n")] = 0;
                        toLower(buffer); 
                        insertSet(set, buffer);
                        break;
                    case 2: strncpy(u.password, buffer, sizeof(u.password)); break;
                    case 3: 
                        if (strcmp(buffer, "pasien") == 0) {
                            u.role = ROLE_PASIEN;
                            break;
                        } else if (strcmp(buffer, "dokter") == 0) {
                            u.role = ROLE_DOKTER;
                            break;
                        } else if (strcmp(buffer, "manager") == 0) {
                            u.role = ROLE_MANAGER;
                            break;
                        }
                        break;
                    case 4: 
                        if (strlen(buffer) == 0) {
                            strncpy(u.riwayat_penyakit, "-", sizeof(u.riwayat_penyakit));
                        } else {
                            strncpy(u.riwayat_penyakit, buffer, sizeof(u.riwayat_penyakit)); 
                        }
                        break;
                    case 5: u.suhu_tubuh = atof(buffer); break;
                    case 6: u.tekanan_darah_sistolik = atoi(buffer); break;
                    case 7: u.tekanan_darah_diastolik = atoi(buffer); break;
                    case 8: u.detak_jantung = atoi(buffer); break;
                    case 9: u.saturasi_oksigen = atof(buffer); break;
                    case 10: u.kadar_gula_darah = atoi(buffer); break;
                    case 11: u.berat_badan = atof(buffer); break;
                    case 12: u.tinggi_badan = atoi(buffer); break;
                    case 13: u.kadar_kolesterol = atoi(buffer); break;
                    case 14: u.trombosit = atoi(buffer); break;
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
        if (field == 14) u.trombosit = atoi(buffer);
        
        initStack(&u.perut);
        AddUser(userList, u);
    }

    fclose(fileUser);
}

void loadDataPenyakit(const char *filename, PenyakitList *listPenyakit) {
    FILE *filePenyakit = fopen(filename, "r");
    if (filePenyakit == NULL) {
        printf(RED "Gagal membuka file penyakit!" RESET);
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
        perror(RED "Gagal membuka file obat" RESET);
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
        char idobat[128];
        char namaobat[128];
        int i = 0, j = 0;

        while (line[i] != ';' && line[i] != '\0') {
            idobat[j++] = line[i++]; 
        }
        idobat[j] = '\0';
        i++;
        j = 0;
            
        while (line[i] != '\n' && line[i] != '\0') {
            namaobat[j++] = line[i++];
        }
        namaobat[j] = '\0';

        if (j > 0 && namaobat[j - 1] == '\r') {
            namaobat[j - 1] = '\0';
        }

        o.id = atoi(idobat);
        strncpy(o.nama, namaobat, sizeof(o.nama) - 1);
        o.nama[sizeof(o.nama) - 1] = '\0';
        listObat->data[listObat->Neff++] = o;
    }

    fclose(fileObat);
}

void loadDataObatPenyakit(const char *filename, Obat_PenyakitList *relasiList) {
    FILE *fileOP = fopen(filename, "r");
    if (fileOP == NULL) {
        perror(RED "Gagal membuka file obat-penyakit" RESET);
        return;
    }

    typedef struct {
        int idObat;
        int idPenyakit;
        int urutanMinum;
    } Temp;

    initObatPenyakitList(relasiList);

    char line[256];
    fgets(line, sizeof(line), fileOP);  // Lewati header

    while (fgets(line, sizeof(line), fileOP)) {
        Temp temp;
        char buffer[64];
        int i = 0, j = 0, field = 0;

        while (line[i] != '\0' && line[i] != '\n') {
            if (line[i] == ';') {
                buffer[j] = '\0';
                if (field == 0) temp.idObat = atoi(buffer);
                else if (field == 1) temp.idPenyakit = atoi(buffer);
                field++;
                j = 0;
            } else {
                buffer[j++] = line[i];
            }
            i++;
        }

        buffer[j] = '\0';
        if (field == 2) temp.urutanMinum = atoi(buffer);

        // Cari apakah penyakit sudah ada
        int index = -1;
        for (int i = 0; i < relasiList->length; i++) {
            if (relasiList->buffer[i].id_penyakit == temp.idPenyakit) {
                index = i;
                break;
            }
        }

        // Kalau belum ada, tambah entry baru
        if (index == -1) {
            index = relasiList->length++;
            relasiList->buffer[index].id_penyakit = temp.idPenyakit;
        }

        // Masukkan obat ke urutan yang benar
        int pos = temp.urutanMinum - 1;
        relasiList->buffer[index].urutan_obat[pos] = temp.idObat;
        relasiList->buffer[index].jumlah_obat++;
    }
    fclose(fileOP);
}

void loadConfig(const char *filename, Matrix *denah, UserList *userList) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf(RED "Error: Tidak dapat membuka file %s\n" RESET, filename);
        return;
    }

    char buffer[256];
    int index;

    // Baca ukuran denah (baris pertama)
    if (fgets(buffer, sizeof(buffer), file) == NULL) {
        printf(RED "Error: File kosong\n" RESET);
        fclose(file);
        return;
    }

    // Parse rows dan cols
    denah->rows = 0;
    denah->cols = 0;
    index = 0;
    
    // Parse rows
    while (buffer[index] >= '0' && buffer[index] <= '9') {
        denah->rows = denah->rows * 10 + (buffer[index++] - '0');
    }
    
    // Lewati spasi/pemisah
    while (buffer[index] == ' ' || buffer[index] == '\t') index++;
    
    // Parse cols
    while (buffer[index] >= '0' && buffer[index] <= '9') {
        denah->cols = denah->cols * 10 + (buffer[index++] - '0');
    }

    // Baca kapasitas (baris kedua)
    if (fgets(buffer, sizeof(buffer), file) == NULL) {
        printf(RED "Error: Format file salah (kapasitas)\n" RESET);
        fclose(file);
        return;
    }

    // Parse kapasitas dalam dan luar
    int kapasitasDalam = 0, kapasitasLuar = 0;
    index = 0;
    
    // Parse kapasitas dalam
    while (buffer[index] >= '0' && buffer[index] <= '9') {
        kapasitasDalam = kapasitasDalam * 10 + (buffer[index++] - '0');
    }
    
    // Lewati spasi/pemisah
    while (buffer[index] == ' ' || buffer[index] == '\t') index++;
    
    // Parse kapasitas luar
    while (buffer[index] >= '0' && buffer[index] <= '9') {
        kapasitasLuar = kapasitasLuar * 10 + (buffer[index++] - '0');
    }
    
    denah->kapasitasRuangan = kapasitasDalam;
    denah->kapasitasLuar = kapasitasLuar;

    // Inisialisasi semua ruangan
    for (int i = 0; i < denah->rows; i++) {
        for (int j = 0; j < denah->cols; j++) {
            denah->data[i][j].nama_dokter[0] = '\0';
            initQueue(&denah->data[i][j].antrian);
        }
    }

    // Baca state ruangan (rows * cols baris)
    for (int i = 0; i < denah->rows; i++) {
        for (int j = 0; j < denah->cols; j++) {
            if (fgets(buffer, sizeof(buffer), file) == NULL) {
                printf(RED "Error: Data ruangan tidak lengkap\n" RESET);
                fclose(file);
                return;
            }

            // Hapus newline
            buffer[strcspn(buffer, "\r\n")] = '\0';

            // Jika ruangan kosong
            if (strcmp(buffer, "0") == 0) {
                denah->data[i][j].nama_dokter[0] = '\0';
                continue;
            }

            // Parse dokter ID
            index = 0;
            int dokterId = 0;
            while (buffer[index] >= '0' && buffer[index] <= '9') {
                dokterId = dokterId * 10 + (buffer[index++] - '0');
            }


            // Cari user berdasarkan ID
            User *dokter = findUserByID(userList, dokterId);
            if (dokter != NULL) {
                // Salin nama asli dokter ke field nama_dokter
                snprintf(denah->data[i][j].nama_dokter, 100, "%s", dokter->username);
            } else {
                // Jika tidak ditemukan, fallback
                snprintf(denah->data[i][j].nama_dokter, 100, "%d", dokterId);
            }

            // Lewati spasi setelah dokter ID
            while (buffer[index] == ' ') index++;

            // Parse pasien dalam ruangan
            int currentNumber = 0;
            int pasienCount = 0;
            while (buffer[index] != '\0' && buffer[index] != '\n') {
                if (buffer[index] >= '0' && buffer[index] <= '9') {
                    currentNumber = currentNumber * 10 + (buffer[index] - '0');
                } else if (currentNumber > 0) {
                    enqueue(&denah->data[i][j].antrian, currentNumber);
                    currentNumber = 0;
                    pasienCount++;
                }
                index++;
            }
            if (currentNumber > 0) {
                enqueue(&denah->data[i][j].antrian, currentNumber);
            }

            // Lewati spasi antara pasien dalam dan antrian luar
            while (buffer[index] == ' ') index++;
        }
    }

    // Baca jumlah pasien dengan inventory (baris setelah ruangan)
    if (fgets(buffer, sizeof(buffer), file) == NULL) {
        printf(RED "Error: Tidak ada data inventory\n" RESET);
        fclose(file);
        return;
    }

    int jumlahPasienInventory = 0;
    index = 0;
    while (buffer[index] >= '0' && buffer[index] <= '9') {
        jumlahPasienInventory = jumlahPasienInventory * 10 + (buffer[index++] - '0');
    }

    // Baca data inventory masing-masing pasien
    for (int i = 0; i < jumlahPasienInventory; i++) {
        if (fgets(buffer, sizeof(buffer), file) == NULL) {
            printf(RED "Error: Data inventory tidak lengkap\n" RESET);
            break;
        }

        // Hapus newline
        buffer[strcspn(buffer, "\r\n")] = '\0';

        // Parse pasien ID
        index = 0;
        int pasienId = 0;
        while (buffer[index] >= '0' && buffer[index] <= '9') {
            pasienId = pasienId * 10 + (buffer[index++] - '0');
        }

        // Cari user di userList
        User *user = NULL;
        for (int u = 0; u < userList->Neff; u++) {
            if (userList->data[u].id == pasienId) {
                user = &userList->data[u];
                break;
            }
        }
        // printf("[DEBUG]%s\n", user->username);
        if (user == NULL) continue;

        // Lewati spasi setelah pasien ID
        while (buffer[index] == ' ') index++;

        // Parse obat-obatan
        user->inventory.jumlahObat = 0;
        int currentObat = 0;
        int obatIndex = 0;
        while (buffer[index] != '\0' && obatIndex < 100) {
            if (buffer[index] >= '0' && buffer[index] <= '9') {
                currentObat = currentObat * 10 + (buffer[index] - '0');
            } else if (currentObat > 0) {
                user->inventory.obat[obatIndex++] = currentObat;
                currentObat = 0;
            }
            index++;
        }
        if (currentObat > 0 && obatIndex < 100) {
            user->inventory.obat[obatIndex++] = currentObat;
        }
        user->inventory.jumlahObat = obatIndex;
        // for (int i = 0; i < user->inventory.jumlahObat; i++) {
        //     printf("[DEBUG]%d ", user->inventory.obat[i]);
        // } 
        // printf("\n");
        // printf("[DEBUG]%d\n", user->inventory.jumlahObat);
    }

    fclose(file);
}

void LOAD(const char *folderName, UserList *userList, PenyakitList *penyakitList, ObatList *obatList, Obat_PenyakitList *relasiList, Set *nama_unik, Matrix *denah){
    char path[256];
    struct stat sb;

    // Bangun path lengkap: ./file/data 1
    snprintf(path, sizeof(path), "./data/%s", folderName);

    // Validasi apakah folder ada
    if (stat(path, &sb) != 0 || !S_ISDIR(sb.st_mode)) {
        printf(RED "Folder '%s' tidak ditemukan di dalam folder 'data/'\n" RESET, folderName);
        exit(1);
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
    sortListByID(userList, TRUE);
    loadDataPenyakit(pathPenyakit, penyakitList);
    loadDataObat(pathObat, obatList);
    loadDataObatPenyakit(pathRelasi, relasiList);
    loadConfig(pathConfig, denah, userList);
}