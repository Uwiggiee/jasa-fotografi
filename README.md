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

## Fitur Utama & Status Penyelesaian (Estimasi: 95%)

- **Autentikasi Pengguna:**

  - [x] Login & Registrasi Pelanggan (via nomor telepon dengan auto-register).
  - [x] Login Admin (username="admin", password="admin123").
  - [x] Logout dengan session management.
  - [x] Persistent data storage untuk user pelanggan.

- **Manajemen Booking (Pelanggan):**

  - [x] Melihat semua jadwal booking yang ada (dengan custom merge sort).
  - [x] Membuat booking baru dengan validasi konflik jadwal.
  - [x] Membatalkan booking berdasarkan kode booking.
  - [x] Undo pembatalan booking menggunakan custom stack. ✅

- **Manajemen Booking (Admin):**

  - [x] Melihat semua jadwal booking & detail pemesan (dengan sorting).
  - [x] Membuat booking baru untuk pelanggan.
  - [x] Membatalkan booking pelanggan berdasarkan kode booking.
  - [x] Undo pembatalan booking menggunakan custom stack. ✅
  - [x] Edit booking yang sudah ada. ✅ **IMPLEMENTED**

- **Manajemen User (Admin):**

  - [x] Melihat daftar semua user pelanggan yang terdaftar.

- **Penyimpanan Data:**
  - [x] Data user pelanggan disimpan dan dimuat dari file `data/users.txt`.
  - [x] Data booking disimpan dan dimuat dari file `data/bookings.txt`.
  - [x] Auto-recovery counter booking dari file existing.
  - [x] Error handling untuk file corruption.

## Struktur Data yang Digunakan

### Struktur Data Standard Library (50%)

- **`std::vector<User *>`**:

  - Digunakan di kelas `Auth` (`daftarSemuaUserPelanggan`) untuk menyimpan daftar pointer ke objek `User` pelanggan yang terdaftar.
  - Memory management dengan destructor untuk mencegah memory leak.

- **`std::vector<Booking>`**:

  - Digunakan di kelas `SistemPemesanan` (`semuaDataBooking`) untuk menyimpan semua objek `Booking`.
  - Digunakan dalam algoritma sorting untuk membuat copy sementara.

- **`std::string`**:

  - Digunakan secara luas untuk nama, nomor telepon, kode booking, input tanggal/waktu, path file.
  - Kelas `Booking` menyimpan `pemesanNama` dan `pemesanNomorTelepon` sebagai `std::string`.

- **`std::ifstream` dan `std::ofstream`**:

  - File I/O untuk `data/users.txt` dan `data/bookings.txt`.
  - Dengan error handling dan auto-create file jika tidak ada.

- **`std::stringstream`**:

  - Parsing CSV data dari file dan formatting output.

- **`time_t` dan `struct tm`**:
  - Representasi waktu dalam `Booking` class dengan konversi string ke time_t.

### Struktur Data Custom Implementation (50%)

- **`CustomStack<Booking>` (Template Class)** ✅ **IMPLEMENTED**:

  - **Implementasi**: Array-based stack dengan kapasitas maksimal 10 elemen.
  - **Operasi**: `push()`, `pop()`, `top()`, `isEmpty()`, `size()`, `isFull()`.
  - **Memory Management**: Copy constructor & assignment operator untuk deep copy.
  - **Template**: Generic template dengan explicit instantiation untuk `Booking`.
  - **Lokasi**: `include/CustomStack.h` dan `src/CustomStack.cpp`.
  - **Penggunaan**: Fitur undo pembatalan booking dalam `SistemPemesanan`.

- **Custom Merge Sort Algorithm** ✅ **IMPLEMENTED**:
  - **Algoritma**: Merge Sort dengan divide-and-conquer approach.
  - **Kompleksitas**: O(n log n) time complexity, O(n) space complexity.
  - **Implementasi**:
    - `mergeSort()`: Recursive function untuk pembagian array.
    - `merge()`: Menggabungkan dua sorted subarrays.
    - `compareBookings()`: Custom comparator berdasarkan `time_t`.
  - **Lokasi**: `include/SortingAlgorithm.h` dan `src/SortingAlgorithm.cpp`.
  - **Penggunaan**: Sorting booking berdasarkan waktu di `tampilkanSemuaBooking()`.

