#ifndef USER_H
#define USER_H

#include <string>

class SistemPemesanan; // Info aja: nanti ada kelas SistemPemesanan

class User
{
private:
    std::string name;
    std::string phoneNumber;

public:
    User(const std::string &namaInput, const std::string &teleponInput);
    virtual ~User() = default; // Penting buat pewarisan (Admin)

    virtual bool isAdmin() const; // Cek ini Admin atau bukan

    std::string getName() const;
    std::string getPhoneNumber() const;

    // Aksi-aksi yang bisa dilakukan User
    virtual void viewAvailableSchedule(SistemPemesanan &sp) const;
    virtual void makeBooking(SistemPemesanan &sp) const;
    virtual void cancelBooking(SistemPemesanan &sp) const;
};

#endif