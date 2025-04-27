#include "../include/Auth.h"
#include <iostream>
#include <fstream>
#include <sstream>

Auth::Auth()
{
    currentUser = nullptr;
    isLoggedIn = false;

    // Load users dari database
    if (!loadUsersFromFile())
    {
       std::cerr << "Error: Failed to load user database." << std::endl;
    }
}

Auth::~Auth()
{
    // Bersihkan memory
    for (auto &user : users)
    {
        delete user;
    }
    users.clear();
}

bool Auth::loadUsersFromFile()
{
    std::ifstream file(userDbPath);
    if (!file.is_open())
    {
        std::cerr << "Error: Cannot open user database file." << std::endl;
        return false;
    }

    for (auto &user : users)
    {
        delete user; // Hapus user yang ada di memory
    }
    users.clear(); // Kosongkan vector users

    // Format file: name,phone
    std::string line;
    while (std::getline(file, line))
    {
        if (line.empty() || line[0] == '#')
            continue; // Skip empty lines and comments

        // Parse CSV (name,phone)
        size_t commaPos = line.find(',');
        if (commaPos != std::string::npos)
        {
            std::string name = line.substr(0, commaPos);
            std::string phone = line.substr(commaPos + 1);

            // Buat user baru
            User *user = new User(name, phone);
            users.push_back(user);
        }
    }

    file.close();
    std::cout << "User database loaded successfully." << std::endl;
    return true;
}

bool Auth::saveUsersToFile()
{
    std::ofstream file(userDbPath);
    if (!file.is_open())
    {
        std::cerr << "Error: Cannot open user database file for writing." << std::endl;
        return false;
    }

    file << "// User database - Format: name,phone" << std::endl;
    for (auto &user : users)
    {
        if (user->getPhoneNumber() != ADMIN_PHONE)
        { 
            file << user->getName() << "," << user->getPhoneNumber() << std::endl;
        }
    }

    file.close();
    std::cout << "User database saved successfully." << std::endl;
    return true;
}

bool Auth::loginOrRegister(const std::string &phone, const std::string &name)
{
    // Coba cari user berdasarkan nomor telepon
    User *user = findUserByPhone(phone);

    if (user != nullptr)
    {
        // User ditemukan, langsung login
        currentUser = user;
        isLoggedIn = true;
        std::cout << "Selamat datang kembali, " << user->getName() << "!" << std::endl;
        return true;
    }
    else if (!name.empty())
    {
        // User tidak ditemukan tapi nama disediakan, buat user baru
        User *newUser = new User(name, phone);
        users.push_back(newUser);
        currentUser = newUser;
        isLoggedIn = true;

        // Simpan perubahan database
        saveUsersToFile();

        std::cout << "Akun baru dibuat: " << name << " (" << phone << ")" << std::endl;
        return true;
    }

    // User tidak ditemukan dan nama tidak disediakan
    std::cout << "Nomor telepon " << phone << " belum terdaftar." << std::endl;
    return false;
}

bool Auth::loginAdmin(const std::string &phone, const std::string &password)
{
    if (phone == ADMIN_PHONE && password == ADMIN_PASSWORD)
    {
        // Login as admin (simplified version)
        currentUser = new Admin();
        isLoggedIn = true;
        std::cout << "Login admin berhasil!" << std::endl;
        return true;
    }
    return false;
}

User *Auth::getCurrentUser() const
{
    return currentUser;
}

bool Auth::isUser() const
{
    return isLoggedIn && currentUser != nullptr;
}

bool Auth::isAdmin() const
{
    return isLoggedIn && currentUser != nullptr &&
           currentUser->isAdmin();
}

User *Auth::findUserByPhone(const std::string &phone)
{
    for (auto &user : users)
    {
        if (user->getPhoneNumber() == phone)
        {
            return user;
        }
    }
    return nullptr;
}
