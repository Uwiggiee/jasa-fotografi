#include "../include/Admin.h"
#include "../include/SistemPemesanan.h"
#include "../include/Auth.h"
#include <iostream>
#include <string>
#include <limits>

Admin::Admin(const std::string &namaInput, const std::string &teleponInput, const std::string &passwordInput)
    : User(namaInput, teleponInput), passwordAdmin(passwordInput) {} // Panggil constructor User dulu

bool Admin::isAdmin() const
{
  return true;
}

std::string Admin::getPasswordAdmin() const
{
  return passwordAdmin;
}

void Admin::makeBooking(SistemPemesanan &sp) const
{
  std::cout << "\n=== ADMIN: Buat Booking Untuk User ===" << std::endl;
  std::string namaPemesan, teleponPemesan, tanggal, waktuMulai, waktuSelesai;

  std::cout << "Nama pemesan: ";
  std::getline(std::cin, namaPemesan);
  std::cout << "Nomor telepon pemesan: ";
  std::getline(std::cin, teleponPemesan);
  std::cout << "Tanggal booking (dd/mm/yyyy): ";
  std::getline(std::cin, tanggal);
  std::cout << "Waktu mulai (hh:mm): ";
  std::getline(std::cin, waktuMulai);
  std::cout << "Waktu selesai (hh:mm): ";
  std::getline(std::cin, waktuSelesai);

  User userUntukBooking(namaPemesan, teleponPemesan); // Buat User sementara
  std::string kodeDihasilkan;

  if (sp.prosesBookingBaru(&userUntukBooking, tanggal, waktuMulai, waktuSelesai, kodeDihasilkan))
  {
    // Sukses
  }
  else
  {
    std::cout << "Admin gagal memproses booking." << std::endl;
  }
  std::cout << "====================================" << std::endl;
}

void Admin::cancelBooking(SistemPemesanan &sp) const
{
  std::cout << "\n=== ADMIN: Batalkan Booking ===" << std::endl;
  std::string kodeBooking;

  if (std::cin.peek() == '\n')
  {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
  std::cout << "Kode booking yang dibatalkan: ";
  std::getline(std::cin, kodeBooking);

  sp.prosesBatalBooking(kodeBooking);
  std::cout << "===============================" << std::endl;
}

void Admin::viewSchedule(SistemPemesanan &sp) const
{
  std::cout << "\n=== ADMIN: Lihat Semua Jadwal ===" << std::endl;
  sp.tampilkanSemuaBooking();
  std::cout << "=================================" << std::endl;
}

void Admin::editBooking([[maybe_unused]] SistemPemesanan &sp)
{
  std::cout << "\n=== ADMIN: Edit Booking ===" << std::endl;
  std::cout << "Fitur ini belum tersedia." << std::endl;
  std::cout << "===========================" << std::endl;
}

void Admin::viewUsers(Auth &sistemAuth) const
{
  std::cout << "\n=== ADMIN: Lihat User Terdaftar ===" << std::endl;
  sistemAuth.tampilkanSemuaUserPelanggan();
  std::cout << "===================================" << std::endl;
}