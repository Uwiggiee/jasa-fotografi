#include "../include/Booking.h"
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

time_t StrDate_toTime(string &date){
    tm date_timestamp = {};
    int day, mon, year;
    char slash1, slash2;

    istringstream ss(date);
    ss >> day >> slash1 >> mon >> slash2 >> year;

    date_timestamp.tm_mday = day;
    date_timestamp.tm_mon = mon-1;
    date_timestamp.tm_year = year-1900;

    return mktime(&date_timestamp);
}

time_t StrClock_toTime(time_t date, string &clock){
    tm clock_timestamp = {};
    int hour, min;
    char slash;

    istringstream ss(clock);
    ss >> hour >> slash >> min;
    
    tm* dt = localtime(&date);
    clock_timestamp.tm_mday = dt->tm_mday;
    clock_timestamp.tm_mon = dt->tm_mon;
    clock_timestamp.tm_year = dt->tm_year;
    clock_timestamp.tm_hour = hour;
    clock_timestamp.tm_min = min;

    time_t ct = mktime(&clock_timestamp);
    return ( ct );
}

Booking::Booking(string telp, string date, string start, string finish){
    nomor_telp_user = telp;

    time_t date_time = StrDate_toTime(date);
    mulai = StrClock_toTime(date_time, start);
    selesai = StrClock_toTime(date_time, finish);
}

void Booking::print_booking(){
    tm* dt = localtime(&mulai);
    cout << put_time(dt, "%d %b %Y | %H:%M - ");
    dt = localtime(&selesai);
    cout << put_time(dt, "%H:%M\n");
}

// int main(){
//     string telp;
//     string tanggal;
//     string start;
//     string finish;

//     cout << "masukkan no telp : ";
//     cin >> telp;

//     cout << "masukkan tanggal mulai (dd/mm/yyyy) : ";
//     cin >> tanggal;
    
//     cout << "masukkan waktu mulai (hh:mm) : ";
//     cin >> start;
    
//     cout << "masukkan waktu selesai (hh:mm) : ";
//     cin >> finish;

//     Booking pesan(telp, tanggal, start, finish);
//     pesan.print_booking();
// }