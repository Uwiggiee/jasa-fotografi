#include <iostream>
#include "../include/Admin.h"

std::string Admin::getAdminPassword() const {
  return password;
}

// Implementasi makeBooking yang override dari User
void Admin::makeBooking() const {
  std::cout << "=== ADMIN: Buat Booking Baru ===" << std::endl;
  std::cout << "Fitur admin untuk membuat booking belum diimplementasikan." << std::endl;
}

void Admin::viewSchedule() {
  std::cout << "=== ADMIN: Lihat Semua Jadwal & Data Pemesan ===" << std::endl;
  std::cout << "Fitur admin untuk melihat jadwal belum diimplementasikan." << std::endl;
}

void Admin::editBooking() {
  std::cout << "=== ADMIN: Edit Booking ===" << std::endl;
  std::cout << "Fitur admin untuk edit booking belum diimplementasikan." << std::endl;
}

void Admin::removeBooking() {
  std::cout << "=== ADMIN: Hapus Booking ===" << std::endl;
  std::cout << "Fitur admin untuk hapus booking belum diimplementasikan." << std::endl;
}

void Admin::viewUsers() {
  std::cout << "=== ADMIN: Lihat Semua User ===" << std::endl;
  std::cout << "Fitur admin untuk melihat data user belum diimplementasikan." << std::endl;
}