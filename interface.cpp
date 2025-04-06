#include <iostream>
using namespace std;

int main(){
    int input;

    do {
        cout << "=== PESAN JASA FOTOGRAFI ===\n"
        << "1. Liat jadwal\n"
        << "2. Booking jadwal\n"
        << "3. undo booking\n"
        << "0. keluar\n"
        << "Pilih menu : ";

        cin >> input;
        cout << "\n";

    }while(input);
}