# Sistem Pemesanan Jasa Fotografi (CLI)

Dibuat oleh:
- Walid Nadirul Ahnaf
- Syafiq Syadidul Azmi
- Ludwig Alven Tama Lumban Tobing

Aplikasi sederhana berbasis Command-Line Interface (CLI) untuk manajemen pemesanan jasa fotografi. Dibangun menggunakan C++ dengan implementasi struktur data custom.

## Struktur Proyek

```
jasa-fotografi/
├── include/                # File header (.h) untuk definisi kelas
│   ├── Admin.h
│   ├── Auth.h
│   ├── Booking.h
│   ├── CustomStack.h       # Implementasi stack custom untuk undo
│   ├── SortingAlgorithm.h  # Implementasi algoritma sorting custom
│   ├── SistemPemesanan.h
│   └── User.h
│
├── src/                    # File implementasi (.cpp) untuk logika kelas
│   ├── Admin.cpp
│   ├── Auth.cpp
│   ├── Booking.cpp
│   ├── CustomStack.cpp     # Implementasi stack custom
│   ├── SortingAlgorithm.cpp # Implementasi algoritma sorting custom
│   ├── SistemPemesanan.cpp
│   ├── User.cpp
│   └── main.cpp            # Titik masuk utama program
│
├── data/
│   ├── users.txt           # File untuk menyimpan data user pelanggan
│   └── bookings.txt        # File untuk menyimpan data booking
│
└── README.md               # Info proyek ini
```

## Fitur Utama & Status Penyelesaian (Estimasi: 85%)

*   **Autentikasi Pengguna:**
    *   [x] Login & Registrasi Pelanggan (via nomor telepon).
    *   [x] Login Admin (username & password hardcoded).
    *   [x] Logout.
*   **Manajemen Booking (Pelanggan):**
    *   [x] Melihat semua jadwal booking yang ada (dengan sorting berdasarkan tanggal).
    *   [x] Membuat booking baru.
    *   [x] Membatalkan booking (berdasarkan kode booking).
    *   [ ] Undo pembatalan booking terakhir. *(Dalam pengembangan)*
*   **Manajemen Booking (Admin):**
    *   [x] Melihat semua jadwal booking & detail pemesan (dengan sorting berdasarkan tanggal).
    *   [x] Membuat booking baru untuk pelanggan.
    *   [x] Membatalkan booking pelanggan (berdasarkan kode booking).
    *   [ ] Undo pembatalan booking terakhir. *(Dalam pengembangan)*
    *   [ ] Edit booking yang sudah ada. *(Fitur belum diimplementasikan)*
*   **Manajemen User (Admin):**
    *   [x] Melihat daftar semua user pelanggan yang terdaftar.
*   **Penyimpanan Data:**
    *   [x] Data user pelanggan disimpan dan dimuat dari file `data/users.txt`.
    *   [x] Data booking disimpan dan dimuat dari file `data/bookings.txt`.

## Struktur Data yang Digunakan

### Struktur Data Standard Library (50%)
*   **`std::vector<User *>`**:
    *   Digunakan di kelas `Auth` (`daftarSemuaUserPelanggan`) untuk menyimpan daftar pointer ke objek `User` pelanggan yang terdaftar.
*   **`std::vector<Booking>`**:
    *   Digunakan di kelas `SistemPemesanan` (`semuaDataBooking`) untuk menyimpan semua objek `Booking` yang telah dibuat (baik dari input baru maupun dari file).
*   **`std::string`**:
    *   Digunakan secara luas untuk menyimpan teks seperti nama, nomor telepon, kode booking, input tanggal/waktu, path file, dll.
    *   Kelas `Booking` kini menyimpan `pemesanNama` dan `pemesanNomorTelepon` sebagai `std::string`.
*   **`std::ifstream` dan `std::ofstream`**:
    *   Digunakan di `Auth.cpp` untuk membaca/menulis `data/users.txt`.
    *   Digunakan di `SistemPemesanan.cpp` untuk membaca/menulis `data/bookings.txt`.
*   **`std::stringstream`**:
    *   Digunakan untuk mem-parsing baris data dari file `users.txt` dan `bookings.txt`.

### Struktur Data Custom Implementation (50%)
*   **`CustomStack<Booking>`**:
    *   Implementasi stack custom menggunakan array atau linked list.
    *   Digunakan untuk menyimpan riwayat booking yang dibatalkan untuk fitur undo.
    *   Operasi: `push()`, `pop()`, `top()`, `isEmpty()`, `size()`.
    *   Lokasi: `include/CustomStack.h` dan `src/CustomStack.cpp`.
*   **Custom Sorting Algorithm**:
    *   Implementasi algoritma sorting sendiri (Quick Sort atau Merge Sort).
    *   Digunakan untuk mengurutkan daftar booking berdasarkan tanggal.
    *   Fungsi: `sortBookingsByDate()` dengan custom comparator.
    *   Lokasi: `include/SortingAlgorithm.h` dan `src/SortingAlgorithm.cpp`.
*   **`time_t` dan `struct tm`**:
    *   Digunakan dalam kelas `Booking` dan fungsi bantu di `Booking.cpp` untuk representasi dan manipulasi tanggal serta waktu booking.
    *   Digunakan juga di `SistemPemesanan.cpp` untuk mengkonversi `time_t` ke format string saat menyimpan ke file.

## Fitur Undo Pembatalan Booking

Sistem undo menggunakan custom stack untuk menyimpan riwayat booking yang dibatalkan:
- Setiap kali booking dibatalkan, data booking disimpan ke stack.
- User dapat melakukan undo untuk mengembalikan booking yang baru saja dibatalkan.
- Stack memiliki kapasitas maksimal untuk menghemat memori.
- Operasi undo hanya berlaku untuk session yang sedang berjalan.

## Sistem Sorting Jadwal

Implementasi custom sorting algorithm untuk mengurutkan booking:
- Jadwal booking diurutkan berdasarkan tanggal dan waktu secara ascending.
- Menggunakan algoritma sorting yang diimplementasi sendiri (bukan `std::sort`).
- Sorting diterapkan setiap kali menampilkan daftar booking.

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

## Roadmap Pengembangan

- [ ] Implementasi `CustomStack` class dengan template
- [ ] Implementasi custom sorting algorithm (Quick Sort/Merge Sort)
- [ ] Integrasi fitur undo pembatalan booking
- [ ] Optimasi performa sorting untuk dataset besar
- [ ] Unit testing untuk struktur data custom

---