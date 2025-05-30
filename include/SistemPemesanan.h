#ifndef SISTEM_PEMESANAN_H
#define SISTEM_PEMESANAN_H

#include <vector>
#include <string>
#include "Booking.h"
#include "User.h"
#include "CustomStack.h"

class SistemPemesanan
{
private:
    std::string fileDatabaseBooking = "data/bookings.txt"; // Path file data booking
    std::vector<Booking> semuaDataBooking;
    int counterBooking;

    CustomStack<Booking> undoStack;

    std::string hasilkanKodeBooking();
    bool cekJadwalBentrok(const Booking &bookingBaru) const;
    bool bacaBookingDariFile();
    bool simpanBookingKeFile() const;

public:
    SistemPemesanan();

    // Parameter User* masih dibutuhkan untuk mendapatkan nama dan telepon saat booking baru
    bool prosesBookingBaru(const User *user, const std::string &strTanggal, const std::string &strMulai, const std::string &strSelesai, std::string &outKodeBooking);
    void tampilkanSemuaBooking() const;
    bool prosesBatalBooking(const std::string &kodeBooking);
    bool undoCancellation();
    bool canUndo() const;

    // New edit methods
    bool cariBookingByKode(const std::string &kodeBooking) const;
    bool editNamaPemesan(const std::string &kodeBooking, const std::string &namaBaru);
    bool editTeleponPemesan(const std::string &kodeBooking, const std::string &teleponBaru);
    bool editWaktuBooking(const std::string &kodeBooking, const std::string &tanggalBaru,
                          const std::string &waktuMulaiBaru, const std::string &waktuSelesaiBaru);
};

#endif