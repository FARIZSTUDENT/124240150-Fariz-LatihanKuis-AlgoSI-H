#include <iostream>
#include <fstream>
#include <cstring> // Untuk manipulasi string

using namespace std;

struct Buku {
    int id;
    char judul[50];
    char penulis[50];
    int stok;
};

// Fungsi login admin
bool login() {
    char nama_pengguna[20], kata_sandi[10];

    while (true) {
        cout << "Masukkan nama pengguna: ";
        cin >> nama_pengguna;
        cout << "Masukkan kata sandi: ";
        cin >> kata_sandi;

        if (strcmp(nama_pengguna, "farizz") == 0 && strcmp(kata_sandi, "006") == 0) {
            cout << "Login berhasil!\n";
            return true;
        } else {
            cout << "Login gagal! Coba lagi.\n";
        }
    }
}

// Fungsi untuk kembali ke menu utama
bool kembaliKeMenu() {
    char pilihan;
    cout << "Kembali ke menu utama? (Y/N): ";
    cin >> pilihan;
    return (pilihan == 'N' || pilihan == 'n'); // Jika N/n, tetap di menu saat ini
}

// Tambah buku ke dalam file
void tambahBuku() {
    do {
        ofstream file("data.dat", ios::app | ios::binary);
        Buku buku;

        cout << "Masukkan ID Buku: ";
        cin >> buku.id;
        cin.ignore();
        cout << "Masukkan Judul Buku: ";
        cin.getline(buku.judul, 50);
        cout << "Masukkan Penulis Buku: ";
        cin.getline(buku.penulis, 50);
        cout << "Masukkan Stok Buku: ";
        cin >> buku.stok;

        file.write(reinterpret_cast<char*>(&buku), sizeof(Buku));
        file.close();
        cout << "Buku berhasil ditambahkan!\n";
    } while (!kembaliKeMenu());
}

// Menampilkan daftar buku
void tampilkanBuku() {
    do {
        ifstream file("data.dat", ios::binary);
        Buku buku;
        cout << "Daftar Buku:\n";
        while (file.read(reinterpret_cast<char*>(&buku), sizeof(Buku))) {
            cout << "ID: " << buku.id << " | Judul: " << buku.judul << " | Penulis: " << buku.penulis << " | Stok: " << buku.stok << endl;
        }
        file.close();
    } while (!kembaliKeMenu());
}

// Mencari buku berdasarkan judul
void cariBuku() {
    do {
        ifstream file("data.dat", ios::binary);
        Buku buku;
        char kata_kunci[50];
        bool ditemukan = false;

        cin.ignore();
        cout << "Masukkan judul buku yang dicari: ";
        cin.getline(kata_kunci, 50);

        while (file.read(reinterpret_cast<char*>(&buku), sizeof(Buku))) {
            if (strstr(buku.judul, kata_kunci)) { // Mencocokkan substring dengan `strstr`
                cout << "Buku ditemukan: ID: " << buku.id << " | Judul: " << buku.judul << " | Penulis: " << buku.penulis << " | Stok: " << buku.stok << endl;
                ditemukan = true;
            }
        }

        if (!ditemukan) {
            cout << "Buku tidak ditemukan!\n";
        }

        file.close();
    } while (!kembaliKeMenu());
}

// Menghapus buku berdasarkan ID
void hapusBuku() {
    do {
        ifstream file("data.dat", ios::binary);
        ofstream file_sementara("temp.dat", ios::binary);
        Buku buku;
        int id_hapus;
        bool ditemukan = false;

        cout << "Masukkan ID buku yang ingin dihapus: ";
        cin >> id_hapus;

        while (file.read(reinterpret_cast<char*>(&buku), sizeof(Buku))) {
            if (buku.id != id_hapus) {
                file_sementara.write(reinterpret_cast<char*>(&buku), sizeof(Buku));
            } else {
                ditemukan = true;
            }
        }

        file.close();
        file_sementara.close();

        remove("data.dat");
        rename("temp.dat", "data.dat");

        if (ditemukan) {
            cout << "Buku berhasil dihapus!\n";
        } else {
            cout << "ID buku tidak ditemukan!\n";
        }
    } while (!kembaliKeMenu());
}

int main() {
    if (!login()) return 0;

    int pilihan;
    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Tambah Buku\n";
        cout << "2. Tampilkan Buku\n";
        cout << "3. Cari Buku\n";
        cout << "4. Hapus Buku\n";
        cout << "5. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: tambahBuku(); break;
            case 2: tampilkanBuku(); break;
            case 3: cariBuku(); break;
            case 4: hapusBuku(); break;
            case 5: cout << "Keluar dari program.\n"; return 0;
            default: cout << "Pilihan tidak valid!\n";
        }
    }
}
