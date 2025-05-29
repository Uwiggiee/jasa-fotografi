#include <iostream>
#include <cstdlib> // Untuk system("cls") atau system("clear")
#include <limits>  // Untuk std::numeric_limits
#include "../include/User.h"
#include "../include/Auth.h"
#include "../include/Admin.h"
#include "../include/SistemPemesanan.h"

// Deklarasi fungsi-fungsi menu
void menuLoginPelanggan(Auth &auth, [[maybe_unused]] SistemPemesanan &sp);
void menuLoginAdmin(Auth &auth, [[maybe_unused]] SistemPemesanan &sp);
void menuUtama(Auth &auth, SistemPemesanan &sp, bool &lanjutJalan);
void menuUserBiasa(Auth &auth, SistemPemesanan &sp);
void menuAdminKhusus(Auth &auth, SistemPemesanan &sp);
void bersihkanLayar();
void pause();

int main()
{
  Auth sistemAuth;
  SistemPemesanan sistemBooking;
  bool lanjutJalan = true;

  while (lanjutJalan)
  {
    if (!sistemAuth.getUserSedangLogin()) // Belum ada yang login
    {
      menuUtama(sistemAuth, sistemBooking, lanjutJalan);
    }
    else // Sudah ada yang login
    {
      if (sistemAuth.apaAdminSedangLogin())
      {
        menuAdminKhusus(sistemAuth, sistemBooking);
      }
      else
      {
        menuUserBiasa(sistemAuth, sistemBooking);
      }
    }
  }
  return 0;
}

void bersihkanLayar()
{
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

void pause()
{
  std::cout << "\nTekan Enter...";
  std::cin.clear();                                                   // Bersihkan error flag kalau ada
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Abaikan sisa input
}

void menuUtama(Auth &auth, SistemPemesanan &sp, bool &lanjutJalan)
{
  bersihkanLayar();
  std::cout << "====== Sistem Booking Foto ======" << std::endl;
  std::cout << "1. Login/Daftar Pelanggan" << std::endl;
  std::cout << "2. Login Admin" << std::endl;
  std::cout << "3. Keluar" << std::endl;
  std::cout << "\nPilih: ";

  int pilihan;
  std::cin >> pilihan;

  if (std::cin.fail()) // Kalau input bukan angka
  {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    pilihan = 0; // Anggap pilihan salah
  }
  else
  {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Bersihkan sisa 'Enter'
  }

  switch (pilihan)
  {
  case 1:
    menuLoginPelanggan(auth, sp);
    break;
  case 2:
    menuLoginAdmin(auth, sp);
    break;
  case 3:
    std::cout << "Makasih udah pake sistem ini!" << std::endl;
    lanjutJalan = false;
    break;
  default:
    std::cout << "Pilihan salah." << std::endl;
    pause();
    break;
  }
}

void menuLoginPelanggan(Auth &auth, [[maybe_unused]] SistemPemesanan &sp)
{
  bersihkanLayar();
  std::string telepon, nama;
  std::cout << "Nomor Telepon: ";
  std::getline(std::cin, telepon);

  if (!auth.cariUserViaTelepon(telepon)) // Belum terdaftar -> registrasi
  {
    std::cout << "Nomor belum ada. Daftar dulu ya." << std::endl;
    std::cout << "Nama Lengkap: ";
    std::getline(std::cin, nama);
    auth.prosesLoginAtauRegistrasiUser(telepon, nama);
  }
  else // Sudah terdaftar -> login
  {
    auth.prosesLoginAtauRegistrasiUser(telepon);
  }
  pause();
}

void menuLoginAdmin(Auth &auth, [[maybe_unused]] SistemPemesanan &sp)
{
  bersihkanLayar();
  std::string username, password;
  std::cout << "Username Admin: ";
  std::getline(std::cin, username);
  std::cout << "Password Admin: ";
  std::getline(std::cin, password);

  if (!auth.prosesLoginAdmin(username, password))
  {
    std::cout << "Username atau password Admin salah." << std::endl;
  }
  pause();
}

void menuUserBiasa(Auth &auth, SistemPemesanan &sp)
{
  bersihkanLayar();
  User *userAktif = auth.getUserSedangLogin();
  if (!userAktif)
    return; // Harusnya gak mungkin, tapi jaga-jaga

  std::cout << "=== MENU PELANGGAN (" << userAktif->getName() << ") ===" << std::endl;
  std::cout << "1. Lihat Jadwal" << std::endl;
  std::cout << "2. Buat Booking" << std::endl;
  std::cout << "3. Batalkan Booking" << std::endl;
  std::cout << "4. Undo Pembatalan";
  if (!sp.canUndo())
  {
    std::cout << " (Tidak tersedia)";
  }
  std::cout << std::endl;
  std::cout << "5. Logout" << std::endl;

  std::cout << "\nPilih: ";

  int pilihan;
  std::cin >> pilihan;
  if (std::cin.fail())
  { /* ... handle error ... */
    pilihan = 0;
  }
  else
  {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }

  switch (pilihan)
  {
  case 1:
    bersihkanLayar();
    userAktif->viewAvailableSchedule(sp);
    break;
  case 2:
    bersihkanLayar();
    userAktif->makeBooking(sp);
    break;
  case 3:
    bersihkanLayar();
    userAktif->cancelBooking(sp);
    break;
  case 4:
    bersihkanLayar();
    std::cout << "=== Undo Pembatalan Booking ===" << std::endl;
    sp.undoCancellation();
    break;
  case 5:
    auth.prosesLogout();
    break;
  default:
    std::cout << "Pilihan salah." << std::endl;
    break;
  }
  pause();
}

void menuAdminKhusus(Auth &auth, SistemPemesanan &sp)
{
  bersihkanLayar();
  Admin *adminAktif = static_cast<Admin *>(auth.getUserSedangLogin());
  if (!adminAktif)
    return;

  std::cout << "=== MENU ADMIN (" << adminAktif->getName() << ") ===" << std::endl;
  std::cout << "1. Lihat Semua Jadwal" << std::endl;
  std::cout << "2. Buat Booking (untuk User)" << std::endl;
  std::cout << "3. Batalkan Booking (via Kode)" << std::endl;
  std::cout << "4. Undo Pembatalan";
  if (!sp.canUndo())
  {
    std::cout << " (Tidak tersedia)";
  }
  std::cout << std::endl;
  std::cout << "5. Lihat User Pelanggan" << std::endl;
  std::cout << "6. Logout" << std::endl;
  std::cout << "\nPilih: ";

  int pilihan;
  std::cin >> pilihan;
  if (std::cin.fail())
  { /* ... handle error ... */
    pilihan = 0;
  }
  else
  {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }

  switch (pilihan)
  {
  case 1:
    bersihkanLayar();
    adminAktif->viewSchedule(sp);
    break;
  case 2:
    bersihkanLayar();
    adminAktif->makeBooking(sp);
    break;
  case 3:
    bersihkanLayar();
    adminAktif->cancelBooking(sp);
    break;
  case 4:
    bersihkanLayar();
    std::cout << "=== ADMIN: Undo Pembatalan Booking ===" << std::endl;
    sp.undoCancellation();
    break;
  case 5:
    bersihkanLayar();
    adminAktif->viewUsers(auth);
    break;
  case 6:
    auth.prosesLogout();
    break;
  default:
    std::cout << "Pilihan salah." << std::endl;
    break;
  }
  pause();
}