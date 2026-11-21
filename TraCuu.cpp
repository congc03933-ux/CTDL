#include "QuanLy.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
#include <utility>

using namespace std;

namespace {
    void xoaBoNhoDemTraCuu() {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    string chuanHoaKhoangTrang(const string& s) {
        string kq;
        bool dangKhoangTrang = true;
        for (size_t i = 0; i < s.size(); ++i) {
            if (s[i] == ' ' || s[i] == '\t' || s[i] == '\r' || s[i] == '\n') {
                if (!dangKhoangTrang) {
                    kq += ' ';
                    dangKhoangTrang = true;
                }
            } else {
                kq += s[i];
                dangKhoangTrang = false;
            }
        }
        if (!kq.empty() && kq.back() == ' ') kq.pop_back();
        return kq;
    }

    void thayTheTatCa(string& s, const string& tu, const string& thanh) {
        size_t pos = 0;
        while ((pos = s.find(tu, pos)) != string::npos) {
            s.replace(pos, tu.length(), thanh);
            pos += thanh.length();
        }
    }

    // Chuyển về chữ thường và bỏ toàn bộ dấu tiếng Việt (hỗ trợ nhập không dấu tìm có dấu)
    string boToanBoDauVaThuong(string s) {
        for (size_t i = 0; i < s.size(); ++i) {
            if (s[i] >= 'A' && s[i] <= 'Z') {
                s[i] = static_cast<char>(s[i] - 'A' + 'a');
            }
        }

        const pair<string, string> bangMap[] = {
            {"À","a"},{"Á","a"},{"Ả","a"},{"Ã","a"},{"Ạ","a"},
            {"à","a"},{"á","a"},{"ả","a"},{"ã","a"},{"ạ","a"},
            {"Ă","a"},{"Ằ","a"},{"Ắ","a"},{"Ẳ","a"},{"Ẵ","a"},{"Ặ","a"},
            {"ă","a"},{"ằ","a"},{"ắ","a"},{"ẳ","a"},{"ẵ","a"},{"ặ","a"},
            {"Â","a"},{"Ầ","a"},{"Ấ","a"},{"Ẩ","a"},{"Ẫ","a"},{"Ậ","a"},
            {"â","a"},{"ầ","a"},{"ấ","a"},{"ẩ","a"},{"ẫ","a"},{"ậ","a"},
            {"Đ","d"},{"đ","d"},
            {"È","e"},{"É","e"},{"Ẻ","e"},{"Ẽ","e"},{"Ẹ","e"},
            {"è","e"},{"é","e"},{"ẻ","e"},{"ẽ","e"},{"ẹ","e"},
            {"Ê","e"},{"Ề","e"},{"Ế","e"},{"Ể","e"},{"Ễ","e"},{"Ệ","e"},
            {"ê","e"},{"ề","e"},{"ế","e"},{"ể","e"},{"ễ","e"},{"ệ","e"},
            {"Ì","i"},{"Í","i"},{"Ỉ","i"},{"Ĩ","i"},{"Ị","i"},
            {"ì","i"},{"í","i"},{"ỉ","i"},{"ĩ","i"},{"ị","i"},
            {"Ò","o"},{"Ó","o"},{"Ỏ","o"},{"Õ","o"},{"Ọ","o"},
            {"ò","o"},{"ó","o"},{"ỏ","o"},{"õ","o"},{"ọ","o"},
            {"Ô","o"},{"Ồ","o"},{"Ố","o"},{"Ổ","o"},{"Ỗ","o"},{"Ộ","o"},
            {"ô","o"},{"ồ","o"},{"ố","o"},{"ổ","o"},{"ỗ","o"},{"ộ","o"},
            {"Ơ","o"},{"Ờ","o"},{"Ớ","o"},{"Ở","o"},{"Ỡ","o"},{"Ợ","o"},
            {"ơ","o"},{"ờ","o"},{"ớ","o"},{"ở","o"},{"ỡ","o"},{"ợ","o"},
            {"Ù","u"},{"Ú","u"},{"Ủ","u"},{"Ũ","u"},{"Ụ","u"},
            {"ù","u"},{"ú","u"},{"ủ","u"},{"ũ","u"},{"ụ","u"},
            {"Ư","u"},{"Ừ","u"},{"Ứ","u"},{"Ử","u"},{"Ữ","u"},{"Ự","u"},
            {"ư","u"},{"ừ","u"},{"ứ","u"},{"ử","u"},{"ữ","u"},{"ự","u"},
            {"Ỳ","y"},{"Ý","y"},{"Ỷ","y"},{"Ỹ","y"},{"Ỵ","y"},
            {"ỳ","y"},{"ý","y"},{"ỷ","y"},{"ỹ","y"},{"ỵ","y"}
        };

        for (const auto& p : bangMap) {
            thayTheTatCa(s, p.first, p.second);
        }
        return s;
    }

    void inTieuDeBang() {
        cout << left
             << setw(12) << "Ma DT"
             << setw(28) << "Ho va ten"
             << setw(10) << "Gioi tinh"
             << setw(14) << "Ngay sinh"
             << setw(20) << "Que quan" << "\n";
        cout << string(84, '-') << "\n";
    }

    void inMotThiSinh(const ThiSinh& ts) {
        cout << left
             << setw(12) << ts.maDuThi
             << setw(28) << ts.hoTen
             << setw(10) << ts.gioiTinh
             << setw(14) << ts.ngaySinh
             << setw(20) << ts.queQuan << "\n";
    }
}

// =========================================================
// 1. HÀM LÕI: TÌM THEO MÃ DỰ THI (Cho Người 1 & Người 5 gọi)
//    So sánh trực tiếp kiểu string -> giữ nguyên số 0 ở đầu
// =========================================================
Node* timTheoMa(const BangBam& bang, const string& maCanTim) {
    string maChuan = chuanHoaKhoangTrang(maCanTim);
    if (maChuan.empty()) return nullptr;

    for (int i = 0; i < SO_NHOM; ++i) {
        Node* p = bang.bucket[i].head;
        while (p != nullptr) {
            if (p->data.maDuThi == maChuan) {
                return p;
            }
            p = p->next;
        }
    }
    return nullptr;
}

// =========================================================
// 2. TRA CỨU THEO MÃ DỰ THI
// =========================================================
void traCuuTheoMa(const BangBam& bang) {
    if (demThiSinh(bang) == 0) {
        cout << "Danh sach thi sinh dang rong.\n";
        return;
    }

    string ma;
    cout << "Nhap ma du thi can tim: ";
    getline(cin, ma);

    Node* kq = timTheoMa(bang, ma);
    if (kq == nullptr) {
        cout << "Khong tim thay thi sinh co ma \"" << chuanHoaKhoangTrang(ma) << "\".\n";
        return;
    }

    cout << "\nKet qua tim kiem:\n";
    inTieuDeBang();
    inMotThiSinh(kq->data);
}

// =========================================================
// 3. TRA CỨU THEO TÊN (Trả đủ mọi người trùng tên)
// =========================================================
void traCuuTheoTen(const BangBam& bang) {
    if (demThiSinh(bang) == 0) {
        cout << "Danh sach thi sinh dang rong.\n";
        return;
    }

    string tuKhoa;
    cout << "Nhap ten (hoac ho ten) can tim: ";
    getline(cin, tuKhoa);

    tuKhoa = chuanHoaKhoangTrang(tuKhoa);
    if (tuKhoa.empty()) {
        cout << "Tu khoa tim kiem khong duoc de trong.\n";
        return;
    }

    string khoaTim = boToanBoDauVaThuong(tuKhoa);
    int dem = 0;

    for (int i = 0; i < SO_NHOM; ++i) {
        Node* p = bang.bucket[i].head;
        while (p != nullptr) {
            string tenGoi = boToanBoDauVaThuong(layTen(p->data.hoTen));
            string hoTenDayDu = boToanBoDauVaThuong(p->data.hoTen);

            if (tenGoi == khoaTim || hoTenDayDu.find(khoaTim) != string::npos) {
                if (dem == 0) {
                    cout << "\nDanh sach thi sinh phu hop:\n";
                    inTieuDeBang();
                }
                inMotThiSinh(p->data);
                dem++;
            }
            p = p->next;
        }
    }

    if (dem == 0) {
        cout << "Khong tim thay thi sinh nao co ten \"" << tuKhoa << "\".\n";
    } else {
        cout << "=> Tim thay " << dem << " thi sinh.\n";
    }
}

// =========================================================
// 4. TRA CỨU THEO CHỮ CÁI ĐẦU CỦA TÊN (Dùng chung xacDinhNhom của Người 1)
// =========================================================
void traCuuTheoChuCaiDau(const BangBam& bang) {
    if (demThiSinh(bang) == 0) {
        cout << "Danh sach thi sinh dang rong.\n";
        return;
    }

    string chuCai;
    cout << "Nhap chu cai dau cua ten (VD: A, D, Đ...): ";
    getline(cin, chuCai);

    chuCai = chuanHoaKhoangTrang(chuCai);
    int idx = xacDinhNhom(chuCai);

    if (idx < 0 || idx >= SO_NHOM) {
        cout << "Chu cai \"" << chuCai << "\" khong hop le.\n";
        return;
    }

    Node* p = bang.bucket[idx].head;
    if (p == nullptr) {
        cout << "Khong co thi sinh nao co ten bat dau bang chu \"" << chuCai << "\".\n";
        return;
    }

    cout << "\nDanh sach thi sinh nhom chu \"" << chuCai << "\" (" << bang.bucket[idx].soLuong << " nguoi):\n";
    inTieuDeBang();
    while (p != nullptr) {
        inMotThiSinh(p->data);
        p = p->next;
    }
}

// =========================================================
// 5. MENU CON TRA CỨU
// =========================================================
void menuTraCuu(const BangBam& bang) {
    int chon = -1;
    do {
        cout << "\n--- TRA CUU THONG TIN THI SINH ---\n";
        cout << "1. Tim theo ma du thi\n";
        cout << "2. Tim theo ten\n";
        cout << "3. Tim theo chu cai dau cua ten\n";
        cout << "0. Quay lai menu chinh\n";
        cout << "Nhap lua chon: ";

        if (!(cin >> chon)) {
            cout << "Lua chon khong hop le! Vui long nhap so.\n";
            xoaBoNhoDemTraCuu();
            continue;
        }
        xoaBoNhoDemTraCuu();

        switch (chon) {
            case 1: traCuuTheoMa(bang); break;
            case 2: traCuuTheoTen(bang); break;
            case 3: traCuuTheoChuCaiDau(bang); break;
            case 0: break;
            default: cout << "Lua chon khong hop le! Chon tu 0 den 3.\n"; break;
        }
    } while (chon != 0);
}
