#include "../include/Auth.h"
#include <iostream>
#include <fstream> // Untuk baca/tulis file

Auth::Auth() : userSedangLogin(nullptr), statusSedangLogin(false)
{
    bacaUserDariFile(); // Coba baca data user pas program mulai
}

Auth::~Auth()
{
    // Hapus semua User pelanggan yang dibuat pakai 'new'
    for (User *userPtr : daftarSemuaUserPelanggan)
    {
        delete userPtr;
    }
    daftarSemuaUserPelanggan.clear();

    // Hapus Admin default jika ada (yang dibuat pakai 'new' pas login admin)
    if (userSedangLogin && userSedangLogin->isAdmin() && userSedangLogin->getPhoneNumber() == ADMIN_USERNAME_DEFAULT)
    {
        delete userSedangLogin;
    }
    userSedangLogin = nullptr;
}

bool Auth::bacaUserDariFile()
{
    std::ifstream fileIn(fileDatabaseUser);
    if (!fileIn.is_open())
    {
        std::cerr << "Warning Auth: File " << fileDatabaseUser << " gak ada atau gak bisa dibuka. Anggap kosong." << std::endl;
        std::ofstream fileOut(fileDatabaseUser); // Coba buat file kosongnya
        fileOut.close();
        return false;
    }

    for (User *userPtr : daftarSemuaUserPelanggan)
    { // Hapus dulu data lama di memori
        delete userPtr;
    }
    daftarSemuaUserPelanggan.clear();

    std::string baris;
    while (std::getline(fileIn, baris))
    {
        if (baris.empty() || baris[0] == '/' || baris[0] == '#')
            continue; // Abaikan baris kosong/komentar

        size_t posKoma = baris.find(',');
        if (posKoma != std::string::npos)
        {
            std::string nama = baris.substr(0, posKoma);
            std::string telepon = baris.substr(posKoma + 1);
            if (!nama.empty() && !telepon.empty())
            {
                daftarSemuaUserPelanggan.push_back(new User(nama, telepon));
            }
        }
    }
    fileIn.close();
    return true;
}

bool Auth::simpanUserKeFile()
{
    std::ofstream fileOut(fileDatabaseUser);
    if (!fileOut.is_open())
    {
        std::cerr << "Error Auth: Gak bisa nulis ke file " << fileDatabaseUser << std::endl;
        return false;
    }
    fileOut << "// Data User Pelanggan (nama,telepon)" << std::endl;
    for (const User *userPtr : daftarSemuaUserPelanggan)
    {
        if (userPtr && !userPtr->isAdmin()) // Hanya simpan user biasa
        {
            fileOut << userPtr->getName() << "," << userPtr->getPhoneNumber() << std::endl;
        }
    }
    fileOut.close();
    return true;
}

User *Auth::cariUserViaTelepon(const std::string &telepon)
{
    for (User *userPtr : daftarSemuaUserPelanggan)
    {
        if (userPtr->getPhoneNumber() == telepon)
            return userPtr;
    }
    return nullptr; // Gak ketemu
}

bool Auth::prosesLoginAtauRegistrasiUser(const std::string &telepon, const std::string &nama)
{
    User *userAda = cariUserViaTelepon(telepon);
    if (userAda) // User udah ada -> Login
    {
        userSedangLogin = userAda;
        statusSedangLogin = true;
        std::cout << "Halo lagi, " << userSedangLogin->getName() << "!" << std::endl;
        return true;
    }
    else if (!nama.empty()) // User gak ada, nama diisi -> Registrasi
    {
        if (telepon.empty())
        {
            std::cout << "Registrasi gagal: Telepon gak boleh kosong." << std::endl;
            return false;
        }
        User *userBaru = new User(nama, telepon);
        daftarSemuaUserPelanggan.push_back(userBaru);
        userSedangLogin = userBaru;
        statusSedangLogin = true;
        simpanUserKeFile(); // Langsung simpan user baru
        std::cout << "Akun untuk " << nama << " berhasil dibuat & langsung login." << std::endl;
        return true;
    }
    std::cout << "Login gagal: Nomor " << telepon << " belum daftar. Registrasi dulu ya." << std::endl;
    return false;
}

bool Auth::prosesLoginAdmin(const std::string &username, const std::string &password)
{
    if (username == ADMIN_USERNAME_DEFAULT && password == ADMIN_PASSWORD_DEFAULT)
    {
        if (userSedangLogin)
            prosesLogout(); // Logout user/admin lama dulu

        userSedangLogin = new Admin(); // Buat objek Admin baru
        statusSedangLogin = true;
        std::cout << "Login Admin (" << userSedangLogin->getName() << ") sukses!" << std::endl;
        return true;
    }
    return false;
}

void Auth::prosesLogout()
{
    if (statusSedangLogin && userSedangLogin)
    {
        std::cout << "Logout sukses: " << userSedangLogin->getName() << std::endl;
        if (userSedangLogin->isAdmin() && userSedangLogin->getPhoneNumber() == ADMIN_USERNAME_DEFAULT)
        {
            delete userSedangLogin; // Hapus Admin default dari memori
        }
    }
    userSedangLogin = nullptr;
    statusSedangLogin = false;
}

User *Auth::getUserSedangLogin() const
{
    return userSedangLogin;
}
bool Auth::apaUserBiasaSedangLogin() const
{
    return statusSedangLogin && userSedangLogin && !userSedangLogin->isAdmin();
}
bool Auth::apaAdminSedangLogin() const
{
    return statusSedangLogin && userSedangLogin && userSedangLogin->isAdmin();
}

void Auth::tampilkanSemuaUserPelanggan() const
{
    std::cout << "\n--- Daftar User Pelanggan ---" << std::endl;
    int no = 1;
    bool ada = false;
    for (const auto &userPtr : daftarSemuaUserPelanggan)
    {
        if (userPtr && !userPtr->isAdmin())
        {
            std::cout << no++ << ". " << userPtr->getName() << " (" << userPtr->getPhoneNumber() << ")" << std::endl;
            ada = true;
        }
    }
    if (!ada)
        std::cout << "Belum ada user pelanggan." << std::endl;
    std::cout << "-----------------------------" << std::endl;
}
