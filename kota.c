#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "kota.h"

#define MAX_KOTA 100
int jumlah_kota = 0;
Kota A[MAX_KOTA];

void entryKota(infotype nama_kota) {
    if (jumlah_kota < MAX_KOTA) {
        strcpy(A[jumlah_kota].nama, nama_kota);
        A[jumlah_kota].q = NULL;
        jumlah_kota++;
    } else {
        printf("Kapasitas kota penuh (maksimal %d).\n", MAX_KOTA);
    }
}

void deleteKota(infotype nama_kota) {
    int index = -1;
    for (int i = 0; i < jumlah_kota; i++) {
        if (strcmp(A[i].nama, nama_kota) == 0) {
            index = i;
            break;
        }
    }
    if (index != -1) {
        // Hapus semua orang dalam linked list
        address temp = A[index].q;
        while (temp != NULL) {
            address del = temp;
            temp = temp->p;
            Dealokasi(&del);
        }

        // Geser array A
        for (int i = index; i < jumlah_kota - 1; i++) {
            A[i] = A[i + 1];
        }
        jumlah_kota--;
    } else {
        printf("Kota tidak ditemukan.\n");
    }
}

void tampilkanKota() {
    if (jumlah_kota == 0) {
        printf("Belum ada kota yang dimasukkan.\n");
        return;
    }

    for (int i = 0; i < jumlah_kota; i++) {
        printf("Kota: %s\n", A[i].nama);
        address curr = A[i].q;
        if (curr == NULL) {
            printf("  (tidak ada orang)\n");
        }
        while (curr != NULL) {
            printf("  - %s\n", curr->nama);
            curr = curr->p;
        }
    }
}

void InsertFirst(int index, infotype namaOrang) {
    if (index >= 0 && index < jumlah_kota) {
        address orangBaru;
        Alokasi(&orangBaru, namaOrang);
        if (orangBaru != NULL) {
            orangBaru->p = A[index].q;
            A[index].q = orangBaru;
        }
    }
}

void InsertLast(int index, infotype namaOrang) {
    if (index >= 0 && index < jumlah_kota) {
        address orangBaru;
        Alokasi(&orangBaru, namaOrang);
        if (orangBaru != NULL) {
            orangBaru->p = NULL;
            if (A[index].q == NULL) {
                A[index].q = orangBaru;
            } else {
                address last = A[index].q;
                while (last->p != NULL) {
                    last = last->p;
                }
                last->p = orangBaru;
            }
        }
    }
}

address SearchPrec(int index, infotype namaOrang) {
    if (index >= 0 && index < jumlah_kota) {
        address prec = NULL;
        address curr = A[index].q;
        while (curr != NULL && strcmp(curr->nama, namaOrang) != 0) {
            prec = curr;
            curr = curr->p;
        }
        return (curr != NULL) ? prec : NULL;
    }
    return NULL;
}

void InsertAfter(address prec, infotype namaOrang) {
    if (prec != NULL) {
        address orangBaru;
        Alokasi(&orangBaru, namaOrang);
        if (orangBaru != NULL) {
            orangBaru->p = prec->p;
            prec->p = orangBaru;
        }
    }
}

void PrintList(int index) {
    if (index >= 0 && index < jumlah_kota) {
        printf("Kota: %s\n", A[index].nama);
        address curr = A[index].q;
        int i = 1;
        if (curr == NULL) {
            printf("  (tidak ada orang)\n");
        }
        while (curr != NULL) {
            printf("  %d. %s\n", i++, curr->nama);
            curr = curr->p;
        }
    }
}
