#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct KTP {
    string nik;
    string nama;
    string tempatLahir;
    string tanggalLahir;
    string jenisKelamin;
    string alamat;
    string rt;
    string rw;
    string kelurahan;
    string kecamatan;
    string agama;
    string statusPerkawinan;
    string pekerjaan;
    string kewarganegaraan;
    string berlakuHingga;
};

struct Pelanggan {
    string nik;
    string nama;
    string waktuKedatangan;
    int jam;
    int menit;
};

struct Barang {
    string kodeItem;
    string namaItem;
    string tanggalMasuk;
};

struct NodeBarang {
    Barang data;
    NodeBarang* next;
};

struct NodePelanggan {
    Pelanggan data;
    NodePelanggan* next;
};

NodeBarang* headBarang = NULL;
NodePelanggan* headPelanggan = NULL;

void tambahDataKTP(KTP* daftarKTP, int& jumlahKTP) {
    cout << "\n--- Masukkan Data KTP ---\n";
    KTP ktp;
    cout << "NIK: ";
    cin >> ktp.nik;
    cin.ignore();
    cout << "Nama: ";
    getline(cin, ktp.nama);
    cout << "Tempat Lahir: ";
    getline(cin, ktp.tempatLahir);
    cout << "Tanggal Lahir: ";
    getline(cin, ktp.tanggalLahir);
    cout << "Jenis Kelamin: ";
    getline(cin, ktp.jenisKelamin);
    cout << "Alamat: ";
    getline(cin, ktp.alamat);
    cout << "RT: ";
    cin >> ktp.rt;
    cout << "RW: ";
    cin >> ktp.rw;
    cin.ignore();
    cout << "Kelurahan: ";
    getline(cin, ktp.kelurahan);
    cout << "Kecamatan: ";
    getline(cin, ktp.kecamatan);
    cout << "Agama: ";
    getline(cin, ktp.agama);
    cout << "Status Perkawinan: ";
    getline(cin, ktp.statusPerkawinan);
    cout << "Pekerjaan: ";
    getline(cin, ktp.pekerjaan);
    cout << "Kewarganegaraan: ";
    getline(cin, ktp.kewarganegaraan);
    cout << "Berlaku Hingga: ";
    getline(cin, ktp.berlakuHingga);

    daftarKTP[jumlahKTP++] = ktp;
    cout << "\nData KTP berhasil ditambahkan.\n";
}

void loginAdmin(KTP* daftarKTP, int jumlahKTP) {
    string nik, nama;
    bool loginBerhasil = false;
    while (!loginBerhasil) {
        cout << "\n--- Login Admin ---\n";
        cout << "NIK: ";
        cin >> nik;
        cin.ignore();
        cout << "Nama: ";
        getline(cin, nama);

        for (int i = 0; i < jumlahKTP; i++) {
            if (daftarKTP[i].nik == nik && daftarKTP[i].nama == nama) {
                cout << "Login berhasil. Selamat datang, " << nama << "!\n";
                loginBerhasil = true;
                break;
            }
        }
        if (!loginBerhasil) {
            cout << "Login gagal. Silakan coba lagi.\n";
        }
    }
}

void tambahBarang() {
    cout << "\n--- Tambah Barang ke Gudang ---\n";
    Barang barang;
    cout << "Kode Barang: ";
    cin >> barang.kodeItem;
    cin.ignore();
    cout << "Nama Barang: ";
    getline(cin, barang.namaItem);
    cout << "Tanggal Masuk: ";
    getline(cin, barang.tanggalMasuk);

    NodeBarang* newNode = new NodeBarang;
    newNode->data = barang;
    newNode->next = headBarang;
    headBarang = newNode;

    cout << "Barang berhasil ditambahkan ke gudang.\n";
}

void tampilBarang() {
    cout << "\n--- Daftar Barang di Gudang ---\n";
    NodeBarang* current = headBarang;
    if (!current) {
        cout << "Gudang kosong.\n";
        return;
    }
    while (current) {
        cout << "Kode: " << current->data.kodeItem << "\n";
        cout << "Nama: " << current->data.namaItem << "\n";
        cout << "Tanggal Masuk: " << current->data.tanggalMasuk << "\n\n";
        current = current->next;
    }
}

void tambahPelanggan() {
    cout << "\n--- Tambah Pelanggan ke Antrian ---\n";
    Pelanggan pelanggan;
    cout << "NIK: ";
    cin >> pelanggan.nik;
    cin.ignore();
    cout << "Nama: ";
    getline(cin, pelanggan.nama);
    cout << "Waktu Kedatangan (HH:MM): ";
    getline(cin, pelanggan.waktuKedatangan);

    NodePelanggan* newNode = new NodePelanggan;
    newNode->data = pelanggan;
    newNode->next = NULL;

    if (!headPelanggan) {
        headPelanggan = newNode;
    } else {
        NodePelanggan* current = headPelanggan;
        while (current->next) {
            current = current->next;
        }
        current->next = newNode;
    }
    cout << "Pelanggan berhasil ditambahkan ke antrian.\n";
}

void tampilPelanggan() {
    cout << "\n--- Daftar Antrian Pelanggan ---\n";
    NodePelanggan* current = headPelanggan;
    if (!current) {
        cout << "Antrian kosong.\n";
        return;
    }
    while (current) {
        cout << "NIK: " << current->data.nik << "\n";
        cout << "Nama: " << current->data.nama << "\n";
        cout << "Waktu Kedatangan: " << current->data.waktuKedatangan << "\n\n";
        current = current->next;
    }
}

void transaksiPenjualan() {
    if (!headBarang || !headPelanggan) {
        cout << "\nTidak dapat melakukan transaksi. Barang atau pelanggan kosong.\n";
        return;
    }

    NodeBarang* barangNode = headBarang;
    NodePelanggan* pelangganNode = headPelanggan;

    cout << "\n--- Transaksi Penjualan ---\n";
    cout << "Pelanggan: " << pelangganNode->data.nama << "\n";
    cout << "Barang: " << barangNode->data.namaItem << "\n";

    headBarang = headBarang->next;
    headPelanggan = headPelanggan->next;

    delete barangNode;
    delete pelangganNode;

    cout << "Transaksi berhasil dilakukan.\n";
}

int main() {
    KTP* daftarKTP = new KTP[100];
    int jumlahKTP = 0;

    // Proses tambah data KTP otomatis
    tambahDataKTP(daftarKTP, jumlahKTP);

    // Proses login admin otomatis
    loginAdmin(daftarKTP, jumlahKTP);

    int pilihan;
    do {
        cout << "\n--- Menu Utama ---\n";
        cout << "1. Tambah Barang\n";
        cout << "2. Tampilkan Barang\n";
        cout << "3. Tambah Pelanggan\n";
        cout << "4. Tampilkan Pelanggan\n";
        cout << "5. Transaksi Penjualan\n";
        cout << "6. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            case 1:
                tambahBarang();
                break;
            case 2:
                tampilBarang();
                break;
            case 3:
                tambahPelanggan();
                break;
            case 4:
                tampilPelanggan();
                break;
            case 5:
                transaksiPenjualan();
                break;
            case 6:
                cout << "Keluar dari sistem.\n";
                // Keluar dari program
                delete[] daftarKTP;
                return 0;
            default:
                cout << "Pilihan tidak valid.\n";
                break;
        }
    } while (true);

    return 0;
}

