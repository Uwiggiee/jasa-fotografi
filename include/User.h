#ifndef USER_H
#define USER_H

#include <string>

class User {
private:
    std::string name;
    std::string phoneNumber;
    
public:
    User(const std::string& name, const std::string& phone);
    virtual bool isAdmin() const {return false;}

    std::string getName() const;
    std::string getPhoneNumber() const;
    
    void viewAvailableSchedule() const;
    virtual void makeBooking() const;   

};

#endif