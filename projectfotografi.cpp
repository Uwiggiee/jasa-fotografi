#include <iostream>
#include <vector>
#include <algorithm>    // untuk sort
#include <queue>       // untuk queue
#include <stack>       // untuk stack
#include <unordered_map> // untuk unordered_map
#include <string>
#include <limits>      // untuk numeric_limits

using namespace std;

// --------------------------------------------------------------------
// Struct untuk menyimpan data slot jadwal
struct SlotJadwal {
    int id;
    string tanggal; // format: YYYY-MM-DD
    string jam;     // format: HH:MM
};

// Struct untuk menyimpan data pelanggan (untuk antrean)
struct Pelanggan {
    int id;
    string nama;
};

// Struct untuk menyimpan data booking
struct Booking {
    string bookingCode;
    int pelangganId;
    SlotJadwal slot;
};

// --------------------------------------------------------------------
// Vektor untuk menampung slot jadwal (nanti bisa disort)
vector<SlotJadwal> jadwalSlots;

// Queue untuk menampung antrean pelanggan
queue<Pelanggan> antreanPelanggan;

// Hash table (unordered_map) untuk menyimpan booking code -> Booking
unordered_map<string, Booking> bookingMap;

// Stack untuk menampung booking yang dibatalkan (untuk undo)
stack<Booking> canceledBookings;

// Variabel global untuk generate booking code (sederhana)
int bookingCounter = 1;

// --------------------------------------------------------------------
// Fungsi bantu untuk membandingkan tanggal & jam secara sederhana
// Asumsi format tanggal: YYYY-MM-DD dan jam: HH:MM
bool compareSlot(const SlotJadwal &a, const SlotJadwal &b) {
    // Gabungkan tanggal dan jam jadi satu string: "YYYY-MM-DD HH:MM"
    string dateTimeA = a.tanggal + " " + a.jam;
    string dateTimeB = b.tanggal + " " + b.jam;
    // Bandingkan secara leksikografis
    return dateTimeA < dateTimeB;
}

// --------------------------------------------------------------------
// Fungsi untuk menambahkan slot jadwal baru
void tambahSlotJadwal() {
    SlotJadwal slot;
    cout << "Masukkan ID slot: ";
    cin >> slot.id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Masukkan tanggal (YYYY-MM-DD): ";
    getline(cin, slot.tanggal);

    cout << "Masukkan jam (HH:MM): ";
    getline(cin, slot.jam);

    jadwalSlots.push_back(slot);
    cout << "Slot jadwal berhasil ditambahkan.\n";
}

// --------------------------------------------------------------------
// Fungsi untuk mengurutkan slot jadwal
void urutkanJadwal() {
    sort(jadwalSlots.begin(), jadwalSlots.end(), compareSlot);
    cout << "Slot jadwal berhasil diurutkan.\n";
}

// --------------------------------------------------------------------
// Fungsi untuk menampilkan slot jadwal
void tampilkanJadwal() {
    cout << "\n=== Daftar Slot Jadwal ===\n";
    for (const auto &slot : jadwalSlots) {
        cout << "ID: " << slot.id 
             << ", Tanggal: " << slot.tanggal 
             << ", Jam: " << slot.jam << "\n";
    }
    cout << "==========================\n";
}

// --------------------------------------------------------------------
// Fungsi untuk menambahkan pelanggan ke antrean
void enqueuePelanggan() {
    Pelanggan p;
    cout << "Masukkan ID pelanggan: ";
    cin >> p.id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Masukkan nama pelanggan: ";
    getline(cin, p.nama);

    antreanPelanggan.push(p);
    cout << "Pelanggan berhasil ditambahkan ke antrean.\n";
}

// --------------------------------------------------------------------
// Fungsi untuk memproses (dequeue) pelanggan terdepan
void prosesAntrean() {
    if (antreanPelanggan.empty()) {
        cout << "Antrean kosong, tidak ada yang diproses.\n";
        return;
    }
    Pelanggan depan = antreanPelanggan.front();
    antreanPelanggan.pop();
    cout << "Memproses pelanggan ID: " << depan.id 
         << ", Nama: " << depan.nama << "\n";
}