## Algoritma & Teknik Khusus

### Interval Overlap Detection

Algoritma untuk mendeteksi konflik jadwal booking:

```cpp
bool cekJadwalBentrok(const Booking &bookingBaru) const {
    // Interval overlap: A.start < B.end && A.end > B.start
    if (bookingBaru.getWaktuMulai() < bookingLama.getWaktuSelesai() &&
        bookingBaru.getWaktuSelesai() > bookingLama.getWaktuMulai()) {
        return true; // BENTROK!
    }
    return false;
}
```

### Time Management System

- **String to time_t conversion**: `ubahStringTanggalKeTimeT()` dan `ubahStringJamKeTimeT()`.
- **Format support**: "dd/mm/yyyy" untuk tanggal dan "hh:mm" untuk waktu.
- **Validation**: Error handling untuk format tanggal/waktu yang tidak valid.

### Object-Oriented Design

- **Inheritance**: `Admin` extends `User` dengan virtual function override.
- **Polymorphism**: Virtual functions untuk `isAdmin()`, `makeBooking()`, `cancelBooking()`.
- **Encapsulation**: Private data members dengan getter/setter methods.

## Fitur Undo Pembatalan Booking ✅ **WORKING**

Sistem undo menggunakan custom stack yang sudah terimplementasi dengan sempurna:

- **Push Operation**: Setiap kali booking dibatalkan via `prosesBatalBooking()`, booking di-push ke `undoStack`.
- **Pop Operation**: Fungsi `undoCancellation()` mem-pop booking terakhir dan mengembalikan statusnya.
- **UI Integration**: Menu menampilkan "(Tidak tersedia)" jika stack kosong (behavior yang benar).
- **Session-based**: Stack direset setiap kali program restart.

## Sistem Sorting Jadwal ✅ **WORKING**

Implementasi custom merge sort yang sudah berfungsi:

- **Stable sorting**: Mempertahankan urutan untuk booking dengan waktu sama.
- **Performance**: O(n log n) guaranteed pada semua kasus.
- **Integration**: Dipanggil setiap kali `tampilkanSemuaBooking()` untuk menampilkan jadwal terurut.

## Sistem Kode Booking

Kode booking otomatis dengan format `B-XXX`:

- **Counter persistence**: Counter diambil dari kode booking terbesar di file.
- **Sequential generation**: Format `B-001`, `B-002`, dst dengan zero-padding.
- **Collision avoidance**: Sistem memastikan tidak ada duplikasi kode.

## Kompilasi dan Menjalankan

### Windows (build.bat tersedia):

```bash
build.bat
```

### Linux/Unix:

```bash
g++ -std=c++17 -Wall -Wextra -I./include src/*.cpp -o booking_system
./booking_system
```

### Struktur direktori data:

Pastikan folder `data/` ada di direktori root:

```bash
mkdir -p data
```

## Status Implementasi Struktur Data Custom

| Komponen                 | Status             | Implementasi                      |
| ------------------------ | ------------------ | --------------------------------- |
| **CustomStack Template** | ✅ Complete        | Array-based, O(1) operations      |
| **Merge Sort Algorithm** | ✅ Complete        | O(n log n), stable sorting        |
| **Undo Functionality**   | ✅ Working         | Stack-based dengan UI integration |
| **Conflict Detection**   | ✅ Complete        | Interval overlap algorithm        |
| **File I/O System**      | ✅ Complete        | CSV format dengan error handling  |
| **Edit Booking**         | ✅ Complete        | Multi-field editing dengan validasi |

## Roadmap Pengembangan

- [x] ~~Implementasi `CustomStack` class dengan template~~ ✅ **DONE**
- [x] ~~Implementasi custom sorting algorithm (Merge Sort)~~ ✅ **DONE**
- [x] ~~Integrasi fitur undo pembatalan booking~~ ✅ **DONE**
- [x] ~~Implementasi fitur edit booking untuk admin~~ ✅ **DONE**
- [ ] Unit testing untuk struktur data custom
- [ ] Performance benchmarking untuk sorting algorithm
- [ ] Build system optimization (Makefile untuk Linux)

**Overall Progress: ~98% Complete** 🚀

---
