# dilakukan oleh:

-Walid Nadirul Ahnaf

-Syafiq Syadidul Azmi

-Ludwig Alven Tama Lumban Tobing


# Sistem Pemesanan Jasa Fotografi

Aplikasi manajemen pemesanan jasa fotografi berbasis command-line interface (CLI) yang dikembangkan dengan C++. Sistem ini menyediakan solusi efisien untuk mengelola jadwal pemesanan jasa fotografi dengan fitur-fitur komprehensif dan antarmuka yang intuitif.

## Struktur Proyek

```
FotografiBookingSystem/
├── include/                     
│   ├── Booking.h                # Header untuk class Booking
│   ├── SistemPemesanan.h        # Header untuk class SistemPemesanan
│   ├── User.h                   # Header untuk class User (pengguna umum)
│   ├── Admin.h                  # Header untuk class Admin
│   └── Auth.h                   # Header untuk autentikasi dan manajemen sesi
│
├── src/                         
│   ├── Booking.cpp              # Implementasi class Booking
│   ├── SistemPemesanan.cpp      # Implementasi class SistemPemesanan
│   ├── User.cpp                 # Implementasi class User
│   ├── Admin.cpp                # Implementasi class Admin
│   ├── Auth.cpp                 # Implementasi fungsi autentikasi
│   └── main.cpp                 # Program utama dengan fungsi main()
│
├── Makefile                     # Untuk kompilasi project
└── README.md                    # Dokumentasi proyek
```

## Deskripsi Komponen

### Header Files (include/)

#### Booking.h
Mendefinisikan class `Booking` yang menyimpan informasi satu pemesanan, termasuk nama pelanggan, nomor telepon, tanggal, waktu mulai dan selesai, kode booking, dan status aktif. Class ini juga menyediakan method untuk menampilkan informasi booking dan getter/setter untuk setiap atribut.

#### SistemPemesanan.h
Mendefinisikan class `SistemPemesanan` yang mengelola semua operasi inti sistem, termasuk menambahkan booking baru, melihat jadwal, membatalkan booking, dan memulihkan booking yang dibatalkan. Class ini menggunakan berbagai struktur data untuk menyimpan dan mengelola pemesanan secara efisien.

#### User.h
Mendefinisikan class `User` yang mewakili pengguna umum dalam sistem, menyimpan informasi dasar seperti nomor telepon atau ID pengguna. Class ini berisi method untuk mengakses fitur yang tersedia untuk pengguna umum seperti melihat jadwal tersedia dan membuat/membatalkan pemesanan mereka sendiri.

#### Admin.h
Mendefinisikan class `Admin` yang mewakili administrator sistem dengan hak akses lebih luas. Class ini mewarisi dari User dengan tambahan method untuk tugas administratif seperti melihat semua pemesanan, mengelola pengguna, dan mengedit/menghapus pemesanan.

#### Auth.h
Mendefinisikan fungsi dan class yang menangani autentikasi, termasuk verifikasi password admin, manajemen sesi, dan kontrol akses berdasarkan peran pengguna. File ini menyediakan interface yang konsisten untuk proses login dan validasi peran pengguna.

### Source Files (src/)

#### Booking.cpp
Implementasi dari method class `Booking` seperti konstruktor, getter/setter, dan method untuk menampilkan informasi booking. File ini juga termasuk fungsi untuk memvalidasi format tanggal dan waktu.

#### SistemPemesanan.cpp
Implementasi dari method class `SistemPemesanan`, berisi logika inti untuk semua operasi sistem termasuk validasi input, pengecekan konflik jadwal, pembuatan kode booking, dan manajemen pemesanan. File ini berisi algoritma untuk struktur data yang digunakan dalam sistem.

#### User.cpp
Implementasi dari method class `User`, menangani operasi yang dapat dilakukan oleh pengguna umum termasuk melihat jadwal tersedia dan mengelola pemesanan mereka sendiri. File ini berinteraksi dengan SistemPemesanan untuk melakukan operasi ini.

#### Admin.cpp
Implementasi dari method class `Admin`, termasuk operasi administratif tambahan seperti melihat semua data pemesanan dan mengelola pengguna. File ini berinteraksi dengan SistemPemesanan dan User untuk menjalankan operasi ini.

#### Auth.cpp
Implementasi dari fungsi autentikasi, termasuk verifikasi password admin, pencatatan login/logout, dan manajemen sesi. File ini menyediakan lapisan keamanan untuk sistem pemesanan.

#### main.cpp
Program utama yang berisi fungsi `main()`, menginisialisasi sistem, menampilkan layar login, dan menangani alur program secara keseluruhan. File ini berfungsi sebagai entry point program dan mengontrol alur eksekusi antar komponen sistem.

