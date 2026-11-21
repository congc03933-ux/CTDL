#include <iostream>
#include <limits>
#include "quanli.h"

using namespace std;

void hienThiMenu() {
    cout << "\n================ QUAN LY THI SINH ================\n";
    cout << "1. Them ho so thi sinh\n";
    cout << "2. Tim kiem thi sinh\n";
    cout << "3. Sap xep danh sach tang dan\n";
    cout << "4. Chia phong thi\n";
    cout << "5. Doc ho so tu file TXT\n";
    cout << "6. Luu ho so ra file TXT va xuat danh sach phong\n";
    cout << "0. Thoat chuong trinh\n";
    cout << "==================================================\n";
    cout << "Nhap lua chon: ";
}

int main() {
    BangQuanLy ds;
    khoiTaoBang(ds);

    int luaChon = -1;
    do {
        hienThiMenu();
        if (!(cin >> luaChon)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Lua chon khong hop le! Vui long nhap so.\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (luaChon) {
            case 1:
                themThiSinh(ds);
                break;
            case 2:
                timKiemThiSinh(ds);
                break;
            case 3:
                sapXepDanhSach(ds);
                break;
            case 4:
                chiaPhongThi(ds);
                break;
            case 5:
                docFileTXT(ds);
                break;
            case 6:
                luuFileVaXuatPhong(ds);
                break;
            case 0:
                giaiPhongBoNho(ds);
                cout << "Da thoat chuong trinh.\n";
                break;
            default:
                cout << "Chuc nang khong ton tai! Vui long chon tu 0 den 6.\n";
                break;
        }
    } while (luaChon != 0);

    return 0;
}
