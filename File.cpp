#include "QuanLy.h"
#include <iostream>
#include <fstream>

using namespace std;

// Chuong 2
string xoaKhoangTrang(string s) {
    int dau = 0;
    while (dau < s.length() && (s[dau] == ' ' || s[dau] == '\t' || s[dau] == '\r' || s[dau] == '\n')) {
        dau++;
    }
    int cuoi = s.length() - 1;
    while (cuoi >= dau && (s[cuoi] == ' ' || s[cuoi] == '\t' || s[cuoi] == '\r' || s[cuoi] == '\n')) {
        cuoi--;
    }
    if (dau > cuoi) {
        return "";
    }
    return s.substr(dau, cuoi - dau + 1);
}

bool docFileThiSinh(BangBam& bang, const string& tenFile) {
    ifstream fin(tenFile.c_str());
    if (!fin.is_open()) {
        cout << "Khong mo duoc file " << tenFile << "!\n";
        return false;
    }

    if (demThiSinh(bang) > 0) {
        cout << "Danh sach hien tai dang co " << demThiSinh(bang) << " thi sinh.\n";
        cout << "Doc file se thay the danh sach hien co. Ban co chac chan khong? (y/n): ";
        string chon;
        getline(cin, chon);
        if (chon != "y" && chon != "Y") {
            cout << "Da huy doc file.\n";
            fin.close();
            return false;
        }
    }

    // Chuong 4 & 6:
    giaiPhongBangBam(bang);

    string dong;
    int soDong = 0;
    int soThanhCong = 0;
    int soLoi = 0;

    while (getline(fin, dong)) {
        soDong++;
        dong = xoaKhoangTrang(dong);
        if (dong == "") {
            continue;
        }

        // Chuong 1
        string truong[5];
        int chiSo = 0;
        string tam = "";
        bool duTruong = true;

        // Chuong 2
        for (int i = 0; i < dong.length(); i++) {
            if (dong[i] == '|') {
                if (chiSo >= 4) {
                    duTruong = false;
                    break;
                }
                truong[chiSo] = xoaKhoangTrang(tam);
                chiSo++;
                tam = "";
            } else {
                tam += dong[i];
            }
        }
        if (duTruong && chiSo == 4) {
            truong[4] = xoaKhoangTrang(tam);
        } else {
            duTruong = false;
        }

        if (!duTruong) {
            cout << "Dong " << soDong << " sai dinh dang (phai co du 5 truong)!\n";
            soLoi++;
            continue;
        }

        // Chuong 1
        ThiSinh ts;
        ts.maDuThi = truong[0];
        ts.hoTen = truong[1];
        ts.gioiTinh = truong[2];
        ts.ngaySinh = truong[3];
        ts.queQuan = truong[4];

        // Chuong 6 
        if (themThiSinh(bang, ts)) {
            soThanhCong++;
        } else {
            cout << "Dong " << soDong << " bi loi du lieu hoac trung ma (" << ts.maDuThi << ")!\n";
            soLoi++;
        }
    }

    fin.close();
    cout << "Doc file xong: Thanh cong " << soThanhCong << " ho so, loi " << soLoi << " dong.\n";
    return true;
}

bool luuFileThiSinh(const BangBam& bang, const string& tenFile) {
    ofstream fout(tenFile.c_str());
    if (!fout.is_open()) {
        cout << "Khong tao duoc file " << tenFile << "!\n";
        return false;
    }

    int dem = 0;
    // Chuong 6:
    for (int i = 0; i < SO_NHOM; i++) {
        Node* p = bang.bucket[i].head;
        while (p != nullptr) {
            fout << p->data.maDuThi << "|"
                 << p->data.hoTen << "|"
                 << p->data.gioiTinh << "|"
                 << p->data.ngaySinh << "|"
                 << p->data.queQuan << "\n";
            dem++;
            p = p->next;
        }
    }

    fout.close();
    cout << "Da luu " << dem << " thi sinh ra file " << tenFile << ".\n";
    return true;
}

// Chuong 1
bool xuatDanhSachPhong(const DanhSach dsPhong[], int soPhong, const string& tenFile) {
    if (dsPhong == nullptr || soPhong <= 0) {
        cout << "Chua co danh sach phong de xuat!\n";
        return false;
    }

    ofstream fout(tenFile.c_str());
    if (!fout.is_open()) {
        cout << "Khong mo duoc file " << tenFile << "!\n";
        return false;
    }

    fout << "DANH SACH PHAN PHONG THI\n";
    for (int i = 0; i < soPhong; i++) {
        fout << "\n--- Phong " << (i + 1) << " (Si so: " << dsPhong[i].soLuong << ") ---\n";
        if (dsPhong[i].head == nullptr) {
            fout << "Phong trong\n";
            continue;
        }

        int stt = 1;
        // Chuong 4
        Node* p = dsPhong[i].head;
        while (p != nullptr) {
            fout << stt << ". "
                 << p->data.maDuThi << " | "
                 << p->data.hoTen << " | "
                 << p->data.gioiTinh << " | "
                 << p->data.ngaySinh << " | "
                 << p->data.queQuan << "\n";
            stt++;
            p = p->next;
        }
    }

    fout.close();
    cout << "Da xuat danh sach phong ra file " << tenFile << ".\n";
    return true;
}
