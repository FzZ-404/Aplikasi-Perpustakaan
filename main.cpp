#include <iostream>
#include <iomanip>
#include <string>
#include <windows.h>
using namespace std;


void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

struct Buku {
    string kode;
    string judul;
    bool dipinjam;
};


void header();
void tampilkanMenu();
void tampilkanSemuaBuku(Buku arr[], int n);
int cariBukuByKode(Buku arr[], int n, string kode);
void prosesPinjamBuku(Buku arr[], int n, string kode);
void prosesKembalikanBuku(Buku arr[], int n, string kode);
void urutkanBuku(Buku arr[], int n);
void pause();


void header() {
    system("cls");
    setColor(11);
    cout << "=====================================================\n";
    cout << "               SISTEM PERPUSTAKAAN C++              \n";
    cout << "=====================================================\n";
    setColor(7);
}


void tampilkanMenu() {
    cout << "\n";
    setColor(14);
    cout << "+-------------------------- MENU --------------------------+\n";
    setColor(7);
    cout << "  1. Tampilkan Semua Buku\n";
    cout << "  2. Pinjam Buku\n";
    cout << "  3. Kembalikan Buku\n";
    cout << "  4. Cari Buku Berdasarkan Kode\n";
    cout << "  5. Keluar\n";
    setColor(14);
    cout << "+-----------------------------------------------------------+\n";
    setColor(11);
    cout << "  Pilih menu: ";
    setColor(7);
}

void tampilkanSemuaBuku(Buku arr[], int n) {
    header();
    setColor(10);
    cout << "DAFTAR BUKU TERSEDIA\n";
    setColor(7);
    cout << "-------------------------------------------------------------\n";
    cout << left << setw(10) << "Kode" 
         << setw(30) << "Judul" 
         << "Status\n";
    cout << "-------------------------------------------------------------\n";

    for (int i = 0; i < n; i++) {
        cout << left << setw(10) << arr[i].kode
             << setw(30) << arr[i].judul;

        if (arr[i].dipinjam) {
            setColor(12);
            cout << "Dipinjam";
        } else {
            setColor(10);
            cout << "Tersedia";
        }
        setColor(7);
        cout << "\n";
    }

    cout << "-------------------------------------------------------------\n";
    pause();
}

int cariBukuByKode(Buku arr[], int n, string kode) {
    for (int i = 0; i < n; i++) {
        if (arr[i].kode == kode) return i;
    }
    return -1;
}


void prosesPinjamBuku(Buku arr[], int n, string kode) {
    header();
    int idx = cariBukuByKode(arr, n, kode);

    if (idx == -1) {
        setColor(12);
        cout << "❌ Buku tidak ditemukan!\n";
        setColor(7);
        pause();
        return;
    }

    if (arr[idx].dipinjam) {
        setColor(14);
        cout << "⚠ Buku tersebut sedang dipinjam.\n";
    } else {
        arr[idx].dipinjam = true;
        setColor(10);
        cout << "✔ Buku '" << arr[idx].judul << "' berhasil dipinjam!\n";
    }
    setColor(7);
    pause();
}


void prosesKembalikanBuku(Buku arr[], int n, string kode) {
    header();
    int idx = cariBukuByKode(arr, n, kode);

    if (idx == -1) {
        setColor(12);
        cout << "❌ Buku tidak ditemukan!\n";
        setColor(7);
        pause();
        return;
    }

    if (!arr[idx].dipinjam) {
        setColor(14);
        cout << "⚠ Buku tidak sedang dipinjam.\n";
    } else {
        arr[idx].dipinjam = false;
        setColor(10);
        cout << "✔ Buku berhasil dikembalikan!\n";
    }
    setColor(7);
    pause();
}


void urutkanBuku(Buku arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j].kode < arr[minIndex].kode) {
                minIndex = j;
            }
        }
        swap(arr[i], arr[minIndex]);
    }
}

void pause() {
    setColor(11);
    cout << "\nTekan enter untuk melanjutkan...";
    setColor(7);
    cin.ignore();
    cin.get();
}


int main() {
    Buku buku[5] = {
        {"B001", "Dasar Algoritma", false},
        {"B002", "Struktur Data", false},
        {"B003", "Matematika Diskrit", false},
        {"B004", "Pemrograman C++", true},
        {"B005", "Jaringan Komputer", false},
    };

    int n = 5;
    int pilihan;
    string kode;

    urutkanBuku(buku, n);

    do {
        header();
        tampilkanMenu();
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tampilkanSemuaBuku(buku, n);
                break;
            case 2:
                cout << "\nMasukkan kode buku: ";
                cin >> kode;
                prosesPinjamBuku(buku, n, kode);
                break;
            case 3:
                cout << "\nMasukkan kode buku: ";
                cin >> kode;
                prosesKembalikanBuku(buku, n, kode);
                break;
            case 4:
                header();
                cout << "Masukkan kode buku: ";
                cin >> kode;
                {
                    int idx = cariBukuByKode(buku, n, kode);
                    if (idx == -1) {
                        setColor(12); cout << "❌ Buku tidak ditemukan!\n";
                    } else {
                        setColor(10);
                        cout << "\n✔ Ditemukan: " << buku[idx].kode 
                             << " - " << buku[idx].judul << "\n";
                    }
                    setColor(7);
                    pause();
                }
                break;
            case 5:
                setColor(10);
                cout << "\nTerima kasih telah menggunakan aplikasi ini!\n";
                setColor(7);
                break;
            default:
                setColor(12);
                cout << "❌ Pilihan tidak valid!\n";
                setColor(7);
                pause();
        }

    } while (pilihan != 5);

    return 0;
}
