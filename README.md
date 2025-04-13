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
Mendefinisikan class `Booking` yang menyimpan informasi satu pemesanan, termasuk nomor telepon pelanggan, lokasi, tanggal, waktu mulai dan selesai, kode booking, dan status aktif. Class ini juga menyediakan method untuk menampilkan informasi booking dan getter/setter untuk setiap atribut.

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

## Struktur Data yang Digunakan

- **Vector**: Untuk menyimpan daftar semua pemesanan
- **Unordered Map**: Untuk mengorganisir jadwal berdasarkan tanggal
- **Unordered Set**: Untuk memastikan keunikan kode booking
- **Stack**: Untuk mengelola riwayat pembatalan dan mendukung operasi undo

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

## Pengembangan

Proyek ini dikembangkan menggunakan bahasa pemrograman C++ dengan fokus pada pendekatan berorientasi objek dan penerapan struktur data yang efisien. Sistem ini dirancang untuk modularitas dan kemudahan pemeliharaan.
```