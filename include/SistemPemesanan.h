#ifndef SISTEM_PEMESANAN_H
#define SISTEM_PEMESANAN_H

#include <vector>
#include <string>
#include "Booking.h"
#include "User.h" 

class SistemPemesanan
{
private:
    std::string fileDatabaseBooking = "data/bookings.txt"; // Path file data booking
    std::vector<Booking> semuaDataBooking;
    int counterBooking;

    std::string hasilkanKodeBooking();
    bool cekJadwalBentrok(const Booking &bookingBaru) const;

    bool bacaBookingDariFile();       // Fungsi baru
    bool simpanBookingKeFile() const; // Fungsi baru, const karena tidak mengubah member secara logis (hanya I/O)

public:
    SistemPemesanan();

    // Parameter User* masih dibutuhkan untuk mendapatkan nama dan telepon saat booking baru
    bool prosesBookingBaru(const User *user, const std::string &strTanggal, const std::string &strMulai, const std::string &strSelesai, std::string &outKodeBooking);
    void tampilkanSemuaBooking() const;
    bool prosesBatalBooking(const std::string &kodeBooking);
};

#endif