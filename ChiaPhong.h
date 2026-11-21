#ifndef CHIAPHONG_H
#define CHIAPHONG_H

#include "QuanLy.h"
#include <ostream>

struct PhongNode {
    const ThiSinh* ts;
    int nhom;
    PhongNode* next;
};

struct Phong {
    PhongNode* head;
    PhongNode* tail;
    int size;
};

struct KetQuaChiaPhong {
    int soPhong;
    Phong* phong;
    int soCapTrung;
};

void khoiTaoKetQua(KetQuaChiaPhong& kq);
void giaiPhongKetQua(KetQuaChiaPhong& kq);

void themVaoPhong(Phong& ph, const ThiSinh* ts, int nhom);
int demCapTrung(const KetQuaChiaPhong& kq);

bool chiaPhong(const BangBam& bang, int soPhong, KetQuaChiaPhong& kq);
void xuatDanhSachPhong(std::ostream& os, const KetQuaChiaPhong& kq);
int nhapSoPhong();
void thucHienChiaPhong(const BangBam& bang, KetQuaChiaPhong& kq);

#endif