## Fitur Utama

### Login
Sistem menyediakan fitur login dengan dua jenis peran pengguna: pengguna umum (user) dan administrator (admin). Pengguna umum dapat mengakses sistem tanpa kata sandi khusus, sementara admin memerlukan verifikasi kata sandi untuk akses ke fitur administratif.

### Tampilan Jadwal
Pengguna dapat melihat slot waktu yang tersedia dan yang sudah dipesan, diurutkan berdasarkan tanggal dan waktu. Admin memiliki akses ke tampilan jadwal yang lebih komprehensif yang mencakup informasi lengkap tentang setiap pemesanan.

### Pembuatan Booking
Sistem menyediakan antarmuka untuk membuat pemesanan baru dengan validasi input, pengecekan konflik jadwal, dan pembuatan kode booking unik. Kode booking yang dihasilkan disimpan dalam sistem dan diberikan kepada pengguna sebagai referensi.

### Pembatalan dan Undo Booking
Pengguna atau admin dapat membatalkan pemesanan yang ada dengan memasukkan kode booking atau nomor telepon. Sistem juga menyediakan fitur "undo" untuk pembatalan yang tidak disengaja, selama slot waktu belum dipesan oleh pengguna lain.

## Struktur Data dan Tipe Data yang Digunakan

### Library yang Digunakan
- **<string>**: Untuk manipulasi string
- **<vector>**: Untuk implementasi struktur data dinamis
- **<stack>**: Untuk implementasi fitur undo
- **<chrono>**: Untuk manipulasi waktu dan tanggal
- **<unordered_map>**: Untuk pengorganisasian jadwal berdasarkan tanggal
- **<iostream>**: Untuk input/output standar

### Tipe Data Dasar
- **string**: Digunakan untuk menyimpan nama pelanggan, nomor telepon, kode booking, dll
- **time_t/chrono**: Untuk representasi internal tanggal dan waktu 
- **bool**: Untuk status aktif/tidak aktif booking
- **int**: Untuk perhitungan, indeks, dan counter booking

### Struktur Data Kompleks
- **vector<Booking>**: 
  - Menyimpan daftar semua pemesanan dalam sistem
  - Memungkinkan akses sekuensial ke seluruh booking
  - Kompleksitas: O(1) untuk akses elemen, O(n) untuk pencarian linier

- **unordered_map<string, vector<Booking>>**: 
  - Mengorganisir booking berdasarkan tanggal
  - Key: string tanggal (misal "2024-04-15") 
  - Value: vector berisi booking pada tanggal tersebut
  - Memungkinkan akses langsung O(1) ke semua booking pada tanggal tertentu
  - Mengoptimalkan proses pengecekan konflik jadwal

- **stack<Booking>**: 
  - Mengelola riwayat pembatalan dengan prinsip LIFO (Last In First Out)
  - Mendukung operasi undo pembatalan booking
  - Kompleksitas O(1) untuk operasi push dan pop

### Sistem Kode Booking
Kode booking dibuat secara deterministik menggunakan kombinasi:
- Inisial nama pelanggan
- Tanggal booking (format pendek)
- Counter sequential untuk tanggal tersebut

Contoh: "BUD0415-1" untuk booking pertama atas nama Budi pada tanggal 15 April.
Metode ini menjamin keunikan kode booking tanpa memerlukan pengecekan duplikasi.

### Hubungan Antar Struktur Data
- **Vector dan Map**: Vector menyimpan semua booking secara berurutan, sementara Map mengorganisirnya berdasarkan tanggal untuk pencarian efisien
- **Map dan Sistem Booking**: Map memungkinkan pengecekan konflik jadwal O(1) saat booking baru dibuat
- **Stack**: Menyimpan booking yang dibatalkan untuk mendukung fitur pembatalan yang dapat di-undo

### Alur Data dalam Sistem
1. Saat booking baru dibuat:
   - Data booking disimpan dalam vector utama
   - Referensi booking juga ditambahkan ke map berdasarkan tanggalnya
   - Kode booking unik digenerate dan diberikan ke pelanggan

2. Saat memeriksa ketersediaan jadwal:
   - Sistem langsung mengakses tanggal yang diminta via map
   - Memeriksa semua booking pada tanggal tersebut untuk konflik jadwal
   
3. Saat booking dibatalkan:
   - Booking ditandai tidak aktif di vector utama
   - Booking dihapus dari map jadwal
   - Booking disimpan di stack riwayat pembatalan untuk fitur undo

## Kompilasi dan Menjalankan Program

Untuk mengkompilasi program:

```bash
cd FotografiBookingSystem
make
```

Untuk menjalankan program:

```bash
./booking_system
```
Untuk compile menjalankan program:

```bash
make run
```
