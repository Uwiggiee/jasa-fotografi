# Sistem Pemesanan Jasa Fotografi (CLI)

Dibuat oleh:
- Walid Nadirul Ahnaf
- Syafiq Syadidul Azmi
- Ludwig Alven Tama Lumban Tobing

Aplikasi sederhana berbasis Command-Line Interface (CLI) untuk manajemen pemesanan jasa fotografi. Dibangun menggunakan C++.

## Struktur Proyek

```
jasa-fotografi/
├── include/                # File header (.h) untuk definisi kelas
│   ├── Admin.h
│   ├── Auth.h
│   ├── Booking.h
│   ├── SistemPemesanan.h
│   └── User.h
│
├── src/                    # File implementasi (.cpp) untuk logika kelas
│   ├── Admin.cpp
│   ├── Auth.cpp
│   ├── Booking.cpp
│   ├── SistemPemesanan.cpp
│   ├── User.cpp
│   └── main.cpp            # Titik masuk utama program
│
├── data/
│   ├── users.txt           # File untuk menyimpan data user pelanggan
│   └── bookings.txt        # File untuk menyimpan data booking
│
├── bin/                    # (Opsional) Tempat output hasil kompilasi
│
└── README.md               # Info proyek ini
```

## Fitur Utama & Status Penyelesaian (Estimasi: 85%)

*   **Autentikasi Pengguna:**
    *   [x] Login & Registrasi Pelanggan (via nomor telepon).
    *   [x] Login Admin (username & password hardcoded).
    *   [x] Logout.
*   **Manajemen Booking (Pelanggan):**
    *   [x] Melihat semua jadwal booking yang ada.
    *   [x] Membuat booking baru.
    *   [x] Membatalkan booking (berdasarkan kode booking).
*   **Manajemen Booking (Admin):**
    *   [x] Melihat semua jadwal booking & detail pemesan.
    *   [x] Membuat booking baru untuk pelanggan.
    *   [x] Membatalkan booking pelanggan (berdasarkan kode booking).
    *   [ ] Edit booking yang sudah ada. *(Fitur belum diimplementasikan)*
*   **Manajemen User (Admin):**
    *   [x] Melihat daftar semua user pelanggan yang terdaftar.
*   **Penyimpanan Data:**
    *   [x] Data user pelanggan disimpan dan dimuat dari file `data/users.txt`.
    *   [x] Data booking disimpan dan dimuat dari file `data/bookings.txt`.

## Struktur Data yang Digunakan

*   **`std::vector<User *>`**:
    *   Digunakan di kelas `Auth` (`daftarSemuaUserPelanggan`) untuk menyimpan daftar pointer ke objek `User` pelanggan yang terdaftar.
*   **`std::vector<Booking>`**:
    *   Digunakan di kelas `SistemPemesanan` (`semuaDataBooking`) untuk menyimpan semua objek `Booking` yang telah dibuat (baik dari input baru maupun dari file).
*   **`std::string`**:
    *   Digunakan secara luas untuk menyimpan teks seperti nama, nomor telepon, kode booking, input tanggal/waktu, path file, dll.
    *   Kelas `Booking` kini menyimpan `pemesanNama` dan `pemesanNomorTelepon` sebagai `std::string`.
    *   Lokasi: Semua file.
*   **`time_t` dan `struct tm`**:
    *   Digunakan dalam kelas `Booking` dan fungsi bantu di [`Booking.cpp`] untuk representasi dan manipulasi tanggal serta waktu booking.
    *   Digunakan juga di [`SistemPemesanan.cpp`] untuk mengkonversi `time_t` ke format string saat menyimpan ke file.
    
*   **`std::ifstream` dan `std::ofstream`**:
    *   Digunakan di `Auth.cpp` untuk membaca/menulis `data/users.txt`.
    *   Digunakan di `SistemPemesanan.cpp` untuk membaca/menulis `data/bookings.txt`.
   
*   **`std::stringstream`**:
    *   Digunakan untuk mem-parsing baris data dari file `users.txt` dan `bookings.txt`.
   

## Sistem Kode Booking

Kode booking saat ini dibuat secara sekuensial dengan format `B-XXX`, dimana `XXX` adalah nomor urut yang terus bertambah (misal: `B-001`, `B-002`, dst.). Nomor counter terakhir diambil dari kode booking terbesar yang ada di file `data/bookings.txt` saat program dimulai.

## Kompilasi dan Menjalankan (Linux)

1.  **Kompilasi:**
    Buka terminal di direktori utama proyek (`jasa-fotografi/`) dan jalankan:
    ```bash
    g++ -std=c++11 -Wall -Wextra -o bin/jasa_foto_app src/*.cpp -Iinclude
    ```
    (Pastikan direktori `bin/` sudah ada, atau sesuaikan output path `bin/jasa_foto_app` jika perlu. Anda mungkin juga ingin menggunakan `-std=c++17` atau yang lebih baru jika ada fitur C++ modern yang digunakan).

2.  **Menjalankan:**
    ```bash
    ./bin/jasa_foto_app
    ```

---
*Catatan: Estimasi penyelesaian fitur adalah perkiraan kasar.*