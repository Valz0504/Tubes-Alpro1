# Tugas Besar Mata Kuliah IF1210 2025 [K01-G]

## 👥 Anggota Kelompok

Nama Lengkap - NIM
Nathan Adhika Santosa - 13524041  
Emilio Justin - 13524043  
Keisha Rizka Syofyani - 13524073  
Eduard Daniel Ariajaya - 13524129  
Muh. Hartawan Haidir - 13524147

## 🛠️ Cara Menjalankan Program

1. Buka terminal (WSL)
2. Masuk ke direktori 'src': "cd src"
3. Compile program : "make clean" lalu ketik "make"
4. Jalankan program : "./main <nama folder>"

Program akan otomatis memuat file default yang berada di dalam folder '/src'.

## Catatan
 - Semua data akan disimpan di dalam folder, dimana folder tersebut berada di folder 'data' dengan file path '../src/data'

## 🔧 Fitur Program

### Fitur Utama dan Commandnya untuk Program
- 'Login' – Masuk sebagai user : LOGIN
- 'Register' – Daftar akun pasien baru : REGISTER
- 'Lupa Password` – Atur ulang kata sandi : LUPA_PASSWORD
- 'Logout` – Keluar dari akun saat ini : LOGOUT
- 'Help` – Menampilkan daftar perintah yang tersedia : HELP
- 'Lihat Denah` – Menampilkan denah rumah sakit (Login terlebih dahulu) : LIHAT_DENAH
- 'Lihat User' - Menampilkan informasi ID, Nama, Role, dan Penyakit setiap user (Login sebagai manajer terlebih dahulu) : LIHAT_USER
- 'Lihat Pasien' - Menampilkan informasi ID, Nama, dan Penyakit setiap pasien (login sebagai manajer terlebih dahulu) : LIHAT_PASIEN
- 'Lihat Dokter' - Menampilkan informasi ID dan Nama setiap dokter (login sebagai manajer terlebih dahulu) : LIHAT_DOKTER
- 'Cari User' - Menampilkan informasi ID, Nama, Role, dan Penyakit satu user (Login sebagai manajer terlebih dahulu) : CARI_USER
- 'Cari Pasien' - Menampilkan informasi ID, Nama, dan Penyakit satu pasien (Login sebagai manajer terlebih dahulu) : CARI_PASIEN
- 'Cari Dokter' - Menampilkan informasi ID dan Nama satu dokter (Login sebagai manajer terlebih dahulu) : CARI_DOKTER
- 'Lihat Semua Antrian' - Menampilkan denah rumah sakit beserta dengan informasi seluruh ruangan di rumah sakit (Login terlebih dahulu) : LIHAT_SEMUA_ANTRIAN
- 'Tambah Dokter` – Menambahkan dokter baru ke sistem (Login sebagai manajer terlebih dahulu) : TAMBAH_DOKTER
- 'Assign Dokter` – Menetapkan dokter ke ruangan tertentu (Login sebagai manajer terlebih dahulu) : ASSIGN_DOKTER
- 'Diagnosis' - Melakukan diagnosis kepada pasien (Login sebagai dokter terlebih dahulu) : DIAGNOSIS
- 'Ngobatin' - Memberikan obat kepada pasien berdasarkan diagnosis (Login sebagai dokter terlebih dahulu) : NGOBATIN
- 'Aku boleh pulang ga dok?' - Menyakan kepada dokter apabila diizinkan untuk pulang (Login sebagai pasien terlebih dahulu) : PULANGDOK
- 'Daftar Checkup' - Melakukan pendaftaran agar dapat melakukan checkup kepada dokter (Login sebagai pasien terlebih dahulu) : DAFTAR_CHECKUP
- 'Antrian saya' - Melihat posisi antrian pasien untuk dokter yang telah pasien daftar (Login sebagai pasien terlebih dahulu) : ANTRIAN
- 'Minum Obat' - Minum obat yang telah diberikan oleh dokter ke pasien satu per satu (Login sebagai pasien terlebih dahulu) : MINUM_OBAT
- 'Minum Penawar' Minum Penawar untuk 'Keluarkan' obat yang telah dikonsumsikan oleh pasien (Login sebagai pasien terlebih dahulu) : PENAWAR
- 'Exit` – Keluar dari program, semua perubahan atau tambahan akan di save : EXIT

### Fitur Tambahan
- 'Aura` – Atribut tambahan yang dimiliki oleh dokter
- 'Mainin Antrian` – Memberi kemampuan untuk cancel atau skip antrian : CANCEL_ANTRIAN atau SKIP_ANTRIAN
- 'Dead or Alive' - Fitur tambahan untuk menentukkan apakah pasien hidup atau meninggal dari setiap kali meminum obat

## 📌 Catatan Milestone

### Milestone 1
- Fitur dasar yang tersedia: 'Login', 'Register', 'Lupa Password', 'Logout', 'Help', 'Lihat Denah', 'Tambah Dokter, 'Assign Dokter', 'Load', 'Exit
- Catatan:
    - Fitur 'Load' belum dapat melacak folder custom, tetapi akan otomatis memuat file dari `/src`
    - Fitur 'Exit' belum menyimpan state program saat keluar

### Milestone 2
- Semua fitur utama sudah dapat dijalankan
- Fitur tambahan seperti 'Aura, 'Mainin Antrian', dan 'Dead or Alive' telah dibuat dan berfungsi
