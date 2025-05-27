#include "../include/Booking.h"
#include <iostream>
#include <iomanip>
#include <sstream>

// Ubah "dd/mm/yyyy" jadi time_t
time_t ubahStringTanggalKeTimeT(const std::string &strTanggal)
{
    struct tm detailWaktu = {}; // struct tm buat simpan detail tanggal & waktu
    int hari, bulan, tahun;
    char slash1, slash2;

    std::istringstream parser(strTanggal); // Alat buat "baca" string
    if (!(parser >> hari >> slash1 >> bulan >> slash2 >> tahun && slash1 == '/' && slash2 == '/'))
    {
        return static_cast<time_t>(-1); // Format salah, balikin error
    }

    detailWaktu.tm_mday = hari;
    detailWaktu.tm_mon = bulan - 1;     // Bulan di tm itu 0-11
    detailWaktu.tm_year = tahun - 1900; // Tahun di tm dihitung dari 1900

    return mktime(&detailWaktu); // Konversi struct tm ke time_t
}

// Ubah "hh:mm" dan tanggal (time_t) jadi time_t lengkap
time_t ubahStringJamKeTimeT(time_t tanggalDasar, const std::string &strJam)
{
    if (tanggalDasar == static_cast<time_t>(-1))
        return static_cast<time_t>(-1); // Kalau tanggalnya udah error, ikut error

    struct tm detailWaktu = {};
    int jam, menit;
    char colon;

    std::istringstream parser(strJam);
    if (!(parser >> jam >> colon >> menit && colon == ':'))
    {
        return static_cast<time_t>(-1); // Format jam salah
    }

    struct tm *infoTanggal = localtime(&tanggalDasar); // Ambil detail dari tanggalDasar
    if (!infoTanggal)
        return static_cast<time_t>(-1); // Gagal ambil info tanggal

    detailWaktu = *infoTanggal; // Salin info tanggal, bulan, tahun
    detailWaktu.tm_hour = jam;
    detailWaktu.tm_min = menit;
    detailWaktu.tm_sec = 0; // Detik set ke 0

    return mktime(&detailWaktu);
}

// Constructor untuk booking baru
Booking::Booking(const std::string &namaPemesanInput, const std::string &teleponPemesanInput,
                 const std::string &strTanggal, const std::string &strMulai, const std::string &strSelesai)
    : pemesanNama(namaPemesanInput), pemesanNomorTelepon(teleponPemesanInput), statusAktif(true)
{
    time_t tanggalKonversi = ubahStringTanggalKeTimeT(strTanggal);
    waktuMulai = ubahStringJamKeTimeT(tanggalKonversi, strMulai);
    waktuSelesai = ubahStringJamKeTimeT(tanggalKonversi, strSelesai);
    // Kode booking akan di-set oleh SistemPemesanan
}

// Constructor untuk loading dari file
Booking::Booking(const std::string &kodeBookingInput, const std::string &namaPemesanInput, const std::string &teleponPemesanInput,
                 const std::string &strTanggal, const std::string &strMulai, const std::string &strSelesai, bool aktifStatus)
    : pemesanNama(namaPemesanInput), 
      pemesanNomorTelepon(teleponPemesanInput),
      kodeBooking(kodeBookingInput),
      statusAktif(aktifStatus)
{
    time_t tanggalKonversi = ubahStringTanggalKeTimeT(strTanggal);
    waktuMulai = ubahStringJamKeTimeT(tanggalKonversi, strMulai);   
    waktuSelesai = ubahStringJamKeTimeT(tanggalKonversi, strSelesai);
}

void Booking::tampilkanDetailBooking() const
{
    std::cout << "Pemesan: " << pemesanNama << " (" << pemesanNomorTelepon << ")" << std::endl;

    if (waktuMulai == static_cast<time_t>(-1) || waktuSelesai == static_cast<time_t>(-1))
    {
        std::cout << "Waktu  : Data waktu tidak valid." << std::endl;
    }
    else
    {
        struct tm *mulai_tm = localtime(&waktuMulai);
        struct tm *selesai_tm = localtime(&waktuSelesai);
        if (mulai_tm && selesai_tm)
        {
            std::cout << "Waktu  : " << std::put_time(mulai_tm, "%d %b %Y | %H:%M")
                      << " - " << std::put_time(selesai_tm, "%H:%M") << std::endl;
        }
        else
        {
            std::cout << "Waktu  : Gagal format waktu." << std::endl;
        }
    }
    std::cout << "Kode   : " << kodeBooking << (statusAktif ? " (Aktif)" : " (Dibatalkan)") << std::endl;
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