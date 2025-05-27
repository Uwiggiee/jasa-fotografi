#ifndef AUTH_H
#define AUTH_H

#include <string>
#include <vector>
#include "User.h"
#include "Admin.h"

class Auth
{
private:
    std::string fileDatabaseUser = "data/users.txt"; // File data user pelanggan

    std::vector<User *> daftarSemuaUserPelanggan; // Daftar user pelanggan di memori
    User *userSedangLogin;                        // Siapa yang lagi login
    bool statusSedangLogin;

    // Info Admin (disimpen di kode aja)
    const std::string ADMIN_USERNAME_DEFAULT = "admin";
    const std::string ADMIN_PASSWORD_DEFAULT = "admin123";

    bool bacaUserDariFile();
    bool simpanUserKeFile();

public:
    Auth();
    ~Auth(); // Buat hapus User* dari memori

    bool prosesLoginAtauRegistrasiUser(const std::string &telepon, const std::string &nama = "");
    bool prosesLoginAdmin(const std::string &username, const std::string &password);
    void prosesLogout();

    User *getUserSedangLogin() const;
    bool apaUserBiasaSedangLogin() const;
    bool apaAdminSedangLogin() const;

    void tampilkanSemuaUserPelanggan() const;
    User *cariUserViaTelepon(const std::string &telepon); // Dipakai di main.cpp
};

#endif