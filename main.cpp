#include <iostream>
#include <string>
using namespace std;


struct Buku {
    string kode;
    string judul;
    bool dipinjam; 
};


void tampilkanSemuaBuku(Buku arr[], int n);
int cariBukuByKode(Buku arr[], int n, string kode);
void prosesPinjamBuku(Buku arr[], int n, string kode);
void prosesKembalikanBuku(Buku arr[], int n, string kode);
void urutkanBuku(Buku arr[], int n);
void tampilkanMenu();


void tampilkanSemuaBuku(Buku arr[], int n) {
    cout << "\n=== DATA BUKU ===\n";
    for (int i = 0; i < n; i++) {
        cout << i+1 << ". " << arr[i].kode << " - " << arr[i].judul;
        cout << " [" << (arr[i].dipinjam ? "Dipinjam" : "Tersedia") << "]\n";
    }
}


int cariBukuByKode(Buku arr[], int n, string kode) {
    for (int i = 0; i < n; i++) {
        if (arr[i].kode == kode) {
            return i;
        }
    }
    return -1;
}


void prosesPinjamBuku(Buku arr[], int n, string kode) {
    int idx = cariBukuByKode(arr, n, kode);

    if (idx == -1) {
        cout << "❌ Buku dengan kode " << kode << " tidak ditemukan.\n";
        return;
    }

    if (arr[idx].dipinjam) {
        cout << "⚠️ Buku '" << arr[idx].judul << "' sedang dipinjam.\n";
    } else {
        arr[idx].dipinjam = true;
        cout << "✔️ Buku '" << arr[idx].judul << "' berhasil dipinjam.\n";
    }
}


void prosesKembalikanBuku(Buku arr[], int n, string kode) {
    int idx = cariBukuByKode(arr, n, kode);

    if (idx == -1) {
        cout << "❌ Buku tidak ditemukan.\n";
        return;
    }

    if (!arr[idx].dipinjam) {
        cout << "⚠️ Buku '" << arr[idx].judul 
             << "' tidak sedang dipinjam.\n";
    } else {
        arr[idx].dipinjam = false;
        cout << "✔️ Buku '" << arr[idx].judul 
             << "' berhasil dikembalikan.\n";
    }
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


void tampilkanMenu() {
    cout << "\n==== MENU PERPUSTAKAAN ====\n";
    cout << "1. Tampilkan Semua Buku\n";
    cout << "2. Pinjam Buku\n";
    cout << "3. Kembalikan Buku\n";
    cout << "4. Cari Buku Berdasarkan Kode\n";
    cout << "5. Keluar\n";
    cout << "Pilih menu: ";
}


int main() {
    const int n = 3;
    Buku arr[n] = {
        {"B001", "Dasar Algoritma", false},
        {"B002", "Struktur Data", false},
        {"B003", "Matematika Diskrit", false}
    };

    int pilihan;
    string kode;

    // urutkan terlebih dahulu
    urutkanBuku(arr, n);

    do {
        tampilkanMenu();
        cin >> pilihan;

        switch(pilihan) {
            case 1:
                urutkanBuku(arr, n);
                tampilkanSemuaBuku(arr, n);
                break;

            case 2:
                cout << "Masukkan kode buku: ";
                cin >> kode;
                prosesPinjamBuku(arr, n, kode);
                break;

            case 3:
                cout << "Masukkan kode buku: ";
                cin >> kode;
                prosesKembalikanBuku(arr, n, kode);
                break;

            case 4:
                cout << "Masukkan kode buku: ";
                cin >> kode;
                {
                    int idx = cariBukuByKode(arr, n, kode);
                    if (idx == -1)
                        cout << "❌ Buku tidak ditemukan.\n";
                    else {
                        cout << "✔️ Ditemukan: " 
                             << arr[idx].kode 
                             << " - " << arr[idx].judul << "\n";
                    }
                }
                break;

            case 5:
                cout << "Keluar...\n";
                break;

            default:
                cout << "⛔ Pilihan tidak valid!\n";
        }

    } while(pilihan != 5);

    return 0;
}
