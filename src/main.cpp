#include <iostream>
#include <cstdlib> // Untuk fungsi exit()
#include <limits>  // Untuk std::numeric_limits
#include "../include/User.h"
#include "../include/Auth.h"
// Include header files lainnya
// #include "../include/Admin.h"
// #include "../include/SistemPemesanan.h"

// Deklarasi fungsi
void handleCustomerLogin(Auth &auth);
void handleAdminLogin(Auth &auth);
void displayMainMenu(Auth &auth);
void displayUserMenu(Auth &auth);
void displayAdminMenu(Auth &auth);
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

void cls()
{
  system("cls"); // Di Windows
}

void pause()
{
  std::cout << "\nTekan Enter untuk melanjutkan...";
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  std::cin.get();
}

void displayMainMenu(Auth &auth)
{
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
    handleAdminLogin(auth);
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

void handleAdminLogin(Auth &auth)
{
  std::string phone;
  std::string password;
  std::cout << "Masukkan username: ";
  std::cin >> phone;
  std::cout << "Masukkan password: ";
  std::cin >> password;

  auth.loginAdmin(phone, password);
  pause();
  displayAdminMenu(auth);
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

void displayAdminMenu(Auth &auth)
{
  if (!auth.isAdmin())
  {
    std::cout << "ANDA BUKAN ADMIN!" << std::endl;
    pause();
    displayMainMenu(auth);
    return; // Important to prevent further execution
  }

  Admin *adminUser = dynamic_cast<Admin *>(auth.getCurrentUser());
  if (!adminUser)
  {
    std::cout << "Error: Admin cast failed! Current user is of type '"
              << typeid(*auth.getCurrentUser()).name()
              << "' with name '" << auth.getCurrentUser()->getName()
              << "' and phone '" << auth.getCurrentUser()->getPhoneNumber()
              << "'. Expected type 'Admin'." << std::endl;
    pause();
    displayMainMenu(auth);
    return;
  }

  cls();
  std::cout << "=== MENU ADMIN ===" << std::endl;
  std::cout << "0. Logout" << std::endl;
  std::cout << "1. Lihat Jadwal Beserta Datanya" << std::endl;
  std::cout << "2. Buat Booking Baru" << std::endl;
  std::cout << "3. Edit Booking" << std::endl;
  std::cout << "4. Remove Booking" << std::endl;
  std::cout << "5. View Users" << std::endl;
  std::cout << "Pilihan: ";

  int choice;
  std::cin >> choice;

  // Process user selection
  switch (choice)
  {
  case 0:
    cls();
    std::cout << "Logout berhasil!" << std::endl;
    pause();
    break;
  case 1:
    adminUser->viewSchedule();
    break;
  case 2:
    cls();
    adminUser->makeBooking();
    pause();
    break;
  case 3:
    adminUser->editBooking();
    break;
  case 4:
    adminUser->removeBooking();
    break;
  case 5:
    adminUser->viewUsers();
    break;
  default:
    std::cout << "Pilihan tidak valid!" << std::endl;
    pause();
    break;
  }

  displayMainMenu(auth); // Kembali ke menu utama setelah selesai
}