#ifndef ADMIN_H
#define ADMIN_H

#include <string>
#include "User.h"

class Admin : public User {
  private: 
    std::string password;
  public: 

    Admin(const std::string& name = "Administrator", 
          const std::string& phone = "admin", 
          const std::string& pwd = "admin123" )
          :User(name, phone), password(pwd) {}
    bool isAdmin() const override {return true;}
    std::string getAdminPassword() const;
    
    void makeBooking() const override;
    void viewSchedule(); //bedanya dengan viewavailableschedule adalah dia bisa melihat data yang mendaftar
    void editBooking();
    void removeBooking();
    void viewUsers();
};

#endif