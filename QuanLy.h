#ifndef QUANLY_H
#define QUANLY_H

#include <string>
using namespace std; 

const int SO_NHOM = 29;

struct ThiSinh {
    string hoTen;
    string gioiTinh;
    string maDuThi;
    string ngaySinh;
    string queQuan;
};

struct Node {
    ThiSinh data;
    Node* next;
};

struct DanhSach {
    Node* head;
    Node* tail;
    int soLuong;
};

struct BangBam {
    DanhSach bucket[SO_NHOM];
};

void khoiTaoDanhSach(DanhSach& ds);
void khoiTaoBangBam(BangBam& bang);
Node* taoNode(const ThiSinh& ts);
void themCuoi(DanhSach& ds, const ThiSinh& ts);
int demThiSinh(const BangBam& bang);
void giaiPhongDanhSach(DanhSach& ds);
void giaiPhongBangBam(BangBam& bang);
string layTen(const string& hoTen);
string layChuDau(const string& ten);
int xacDinhNhom(const string& hoTen);	
bool themThiSinh(BangBam& bang, const ThiSinh& ts);
bool kiemTraNgaySinh(const std::string& ngaySinh);
bool docFileThiSinh(BangBam& bang, const string& tenFile);
bool luuFileThiSinh(const BangBam& bang, const string& tenFile);
bool xuatDanhSachPhong(const DanhSach dsPhong[], int soPhong, const string& tenFile);


#endif
