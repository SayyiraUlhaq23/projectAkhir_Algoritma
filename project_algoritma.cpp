#include <iostream>
#include <fstream>
using namespace std;

struct Node {
    int nomorAntrian;
    string nama;
    string layanan;
    Node* prev;
    Node* next;
};

Node* head = NULL;
Node* tail = NULL;

void simpanKeFile() {

    ofstream file("antrian.txt");

    Node* bantu = head;

    while (bantu != NULL) {

        file << bantu->nomorAntrian << endl;
        file << bantu->nama << endl;
        file << bantu->layanan << endl;

        bantu = bantu->next;
    }

    file.close();
}

void bacaFile() {

    ifstream file("antrian.txt");

    if (!file.is_open()) {
        return;
    }

    while (!file.eof()) {

        Node* baru = new Node;

        file >> baru->nomorAntrian;
        file.ignore();

        getline(file, baru->nama);
        getline(file, baru->layanan);

        if (file.fail()) {
            delete baru;
            break;
        }

		if (head == NULL) {

			head = tail = baru;

		} else {

			baru->prev = tail;
			tail->next = baru;
			tail = baru;
		}
    }

    file.close();
}

bool cekNomorAntrian(int nomor) {

    Node* bantu = head;

    while (bantu != NULL) {

        if (bantu->nomorAntrian == nomor) {
            return true;
        }

        bantu = bantu->next;
    }

    return false;
}

void tambahAntrian() {

    Node* baru = new Node;

    int pilihanLayanan;

    cout << "\n=== Tambah Antrian ===" << endl;

    cout << "Nomor Antrian : ";
    cin >> baru->nomorAntrian;

    if (cekNomorAntrian(baru->nomorAntrian)) {

        cout << "\nNomor antrian sudah ada!\n";

        delete baru;
        return;
    }

    cin.ignore();

    cout << "Nama Nasabah  : ";
    getline(cin, baru->nama);

    cout << "\n=== Jenis Layanan ===" << endl;
    cout << "1. Transfer" << endl;
    cout << "2. Setor Tunai" << endl;
    cout << "3. Tarik Tunai" << endl;
    cout << "4. Pembukaan Rekening" << endl;
    cout << "Pilih Layanan : ";
    cin >> pilihanLayanan;

    switch (pilihanLayanan) {

        case 1:
            baru->layanan = "Transfer";
            break;

        case 2:
            baru->layanan = "Setor Tunai";
            break;

        case 3:
            baru->layanan = "Tarik Tunai";
            break;

        case 4:
            baru->layanan = "Pembukaan Rekening";
            break;

        default:
            baru->layanan = "Layanan Lain";
    }

    baru->prev = NULL;
    baru->next = NULL;

    if (head == NULL) {

        head = tail = baru;

    } else {

        baru->prev = tail;
        tail->next = baru;
        tail = baru;
    }

    simpanKeFile();

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

void cariAntrian() {

    Node* bantu = head;
    int cari;
    bool ditemukan = false;

    cout << "\n=== Cari Antrian ===" << endl;
    cout << "Masukkan Nomor Antrian : ";
    cin >> cari;

    while (bantu != NULL) {

        if (bantu->nomorAntrian == cari) {

            cout << "\nData Ditemukan!\n";
            cout << "Nomor Antrian : " << bantu->nomorAntrian << endl;
            cout << "Nama Nasabah  : " << bantu->nama << endl;
            cout << "Jenis Layanan : " << bantu->layanan << endl;

            ditemukan = true;
            break;
        }

        bantu = bantu->next;
    }

    if (!ditemukan) {
        cout << "\nData tidak ditemukan.\n";
    }
}

void sortingAntrian() {

    if (head == NULL) {

        cout << "\nAntrian masih kosong.\n";
        return;
    }

    bool tukar;
    Node* bantu;
    Node* akhir = NULL;

    do {

        tukar = false;
        bantu = head;

        while (bantu->next != akhir) {

            if (bantu->nomorAntrian > bantu->next->nomorAntrian) {

                swap(bantu->nomorAntrian, bantu->next->nomorAntrian);
                swap(bantu->nama, bantu->next->nama);
                swap(bantu->layanan, bantu->next->layanan);

                tukar = true;
            }

            bantu = bantu->next;
        }

        akhir = bantu;

    } while (tukar);

    simpanKeFile();

    cout << "\nData berhasil diurutkan menggunakan Bubble Sort!\n";
}

void tukarData(Node* a, Node* b) {

    swap(a->nomorAntrian, b->nomorAntrian);
    swap(a->nama, b->nama);
    swap(a->layanan, b->layanan);
}

Node* partition(Node* low, Node* high) {

    int pivot = high->nomorAntrian;

    Node* i = low;
    Node* j = low;

    while (j != high) {

        if (j->nomorAntrian < pivot) {

            tukarData(i, j);
            i = i->next;
        }

        j = j->next;
    }

    tukarData(i, high);

    return i;
}

void quickSortRekursif(Node* low, Node* high) {

    if (low != NULL && high != NULL && low != high && low != high->next) {

        Node* pivot = partition(low, high);

        Node* temp = low;
        Node* sebelumPivot = NULL;

        while (temp != pivot) {

            sebelumPivot = temp;
            temp = temp->next;
        }

        quickSortRekursif(low, sebelumPivot);
        quickSortRekursif(pivot->next, high);
    }
}

void quickSortAntrian() {

    if (head == NULL) {

        cout << "\nAntrian masih kosong.\n";
        return;
    }

    quickSortRekursif(head, tail);

    simpanKeFile();

    cout << "\nData berhasil diurutkan menggunakan Quick Sort!\n";
}

int main() {

    bacaFile();

    int pilih;

    do {

			cout << "\n===== SISTEM ANTRIAN BANK PROJECT ALGORITMA =====" << endl;
			cout << "1. Tambah Antrian" << endl;
			cout << "2. Tampilkan Antrian" << endl;
			cout << "3. Cari Antrian" << endl;
			cout << "4. Bubble Sort" << endl;
			cout << "5. Quick Sort" << endl;
			cout << "6. Keluar" << endl;
			cout << "Pilih Menu : ";
			cin >> pilih;

			switch (pilih) {

				case 1:
					tambahAntrian();
					break;

				case 2:
					tampilAntrian();
					break;

				case 3:
					cariAntrian();
					break;

				case 4:
					sortingAntrian();
					break;

				case 5:
					quickSortAntrian();
					break;

				case 6:
					cout << "\nProgram selesai.\n";
					break;

				default:
					cout << "\nMenu tidak tersedia.\n";
			}

    } while (pilih != 6);

    return 0;
}
