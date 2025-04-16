// Di include/User.h
#ifndef USER_H
#define USER_H

#include <string>

class User {
private:
    std::string name;
    std::string phoneNumber;
    
public:
    // Constructor
    User(const std::string& name, const std::string& phone);
    
    // Getters
    std::string getName() const;
    std::string getPhoneNumber() const;
    
    // User operations
    void viewAvailableSchedule() const;
    void makeBooking() const;

};

#endif