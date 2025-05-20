// #include <stdio.h>
// #include <string.h>
// #include "../header/user.h"
// #include "../header/map.h"

// #define MAX_OBAT_LIST_SIZE 100
// #define MAX_OBAT_IN_INVENTORY 100

// // Fungsi untuk mendapatkan obat berdasarkan id_obat
// Obat getObatById(int id_obat) {
//     extern ObatList obatList[MAX_OBAT_LIST_SIZE];  // Misalkan obatList sudah terdefinisi sebelumnya
//     for (int i = 0; i < MAX_OBAT_LIST_SIZE; i++) {
//         if (obatList->data[i].id == id_obat) {
//             return obatList->data[i];
//         }
//     }
//     Obat emptyObat = {0, "Obat tidak ditemukan"};
//     return emptyObat;  // Kembalikan obat kosong jika tidak ditemukan
// }

// // Fungsi untuk menambahkan obat ke inventory pasien
// void addToInventory(User *u, int obatId) {
//     if (u->inventory.jumlahObat < MAX_OBAT_IN_INVENTORY) {
//         u->inventory.obat[u->inventory.jumlahObat] = obatId;
//         u->inventory.jumlahObat++;
//         // printf("Obat dengan ID %d ditambahkan ke inventory\n", obatId);  // Feedback obat yang ditambahkan
//     } else {
//         printf("Inventory pasien sudah penuh!\n");
//     }
// }

// // Prosedur untuk mengobati pasien
// void ngobatin(User *current_user, PenyakitList *penyakitList, Obat_PenyakitList *obatPenyakitList, boolean *isLogin) {
//     if (!(*isLogin)) {
//         printf("Login sebagai Dokter terlebih dahulu!\n\n");
//         return;
//     }

//     if (current_user->role == ROLE_DOKTER) {
//         printf("Dokter sedang mengobati pasien!\n");
    
//         if (current_user == NULL) {
//             printf("Tidak ada pasien untuk diperiksa!\n");
//             return;
//         }
    
//         // Riwayat penyakit pasien
//         char penyakitTerdiagnosis[100];
//         strncpy(penyakitTerdiagnosis, current_user->riwayat_penyakit, sizeof(penyakitTerdiagnosis));
    
//         // Jika pasien tidak terdiagnosis penyakit apapun
//         if (strcmp(penyakitTerdiagnosis, "Sehat") == 0) {
//             printf("Pasien tidak memiliki penyakit yang terdiagnosis!\n");
//             return;
//         }
    
//         // Menentukan penyakit yang terdiagnosis
//         Penyakit *penyakitTerdeteksi = NULL;
//         for (int i = 0; i < penyakitList->Neff; i++) {
//             if (strcmp(penyakitList->data[i].nama, penyakitTerdiagnosis) == 0) {
//                 penyakitTerdeteksi = &penyakitList->data[i];
//                 break;
//             }
//         }
    
//         if (!penyakitTerdeteksi) {
//             printf("Penyakit %s tidak ditemukan dalam daftar penyakit!\n", penyakitTerdiagnosis);
//             return;
//         }
    
//         // Menentukan obat berdasarkan penyakit yang terdiagnosis
//         printf("Pasien memiliki penyakit %s\n", penyakitTerdiagnosis);
//         printf("Obat yang harus diberikan:\n");
    
//         // Mengambil obat untuk penyakit tersebut dari Obat_Penyakit
//         for (int i = 0; i < obatPenyakitList->Neff; i++) {
//             if (obatPenyakitList->data[i].id_penyakit == penyakitTerdeteksi->id) {
//                 // Ambil obat berdasarkan id_obat
//                 Obat obat = getObatById(obatPenyakitList->data[i].id_penyakit);
//                 printf("%d. %s\n", i + 1, obat.nama);
    
//                 // Menambahkan obat ke inventory pasien
//                 addToInventory(current_user, obat.id);
//             }
//         }
//     } else {
//         printf("Anda bukan dokter! Tidak bisa diagnosis pasien!\n\n");
//     }
// }