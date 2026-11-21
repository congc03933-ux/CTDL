#include <iostream>
#include <limits>
#include <string>
#include "QuanLy.h"
#include "ChiaPhong.h"
#include <windows.h>
using namespace std;

namespace {
    void xoaBoNhoDem() {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    void hienThiMenu() {
        cout << "\n========== QUAN LY DANH SACH THI SINH ==========\n";
        cout << "1. Them thi sinh\n";
        cout << "2. Tra cuu thong tin thi sinh\n";
        cout << "3. Hien thi danh sach thi sinh theo thu tu ten tang dan\n";
        cout << "4. Phan danh sach vao n phong thi\n";
        cout << "5. Luu tru du lieu ra file TXT\n";
        cout << "6. Doc du lieu tu file TXT (ho tro nap du lieu test)\n";
        cout << "7. Xem tong so thi sinh\n";
        cout << "0. Thoat chuong trinh\n";
        cout << "================================================\n";
        cout << "Nhap lua chon: ";
    }

    void nhapThiSinh(ThiSinh& ts) {
        cout << "Nhap ma du thi: ";
        getline(cin, ts.maDuThi);
        cout << "Nhap ho ten: ";
        getline(cin, ts.hoTen);
        cout << "Nhap gioi tinh: ";
        getline(cin, ts.gioiTinh);
        cout << "Nhap ngay sinh (dd/mm/yyyy): ";
        getline(cin, ts.ngaySinh);
        cout << "Nhap que quan: ";
        getline(cin, ts.queQuan);
    }
}

int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    BangBam bang;
    khoiTaoBangBam(bang);

    KetQuaChiaPhong kqPhong;
    khoiTaoKetQua(kqPhong);

    int luaChon = -1;
    do {
        hienThiMenu();
        if (!(cin >> luaChon)) {
            cout << "Lua chon khong hop le! Vui long nhap so.\n";
            xoaBoNhoDem();
            continue;
        }
        xoaBoNhoDem();

        switch (luaChon) {
            case 1: {
                ThiSinh ts;
                nhapThiSinh(ts);
                if (themThiSinh(bang, ts)) {
                    cout << "Them thi sinh thanh cong.\n";
                } else {
                    cout << "Them that bai (kiem tra thong tin, ngay sinh dd/mm/yyyy hoac trung ma du thi).\n";
                }
                break;
            }
            case 2: {
                cout << "Tinh nang tra cuu thong tin thi sinh chua duoc cai dat trong TraCuu.cpp.\n";
                break;
            }
            case 3: {
                cout << "Tinh nang hien thi danh sach theo thu tu ten tang dan chua duoc cai dat trong SapXep.cpp.\n";
                break;
            }
            case 4: {
                thucHienChiaPhong(bang, kqPhong);
                break;
            }
            case 5: {
                string tenFile;
                cout << "Nhap ten file TXT de luu: ";
                getline(cin, tenFile);
                luuFileThiSinh(bang, tenFile);
                break;
            }
            case 6: {
                string tenFile;
                cout << "Nhap ten file TXT can doc: ";
                getline(cin, tenFile);
                docFileThiSinh(bang, tenFile);
                break;
            }
            case 7: {
cout << "Tong so thi sinh hien tai: " << demThiSinh(bang) << "\n";
                break;
            }
            case 0: {
                cout << "Dang thoat chuong trinh...\n";
                break;
            }
            default: {
                cout << "Lua chon khong hop le! Vui long chon tu 0 den 7.\n";
                break;
            }
        }
    } while (luaChon != 0);

    giaiPhongKetQua(kqPhong);
    giaiPhongBangBam(bang);
    return 0;
}
