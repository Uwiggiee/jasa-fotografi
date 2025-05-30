#include "../include/Admin.h"
#include "../include/SistemPemesanan.h"
#include "../include/Auth.h"
#include <iostream>
#include <string>
#include <limits>
#include <algorithm> //untuk std::transform
#include <cctype>    // Untuk std::tolower

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

  std::cout << "Kode booking yang dibatalkan: ";
  std::getline(std::cin, kodeBooking);

  std::transform(kodeBooking.begin(), kodeBooking.end(), kodeBooking.begin(),
                 [](unsigned char c)
                 { return std::toupper(c); });

  sp.prosesBatalBooking(kodeBooking);
  std::cout << "===============================" << std::endl;
}

void Admin::viewSchedule(SistemPemesanan &sp) const
{
  std::cout << "\n=== ADMIN: Lihat Semua Jadwal ===" << std::endl;
  sp.tampilkanSemuaBooking();
  std::cout << "=================================" << std::endl;
}

void Admin::editBooking(SistemPemesanan &sp)
{
  std::cout << "\n=== ADMIN: Edit Booking ===" << std::endl;

  // Tampilkan semua booking dulu
  std::cout << "Daftar booking yang ada:" << std::endl;
  sp.tampilkanSemuaBooking();

  std::string kodeBooking;
  std::cout << "\nMasukkan kode booking yang ingin diedit: ";
  std::getline(std::cin, kodeBooking);

  // Convert ke uppercase untuk konsistensi
  std::transform(kodeBooking.begin(), kodeBooking.end(), kodeBooking.begin(),
                 [](unsigned char c)
                 { return std::toupper(c); });

  // Cari booking berdasarkan kode
  if (!sp.cariBookingByKode(kodeBooking))
  {
    std::cout << "Error: Kode booking '" << kodeBooking << "' tidak ditemukan!" << std::endl;
    std::cout << "===========================" << std::endl;
    return;
  }

  // Menu edit options
  std::cout << "\nPilih yang ingin diedit:" << std::endl;
  std::cout << "1. Nama pemesan" << std::endl;
  std::cout << "2. Nomor telepon pemesan" << std::endl;
  std::cout << "3. Tanggal & waktu booking" << std::endl;
  std::cout << "4. Batalkan edit" << std::endl;
  std::cout << "Pilih: ";

  int pilihan;
  std::cin >> pilihan;
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  switch (pilihan)
  {
  case 1:
  {
    std::string namaBaru;
    std::cout << "Nama pemesan baru: ";
    std::getline(std::cin, namaBaru);
    if (!namaBaru.empty())
    {
      sp.editNamaPemesan(kodeBooking, namaBaru);
    }
    else
    {
      std::cout << "Nama tidak boleh kosong!" << std::endl;
    }
    break;
  }
  case 2:
  {
    std::string teleponBaru;
    std::cout << "Nomor telepon baru: ";
    std::getline(std::cin, teleponBaru);
    if (!teleponBaru.empty())
    {
      sp.editTeleponPemesan(kodeBooking, teleponBaru);
    }
    else
    {
      std::cout << "Nomor telepon tidak boleh kosong!" << std::endl;
    }
    break;
  }
  case 3:
  {
    std::string tanggalBaru, waktuMulaiBaru, waktuSelesaiBaru;
    std::cout << "Tanggal baru (dd/mm/yyyy): ";
    std::getline(std::cin, tanggalBaru);
    std::cout << "Waktu mulai baru (hh:mm): ";
    std::getline(std::cin, waktuMulaiBaru);
    std::cout << "Waktu selesai baru (hh:mm): ";
    std::getline(std::cin, waktuSelesaiBaru);

    sp.editWaktuBooking(kodeBooking, tanggalBaru, waktuMulaiBaru, waktuSelesaiBaru);
    break;
  }
  case 4:
    std::cout << "Edit dibatalkan." << std::endl;
    break;
  default:
    std::cout << "Pilihan tidak valid!" << std::endl;
    break;
  }

  std::cout << "===========================" << std::endl;
}

void Admin::viewUsers(Auth &sistemAuth) const
{
  std::cout << "\n=== ADMIN: Lihat User Terdaftar ===" << std::endl;
  sistemAuth.tampilkanSemuaUserPelanggan();
  std::cout << "===================================" << std::endl;
}