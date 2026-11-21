#ifndef QUANLI_H
#define QUANLI_H

#include <iostream>
using namespace std;

struct BangQuanLy {
    int dummy;
};

inline void khoiTaoBang(BangQuanLy& ds) {
    ds.dummy = 0;
}

inline void themThiSinh(BangQuanLy& ds) {
    (void)ds;
    cout << "[Tam] Goi chuc nang them thi sinh (Nguoi 1).\n";
}

inline void timKiemThiSinh(BangQuanLy& ds) {
    (void)ds;
    cout << "[Tam] Goi chuc nang tim kiem thi sinh (Nguoi 2).\n";
}

inline void sapXepDanhSach(BangQuanLy& ds) {
    (void)ds;
    cout << "[Tam] Goi chuc nang sap xep danh sach (Nguoi 3).\n";
}

inline void chiaPhongThi(BangQuanLy& ds) {
    (void)ds;
    cout << "[Tam] Goi chuc nang chia phong thi (Nguoi 4).\n";
}

inline void docFileTXT(BangQuanLy& ds) {
    (void)ds;
    cout << "[Tam] Goi chuc nang doc file TXT (Nguoi 5).\n";
}

inline void luuFileVaXuatPhong(BangQuanLy& ds) {
    (void)ds;
    cout << "[Tam] Goi chuc nang luu file TXT va xuat danh sach phong (Nguoi 5).\n";
}

inline void giaiPhongBoNho(BangQuanLy& ds) {
    (void)ds;
    cout << "[Tam] Giai phong bo nho (Nguoi 1).\n";
}

#endif
