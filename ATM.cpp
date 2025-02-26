#include <iostream>
#include <cstdlib>
#include <limits>
#include <ctime>

using namespace std;

const int PIN = 1234; // PIN ATM tetap
const int MAX_ATTEMPTS = 3;
int saldo = 2000000;

void header() {
    cout << "================================================\n"
         << "\t      ATM Sederhana\n"
         << "\t        Mesin ATM\n"
            << "\t by: Yafi Widya Putra (34)\n"
         << "\t     Dede Ichsan R (16)\n"
         << "\t    M Khoirus Zaman (28)\n"

         << "================================================\n";
}

void footer() {
    cout << "================================================\n"
         << "       Terima Kasih atas kunjungan Anda\n"
         << "\tSilahkan cek kembali uang Anda\n"
         << "dan pastikan tidak ada barang yang tertinggal\n"
         << "================================================\n";
}

void menu() {
    cout << "\n1. Tarik Tunai\n"
         << "2. Setor Tunai\n"
         << "3. Cek Saldo\n"
         << "4. Keluar\n"
         << "Pilihan Anda: ";
}

void printTimestamp() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    cout << "Waktu Transaksi: " << 1900 + ltm->tm_year << "-"
         << 1 + ltm->tm_mon << "-"
         << ltm->tm_mday << " "
         << ltm->tm_hour << ":"
         << ltm->tm_min << ":"
         << ltm->tm_sec << "\n";
}

bool validasiPIN() {
    int pin_input, attempts = 0;
    while (attempts < MAX_ATTEMPTS) {
        cout << "Masukkan PIN Anda: ";
        cin >> pin_input;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Input tidak valid! Masukkan angka.\n";
            continue;
        }
        if (pin_input == PIN) return true;
        attempts++;
        cout << "PIN salah! Percobaan tersisa: " << MAX_ATTEMPTS - attempts << "\n";
    }
    cout << "Anda telah melebihi batas percobaan. Kartu Anda diblokir!\n";
    return false;
}

void tarikTunai() {
    int tarik;
    cout << "Masukkan jumlah yang ingin ditarik (kelipatan 50.000): ";
    cin >> tarik;
    if (tarik % 50000 != 0 || tarik <= 0) {
        cout << "Jumlah harus kelipatan 50.000.\n";
    } else if (tarik > saldo) {
        cout << "Saldo tidak cukup.\n";
    } else {
        saldo -= tarik;
        cout << "Berhasil menarik Rp" << tarik << "\nSaldo tersisa: Rp" << saldo << "\n";
        printTimestamp();
    }
}

void setorTunai() {
    int setor;
    cout << "Masukkan jumlah yang ingin disetor (kelipatan 50.000): ";
    cin >> setor;
    if (setor % 50000 != 0 || setor <= 0) {
        cout << "Jumlah harus kelipatan 50.000.\n";
    } else {
        saldo += setor;
        cout << "Berhasil menyetor Rp" << setor << "\nSaldo sekarang: Rp" << saldo << "\n";
        printTimestamp();
    }
}

void cekSaldo() {
    cout << "Saldo Anda saat ini: Rp" << saldo << "\n";
    printTimestamp();
}

int main() {
    system("cls");
    header();
    if (!validasiPIN()) return 0;

    int pilihan;
    do {
        menu();
        cin >> pilihan;
        system("cls");
        header();

        switch (pilihan) {
            case 1: tarikTunai(); break;
            case 2: setorTunai(); break;
            case 3: cekSaldo(); break;
            case 4: footer(); return 0;
            default: cout << "Pilihan tidak valid!\n";
        }
    } while (true);
}

