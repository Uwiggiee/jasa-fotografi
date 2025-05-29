#include "../include/SistemPemesanan.h"
#include <iostream>
#include <fstream> // Untuk baca/tulis file
#include <iomanip>
#include <sstream>
#include <algorithm> // Untuk std::max

SistemPemesanan::SistemPemesanan() : counterBooking(0)
{
    bacaBookingDariFile(); // Baca data booking pas program mulai
}

// Fungsi baca data booking dari file
bool SistemPemesanan::bacaBookingDariFile()
{
    std::ifstream fileIn(fileDatabaseBooking);
    if (!fileIn.is_open())
    {
        std::cerr << "Warning SistemPemesanan: File " << fileDatabaseBooking << " gak ada atau gak bisa dibuka. Anggap kosong." << std::endl;
        // Coba buat file kosongnya jika tidak ada
        std::ofstream fileOut(fileDatabaseBooking);
        fileOut.close();
        return false;
    }

    semuaDataBooking.clear(); // Kosongkan dulu data di memori
    std::string baris;
    int maxKodeNum = 0; // Untuk update counterBooking

    while (std::getline(fileIn, baris))
    {
        if (baris.empty() || baris[0] == '/' || baris[0] == '#') // Abaikan baris kosong/komentar
            continue;

        std::stringstream ss(baris);
        std::string item;
        std::vector<std::string> dataBooking;

        while (std::getline(ss, item, ',')) // Pisahkan data berdasarkan koma
        {
            dataBooking.push_back(item);
        }

        if (dataBooking.size() == 7) // Format: kode,telp,nama,tgl,mulai,selesai,status
        {
            std::string kode = dataBooking[0];
            std::string telp = dataBooking[1];
            std::string nama = dataBooking[2];
            std::string tgl = dataBooking[3];
            std::string mulai = dataBooking[4];
            std::string selesai = dataBooking[5];
            bool aktif = (dataBooking[6] == "1");

            semuaDataBooking.emplace_back(kode, nama, telp, tgl, mulai, selesai, aktif);

            // Update counterBooking dari kode yang ada
            if (kode.rfind("B-", 0) == 0 && kode.length() > 2)
            {
                try
                {
                    int kodeNum = std::stoi(kode.substr(2));
                    if (kodeNum > maxKodeNum)
                    {
                        maxKodeNum = kodeNum;
                    }
                }
                catch (const std::invalid_argument &ia)
                {
                    std::cerr << "Peringatan: Format nomor kode booking tidak valid di file: " << kode << std::endl;
                }
                catch (const std::out_of_range &oor)
                {
                    std::cerr << "Peringatan: Nomor kode booking terlalu besar di file: " << kode << std::endl;
                }
            }
        }
        else
        {
            std::cerr << "Peringatan SistemPemesanan: Format baris data booking salah di file: " << baris << std::endl;
        }
    }
    fileIn.close();
    counterBooking = maxKodeNum; // Set counter ke nomor terbesar yang ditemukan
    return true;
}

// Fungsi simpan data booking ke file
bool SistemPemesanan::simpanBookingKeFile() const
{
    std::ofstream fileOut(fileDatabaseBooking);
    if (!fileOut.is_open())
    {
        std::cerr << "Error SistemPemesanan: Gak bisa nulis ke file " << fileDatabaseBooking << std::endl;
        return false;
    }

    fileOut << "// Data Booking (kode,teleponPemesan,namaPemesan,tgl_dd/mm/yyyy,mulai_hh:mm,selesai_hh:mm,statusAktif_1atau0)" << std::endl;
    for (const auto &booking : semuaDataBooking)
    {
        time_t waktuMulai_t = booking.getWaktuMulai(); 
        time_t waktuSelesai_t = booking.getWaktuSelesai();

        struct tm *tm_mulai = nullptr;
        if (waktuMulai_t != static_cast<time_t>(-1))
        { // Hanya panggil localtime jika waktunya valid
            tm_mulai = localtime(&waktuMulai_t);
        }

        struct tm *tm_selesai = nullptr;
        if (waktuSelesai_t != static_cast<time_t>(-1))
        { // Hanya panggil localtime jika waktunya valid
            tm_selesai = localtime(&waktuSelesai_t);
        }

        std::string tanggal_str = "00/00/0000"; // Default jika ada masalah
        std::string mulai_str = "00:00";
        std::string selesai_str = "00:00";

        if (tm_mulai) // Pastikan tm_mulai tidak null sebelum diakses
        {
            std::ostringstream oss_tgl;
            oss_tgl << std::setfill('0') << std::setw(2) << tm_mulai->tm_mday << "/"
                    << std::setfill('0') << std::setw(2) << (tm_mulai->tm_mon + 1) << "/"
                    << (tm_mulai->tm_year + 1900);
            tanggal_str = oss_tgl.str();

            std::ostringstream oss_mulai;
            oss_mulai << std::setfill('0') << std::setw(2) << tm_mulai->tm_hour << ":"
                      << std::setfill('0') << std::setw(2) << tm_mulai->tm_min;
            mulai_str = oss_mulai.str();
        }

        if (tm_selesai) // Pastikan tm_selesai tidak null
        {
            std::ostringstream oss_selesai;
            oss_selesai << std::setfill('0') << std::setw(2) << tm_selesai->tm_hour << ":"
                        << std::setfill('0') << std::setw(2) << tm_selesai->tm_min;
            selesai_str = oss_selesai.str();
        }
        // Baru kita tulis ke file
        fileOut << booking.getKodeBooking() << ","
                << booking.getPemesanNomorTelepon() << ","
                << booking.getPemesanNama() << ","
                << tanggal_str << ","
                << mulai_str << ","
                << selesai_str << ","
                << (booking.isAktif() ? "1" : "0") << std::endl;
    }
    fileOut.close();
    return true;
}