// --------------------------------------------------------------------
// Fungsi untuk melakukan booking (asumsi pelanggan & slot sudah siap)
void lakukanBooking() {
    if (jadwalSlots.empty()) {
        cout << "Belum ada slot jadwal. Tambahkan terlebih dahulu.\n";
        return;
    }
    
    // Minta ID pelanggan (asumsi sudah diproses dari antrean)
    int pelangganId;
    cout << "Masukkan ID pelanggan yang akan booking: ";
    cin >> pelangganId;
    
    // Pilih ID slot
    int slotId;
    cout << "Masukkan ID slot yang ingin di-booking: ";
    cin >> slotId;

    // Cari slot di vektor
    SlotJadwal selectedSlot;
    bool found = false;
    for (auto &slot : jadwalSlots) {
        if (slot.id == slotId) {
            selectedSlot = slot;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Slot dengan ID tersebut tidak ditemukan.\n";
        return;
    }

    // Generate kode booking
    string code = "BK-" + to_string(bookingCounter++);
    
    // Buat struct Booking
    Booking newBooking;
    newBooking.bookingCode = code;
    newBooking.pelangganId = pelangganId;
    newBooking.slot = selectedSlot;

    // Simpan ke hash table
    bookingMap[code] = newBooking;

    cout << "Booking berhasil! Kode booking: " << code << "\n";
}

// --------------------------------------------------------------------
// Fungsi untuk menampilkan semua booking
void tampilkanBooking() {
    cout << "\n=== Daftar Booking ===\n";
    for (auto &pair : bookingMap) {
        Booking &bk = pair.second;
        cout << "Kode: " << bk.bookingCode 
             << ", PelangganID: " << bk.pelangganId
             << ", SlotID: " << bk.slot.id 
             << " (" << bk.slot.tanggal << " " << bk.slot.jam << ")\n";
    }
    cout << "======================\n";
}

// --------------------------------------------------------------------
// Fungsi untuk membatalkan booking (dimasukkan ke stack)
void batalkanBooking() {
    cout << "Masukkan kode booking yang akan dibatalkan: ";
    string code;
    cin >> code;

    // Cari di bookingMap
    auto it = bookingMap.find(code);
    if (it == bookingMap.end()) {
        cout << "Kode booking tidak ditemukan.\n";
        return;
    }

    // Ambil data booking
    Booking canceled = it->second;
    // Hapus dari bookingMap
    bookingMap.erase(it);
    // Push ke stack
    canceledBookings.push(canceled);

    cout << "Booking " << code << " berhasil dibatalkan.\n";
}

// --------------------------------------------------------------------
// Fungsi untuk undo pembatalan (pop dari stack)
void undoPembatalan() {
    if (canceledBookings.empty()) {
        cout << "Tidak ada pembatalan yang bisa di-undo.\n";
        return;
    }
    Booking lastCanceled = canceledBookings.top();
    canceledBookings.pop();

    // Kembalikan ke bookingMap
    bookingMap[lastCanceled.bookingCode] = lastCanceled;
    cout << "Booking " << lastCanceled.bookingCode 
         << " berhasil di-undo pembatalannya.\n";
}

// --------------------------------------------------------------------
// Fungsi main dengan menu sederhana
int main() {
    int pilihan;
    do {
        cout << "\n=== SISTEM PEMASARAN JASA FOTOGRAFI ===\n";
        cout << "1. Tambah Slot Jadwal\n";
        cout << "2. Urutkan Jadwal\n";
        cout << "3. Tampilkan Jadwal\n";
        cout << "4. Enqueue Pelanggan\n";
        cout << "5. Proses Pelanggan dari Antrean\n";
        cout << "6. Lakukan Booking\n";
        cout << "7. Tampilkan Semua Booking\n";
        cout << "8. Batalkan Booking\n";
        cout << "9. Undo Pembatalan Terakhir\n";
        cout << "0. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (pilihan) {
            case 1:
                tambahSlotJadwal();
                break;
            case 2:
                urutkanJadwal();
                break;
            case 3:
                tampilkanJadwal();
                break;
            case 4:
                enqueuePelanggan();
                break;
            case 5:
                prosesAntrean();
                break;
            case 6:
                lakukanBooking();
                break;
            case 7:
                tampilkanBooking();
                break;
            case 8:
                batalkanBooking();
                break;
            case 9:
                undoPembatalan();
                break;
            case 0:
                cout << "Keluar dari program.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
                break;
        }
    } while (pilihan != 0);

    return 0;
}