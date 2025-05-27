// Di src/User.cpp
#include "../include/User.h"
#include "../include/SistemPemesanan.h"
#include <iostream>
#include <string>
#include <limits> // Buat std::cin.ignore

User::User(const std::string &namaInput, const std::string &teleponInput)
    : name(namaInput), phoneNumber(teleponInput) {}

std::string User::getName() const
{
    return name;
}

std::string User::getPhoneNumber() const
{
    return phoneNumber;
}

// Tambahkan definisi ini
bool User::isAdmin() const
{
    return false; // User biasa bukan admin
}

void User::viewAvailableSchedule(SistemPemesanan &sp) const
{
    std::cout << "\n=== Jadwal Booking Tersedia ===" << std::endl;
    sp.tampilkanSemuaBooking(); // Minta SistemPemesanan nampilin jadwal
    std::cout << "===============================" << std::endl;
}

void User::makeBooking(SistemPemesanan &sp) const
{
    std::cout << "\n=== Buat Booking Baru ===" << std::endl;
    std::string tanggal, waktuMulai, waktuSelesai;

    // Bersihin sisa 'Enter' dari input sebelumnya, biar getline gak error
    if (std::cin.peek() == '\n')
    {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "Tanggal booking (dd/mm/yyyy): ";
    std::getline(std::cin, tanggal);
    std::cout << "Waktu mulai (hh:mm): ";
    std::getline(std::cin, waktuMulai);
    std::cout << "Waktu selesai (hh:mm): ";
    std::getline(std::cin, waktuSelesai);

    std::string kodeDihasilkan;
    // 'this' artinya objek User yang lagi manggil fungsi ini
    if (sp.prosesBookingBaru(this, tanggal, waktuMulai, waktuSelesai, kodeDihasilkan))
    {
        // Pesan sukses/gagal diurus SistemPemesanan
    }
    else
    {

        std::cout << "Maaf, booking gagal diproses dari sisi User." << std::endl;
    }
    std::cout << "=========================" << std::endl;
}

void User::cancelBooking(SistemPemesanan &sp) const
{
    std::cout << "\n=== Batalkan Booking ===" << std::endl;
    std::string kodeBooking;

    if (std::cin.peek() == '\n')
    {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "Kode booking yang mau dibatalkan: ";
    std::getline(std::cin, kodeBooking);

    sp.prosesBatalBooking(kodeBooking); // Pesan sukses/gagal diurus SistemPemesanan
    std::cout << "========================" << std::endl;
}
