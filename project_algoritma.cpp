#include <iostream>
using namespace std;

struct Node {
    int nomorAntrian;
    string nama;
    string layanan;
    Node* next;
};

Node* head = NULL;
Node* tail = NULL;

void tambahAntrian() {
    Node* baru = new Node;

    cout << "\n=== Tambah Antrian ===" << endl;

    cout << "Nomor Antrian : ";
    cin >> baru->nomorAntrian;
    cin.ignore();

    cout << "Nama Nasabah  : ";
    getline(cin, baru->nama);

    cout << "Jenis Layanan : ";
    getline(cin, baru->layanan);

    baru->next = NULL;

    if (head == NULL) {
        head = tail = baru;
    } else {
        tail->next = baru;
        tail = baru;
    }

    cout << "\nAntrian berhasil ditambahkan!\n";
}

void tampilAntrian() {
    Node* bantu = head;

    cout << "\n=== Daftar Antrian ===" << endl;

    if (head == NULL) {
        cout << "Antrian masih kosong.\n";
    } else {
        while (bantu != NULL) {
            cout << "Nomor Antrian : " << bantu->nomorAntrian << endl;
            cout << "Nama Nasabah  : " << bantu->nama << endl;
            cout << "Jenis Layanan : " << bantu->layanan << endl;
            cout << "-------------------------" << endl;

            bantu = bantu->next;
        }
    }
}

int main() {
    int pilih;

    do {
        cout << "\n===== SISTEM ANTRIAN BANK PROJECT ALGORITMA =====" << endl;
        cout << "1. Tambah Antrian" << endl;
        cout << "2. Tampilkan Antrian" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilih Menu : ";
        cin >> pilih;

        switch (pilih) {
            case 1:
                tambahAntrian();
                break;

            case 2:
                tampilAntrian();
                break;

            case 0:
                cout << "\nProgram selesai.\n";
                break;

            default:
                cout << "\nMenu tidak tersedia.\n";
        }

    } while (pilih != 0);

    return 0;
}
