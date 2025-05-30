#ifndef ADMIN_H
#define ADMIN_H

#include <string>
#include "User.h" // Admin adalah turunan dari User

// Forward declarations
class SistemPemesanan;
class Auth;

class Admin : public User // 'public User' artinya Admin mewarisi dari User
{
private:
  std::string passwordAdmin;

public:
  Admin(const std::string &namaInput = "Administrator",
        const std::string &teleponInput = "admin", // Username default admin
        const std::string &passwordInput = "admin123");

  bool isAdmin() const override; // Admin pasti true
  std::string getPasswordAdmin() const;

  // Fungsi Admin yang beda atau tambahan
  void makeBooking(SistemPemesanan &sp) const override;
  void cancelBooking(SistemPemesanan &sp) const override;
  void viewSchedule(SistemPemesanan &sp) const;
  void editBooking(SistemPemesanan &sp);
  void viewUsers(Auth &sistemAuth) const;
};

#endif