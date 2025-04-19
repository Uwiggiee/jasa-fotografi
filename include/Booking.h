#ifndef BOOKING_H
#define BOOKING_H

#include <string>
#include <ctime>

time_t StrDate_toTime(std::string &date);
time_t StrClock_toTime(time_t date, std::string &clock);

class Booking{
    private:
        std::string nomor_telp_user;
        time_t mulai;
        time_t selesai;
    
    public:
        Booking(std::string telp, std::string date, std::string start, std::string finish);
        void print_booking();

};
#endif