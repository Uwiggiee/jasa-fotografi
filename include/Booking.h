#ifndef BOOKING_H
#define BOOKING_H

#include <string>
#include <ctime>

// Fungsi bantu konversi string ke waktu (tetap)
time_t ubahStringTanggalKeTimeT(const std::string &strTanggal);
time_t ubahStringJamKeTimeT(time_t tanggalDasar, const std::string &strJam);

class Booking
{
private:
    std::string pemesanNama;         // Simpan nama pemesan
    std::string pemesanNomorTelepon; // Simpan nomor telepon pemesan

    time_t waktuMulai;
    time_t waktuSelesai;
    std::string kodeBooking;
    bool statusAktif;

public:
    // Tambah default constructor
    Booking() : pemesanNama(""), pemesanNomorTelepon(""),
                waktuMulai(0), waktuSelesai(0), kodeBooking(""), statusAktif(false) {}

    // Constructor diubah untuk terima nama dan telepon pemesan
    Booking(const std::string &namaPemesanInput, const std::string &teleponPemesanInput,
            const std::string &strTanggal, const std::string &strMulai, const std::string &strSelesai);

    // Constructor tambahan untuk loading dari file (termasuk kode dan status)
    Booking(const std::string &kodeBookingInput, const std::string &namaPemesanInput, const std::string &teleponPemesanInput,
            const std::string &strTanggal, const std::string &strMulai, const std::string &strSelesai, bool aktifStatus);

    void tampilkanDetailBooking() const;

    time_t getWaktuMulai() const { return waktuMulai; }
    time_t getWaktuSelesai() const { return waktuSelesai; }
    std::string getKodeBooking() const { return kodeBooking; }
    bool isAktif() const { return statusAktif; }
    std::string getPemesanNama() const { return pemesanNama; }
    std::string getPemesanNomorTelepon() const { return pemesanNomorTelepon; }

    void setKodeBooking(const std::string &kode) { kodeBooking = kode; }
    void setStatusAktif(bool status) { statusAktif = status; }

    // New setter methods for editing
    void setPemesanNama(const std::string &nama) { pemesanNama = nama; }
    void setPemesanNomorTelepon(const std::string &telepon) { pemesanNomorTelepon = telepon; }
    void setWaktuMulai(time_t waktu) { waktuMulai = waktu; }
    void setWaktuSelesai(time_t waktu) { waktuSelesai = waktu; }
};

#endif