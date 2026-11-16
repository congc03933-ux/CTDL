#include <iostream>
#include <windows.h>
#include "QuanLy.h"
using namespace std;
//Ðay la test xoa neu can 
int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    BangBam bang;
    khoiTaoBangBam(bang);

    ThiSinh ts;

    cout << "Nhap ho ten: ";
    getline(cin, ts.hoTen);

    cout << "Nhap ma du thi: ";
    getline(cin, ts.maDuThi);

    cout << "Nhap gioi tinh: ";
    getline(cin, ts.gioiTinh);

    cout << "Nhap ngay sinh: ";
    getline(cin, ts.ngaySinh);

    cout << "Nhap que quan: ";
    getline(cin, ts.queQuan);

    if (themThiSinh(bang, ts)) {
        cout << "Them thanh cong.\n";
        cout << "Chi so nhom: "
             << xacDinhNhom(ts.hoTen) << '\n';
    } else {
        cout << "Khong them duoc: thong tin khong hop le hoac trung ma.\n";
    }

    cout << "Tong so thi sinh: " << demThiSinh(bang) << '\n';

    cout << "Thu them lai cung ho so:\n";

    if (themThiSinh(bang, ts)) {
        cout << "Them thanh cong.\n";
    } else {
        cout << "Khong them duoc: thong tin khong hop le hoac trung ma.\n";
    }

    cout << "Tong so thi sinh: " << demThiSinh(bang) << '\n';

    giaiPhongBangBam(bang);
    return 0;
}