std::string SistemPemesanan::hasilkanKodeBooking()
{
    std::ostringstream ss;
    ss << "B-" << std::setfill('0') << std::setw(3) << ++counterBooking;
    return ss.str();
}

bool SistemPemesanan::cekJadwalBentrok(const Booking &bookingBaru) const
{
    for (const auto &bookingLama : semuaDataBooking)
    {
        if (bookingLama.isAktif())
        {
            if (bookingBaru.getWaktuMulai() < bookingLama.getWaktuSelesai() &&
                bookingBaru.getWaktuSelesai() > bookingLama.getWaktuMulai())
            {
                return true;
            }
        }
    }
    return false;
}

bool SistemPemesanan::prosesBookingBaru(const User *user, const std::string &strTanggal, const std::string &strMulai, const std::string &strSelesai, std::string &outKodeBooking)
{
    if (!user)
    {
        std::cerr << "Error Sistem: User tidak ada." << std::endl;
        outKodeBooking = "GAGAL_USER_KOSONG";
        return false;
    }

    // Gunakan constructor Booking yang baru
    Booking bookingDibuat(user->getName(), user->getPhoneNumber(), strTanggal, strMulai, strSelesai);

    if (bookingDibuat.getWaktuMulai() == static_cast<time_t>(-1) || bookingDibuat.getWaktuSelesai() == static_cast<time_t>(-1))
    {
        std::cout << "Error Sistem: Format tanggal/waktu salah." << std::endl;
        outKodeBooking = "GAGAL_FORMAT_WAKTU";
        return false;
    }
    if (bookingDibuat.getWaktuSelesai() <= bookingDibuat.getWaktuMulai())
    {
        std::cout << "Error Sistem: Waktu selesai harus setelah mulai." << std::endl;
        outKodeBooking = "GAGAL_WAKTU_ANEH";
        return false;
    }
    if (cekJadwalBentrok(bookingDibuat))
    {
        std::cout << "Error Sistem: Jadwal sudah terisi." << std::endl;
        outKodeBooking = "GAGAL_BENTROK";
        return false;
    }

    outKodeBooking = hasilkanKodeBooking();
    bookingDibuat.setKodeBooking(outKodeBooking); // Set kode booking setelah dihasilkan
    semuaDataBooking.push_back(bookingDibuat);

    std::cout << "Booking untuk " << user->getName() << " berhasil! Kode: " << outKodeBooking << std::endl;
    simpanBookingKeFile(); // Simpan ke file setelah booking baru
    return true;
}

void SistemPemesanan::tampilkanSemuaBooking() const
{
    if (semuaDataBooking.empty())
    {
        std::cout << "Info: Belum ada booking sama sekali." << std::endl;
        return;
    }
    std::cout << "\n=== Daftar Semua Booking di Sistem ===" << std::endl;
    for (const auto &booking : semuaDataBooking)
    {
        booking.tampilkanDetailBooking();
        std::cout << "------------------------------------" << std::endl;
    }
}

bool SistemPemesanan::prosesBatalBooking(const std::string &kodeBookingInput)
{
    bool ditemukanDanDiubah = false;
    for (auto &booking : semuaDataBooking)
    {
        if (booking.getKodeBooking() == kodeBookingInput)
        {
            if (booking.isAktif())
            {
                undoStack.push(booking);
                booking.setStatusAktif(false);
                std::cout << "Sistem: Booking " << kodeBookingInput << " dibatalkan." << std::endl;
                ditemukanDanDiubah = true;
                break;
            }
            else
            {
                std::cout << "Info Sistem: Booking " << kodeBookingInput << " sudah batal." << std::endl;
                return false; 
            }
        }
    }

    if (ditemukanDanDiubah)
    {
        simpanBookingKeFile(); 
        return true;
    }
    else
    {
        std::cout << "Error Sistem: Kode booking " << kodeBookingInput << " tidak ketemu." << std::endl;
        return false;
    }
}

bool SistemPemesanan::undoCancellation() {
    if(undoStack.isEmpty()) {
        std::cout << "Tidak ada pembatalan yang bisa di-undo." << std::endl;
        return false;
    }

    // Ambil booking terakhir yang dibatalkan (di paling atas stack)
    Booking restoredBooking = undoStack.top();
    undoStack.pop();

    // Cari booking di vector dan restore
    for (auto &booking : semuaDataBooking) {
        if(booking.getKodeBooking() == restoredBooking.getKodeBooking()) {
            booking.setStatusAktif(true);                  // Restoring
            std::cout << "Undo berhasil! Booking " << restoredBooking.getKodeBooking()
                      << " dikembalikan." << std::endl;
            simpanBookingKeFile();
            return true;
        }
    }
    
    std::cout << "Error: Booking tidak ditemukan untuk di-restore." << std::endl;
    return false;
}

bool SistemPemesanan::canUndo() const {
    return !undoStack.isEmpty();
}