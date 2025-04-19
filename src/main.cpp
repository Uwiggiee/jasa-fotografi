#include <iostream>
#include <cstdlib> // Untuk fungsi exit()
#include <limits>  // Untuk std::numeric_limits
#include "../include/User.h"
#include "../include/Auth.h"
#include "../include/Booking.h"
// Include header files lainnya
// #include "../include/Admin.h"
// #include "../include/SistemPemesanan.h"

// Deklarasi fungsi
void handleCustomerLogin(Auth &auth);
void handleAdminLogin();
void displayMainMenu(Auth &auth);
void displayUserMenu(Auth &auth);
void cls();
void pause();

int main()
{

  Auth authSystem;

  bool isRunning = true;
  while (isRunning)
  {
    displayMainMenu(authSystem);
    // Program akan terus berjalan sampai user memilih exit
  }

  return 0;
}

void cls(){
  system("cls"); // Di Windows
}

void pause(){
  std::cout << "\nTekan Enter untuk melanjutkan...";
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  std::cin.get();
}

void displayMainMenu(Auth &auth){
  cls();
  std::cout << "====== Selamat Datang di sistem pemesanan jasa fotografi ======" << std::endl;
  std::cout << "1. Login Sebagai Pelanggan" << std::endl;
  std::cout << "2. Login Sebagai Admin" << std::endl;
  std::cout << "3. Exit" << std::endl;
  std::cout << std::endl
            << "Silahkan pilih menu: ";

  int choice;
  std::cin >> choice;

  switch (choice)
  {
  case 1:
    handleCustomerLogin(auth);
    break;
  case 2:
    handleAdminLogin();
    break;
  case 3:
    std::cout << "Terima kasih telah menggunakan sistem kami!" << std::endl;
    exit(0);
  default:
    std::cout << "Pilihan tidak valid. Silahkan coba lagi." << std::endl;
  }
  std::cout << "==============================================================" << std::endl;
}

void handleCustomerLogin(Auth &auth)
{
  std::string phone;
  std::cout << "Masukkan nomor telepon: ";
  std::cin >> phone;

  // Cek apakah user sudah terdaftar
  if (auth.findUserByPhone(phone) == nullptr)
  {
    // User belum terdaftar, minta nama
    std::string name;
    std::cout << "Nomor belum terdaftar. Masukkan nama Anda untuk membuat akun: ";
    std::cin.ignore(); // Clear buffer
    std::getline(std::cin, name);

    // Register dan login
    if (auth.loginOrRegister(phone, name))
    {
      cls();
      std::cout << "Akun baru berhasil dibuat!" << std::endl;
      pause(); 
      displayUserMenu(auth);
    }
  }
  else
  {
    // User sudah terdaftar, langsung login
    if (auth.loginOrRegister(phone))
    {
      cls();
      std::cout << "Login berhasil!" << std::endl;
      std::cout << "Selamat datang, " << auth.getCurrentUser()->getName() << "!" << std::endl;
      pause();
      displayUserMenu(auth);
    }
  }
}

void handleAdminLogin()
{
  // Implementasi login admin
  std::cout << "Handling admin login..." << std::endl;
  // Contoh: auth.loginAsAdmin();
}

void displayUserMenu(Auth &auth)
{
  cls();
  std::cout << "=== MENU USER ===" << std::endl;
  std::cout << "1. Lihat Jadwal Tersedia" << std::endl;
  std::cout << "2. Buat Booking" << std::endl;
  std::cout << "3. Logout" << std::endl;
  std::cout << "Pilihan: ";

  int choice;
  std::cin >> choice;

  // Process user selection
  switch (choice)
  {
  case 1:
    cls();
    auth.getCurrentUser()->viewAvailableSchedule();
    pause(); 
    break;
  case 2:
    cls();
    auth.getCurrentUser()->makeBooking();
    pause();
    break;
  case 3:
    std::cout << "Logout berhasil!" << std::endl;
    break;
  default:
    std::cout << "Pilihan tidak valid!" << std::endl;
    pause(); 
    break;
  }

  displayMainMenu(auth); // Kembali ke menu utama setelah selesai
}