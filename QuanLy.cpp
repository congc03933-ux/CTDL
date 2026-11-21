#include "QuanLy.h"

void khoiTaoDanhSach(DanhSach& ds) {
    ds.head = nullptr;
    ds.tail = nullptr;
    ds.soLuong = 0;
}

void khoiTaoBangBam(BangBam& bang) {
    for (int i = 0; i < SO_NHOM; i++) {
        khoiTaoDanhSach(bang.bucket[i]);
    }
}

Node* taoNode(const ThiSinh& ts) {
    Node* p = new Node;
    p->data = ts;
    p->next = nullptr;
    return p;
}

void themCuoi(DanhSach& ds, const ThiSinh& ts) {
    Node* p = taoNode(ts);

    if (ds.head == nullptr) {
        ds.head = p;
        ds.tail = p;
    } else {
        ds.tail->next = p;
        ds.tail = p;
    }

    ds.soLuong++;
}

int demThiSinh(const BangBam& bang) {
    int tong = 0;
    for (int i = 0; i < SO_NHOM; i++) {
        tong += bang.bucket[i].soLuong;
    }
    return tong;
}

void giaiPhongDanhSach(DanhSach& ds) {
    while (ds.head != nullptr) {
        Node* p = ds.head;
        ds.head = ds.head->next;
        delete p;
    }

    ds.tail = nullptr;
    ds.soLuong = 0;
}

void giaiPhongBangBam(BangBam& bang) {
    for (int i = 0; i < SO_NHOM; i++) {
        giaiPhongDanhSach(bang.bucket[i]);
    }
}
string layTen(const string& hoTen) {
    int i = static_cast<int>(hoTen.length()) - 1;
    while (i >= 0 && hoTen[i] == ' ') {
        i--;
    }
    if (i < 0) {
        return "";
    }
    int cuoi = i;
    while (i >= 0 && hoTen[i] != ' ') {
        i--;
    }
    int dau = i + 1;
    return hoTen.substr(dau, cuoi - dau + 1);
}
string layChuDau(const string& ten) {
    if (ten.empty()) {
        return "";
    }
    unsigned char c = static_cast<unsigned char>(ten[0]);
    int soByte;

    if (c < 128) {
        soByte = 1;
    } else if (c >= 194 && c <= 223) {
        soByte = 2;
    } else if (c >= 224 && c <= 239) {
        soByte = 3;
    } else if (c >= 240 && c <= 244) {
        soByte = 4;
    } else {
        return "";
    }
    return ten.substr(0, soByte);
}
int xacDinhNhom(const string& hoTen) {
    string ten = layTen(hoTen);
    string chuDau = layChuDau(ten);

    if (chuDau.empty()) {
        return -1;
    }

    static const string nhom[SO_NHOM] = {
        u8"aA\u00E0\u00C0\u00E1\u00C1\u1EA3\u1EA2\u00E3\u00C3\u1EA1\u1EA0",
        u8"\u0103\u0102\u1EB1\u1EB0\u1EAF\u1EAE\u1EB3\u1EB2\u1EB5\u1EB4\u1EB7\u1EB6",
        u8"\u00E2\u00C2\u1EA7\u1EA6\u1EA5\u1EA4\u1EA9\u1EA8\u1EAB\u1EAA\u1EAD\u1EAC",
        "bB",
        "cC",
        "dD",
        u8"\u0111\u0110",
        u8"eE\u00E8\u00C8\u00E9\u00C9\u1EBB\u1EBA\u1EBD\u1EBC\u1EB9\u1EB8",
        u8"\u00EA\u00CA\u1EC1\u1EC0\u1EBF\u1EBE\u1EC3\u1EC2\u1EC5\u1EC4\u1EC7\u1EC6",
        "gG",
        "hH",
        u8"iI\u00EC\u00CC\u00ED\u00CD\u1EC9\u1EC8\u0129\u0128\u1ECB\u1ECA",
        "kK",
        "lL",
        "mM",
        "nN",
        u8"oO\u00F2\u00D2\u00F3\u00D3\u1ECF\u1ECE\u00F5\u00D5\u1ECD\u1ECC",
        u8"\u00F4\u00D4\u1ED3\u1ED2\u1ED1\u1ED0\u1ED5\u1ED4\u1ED7\u1ED6\u1ED9\u1ED8",
        u8"\u01A1\u01A0\u1EDD\u1EDC\u1EDB\u1EDA\u1EDF\u1EDE\u1EE1\u1EE0\u1EE3\u1EE2",
        "pP",
        "qQ",
        "rR",
        "sS",
        "tT",
        u8"uU\u00F9\u00D9\u00FA\u00DA\u1EE7\u1EE6\u0169\u0168\u1EE5\u1EE4",
        u8"\u01B0\u01AF\u1EEB\u1EEA\u1EE9\u1EE8\u1EED\u1EEC\u1EEF\u1EEE\u1EF1\u1EF0",
        "vV",
        "xX",
        u8"yY\u1EF3\u1EF2\u00FD\u00DD\u1EF7\u1EF6\u1EF9\u1EF8\u1EF5\u1EF4"
    };

    for (int i = 0; i < SO_NHOM; i++) {
        if (nhom[i].find(chuDau) != string::npos) {
            return i;
        }
    }

    return -1;
}
bool coNoiDung(const string& s) {
    for (int i = 0; i < static_cast<int>(s.length()); i++) {
        if (s[i] != ' ' && s[i] != '\t'
            && s[i] != '\r' && s[i] != '\n') {
            return true;
        }
    }

    return false;
}
bool themThiSinh(BangBam& bang, const ThiSinh& ts) {
	if (!coNoiDung(ts.hoTen)|| !coNoiDung(ts.maDuThi)|| !coNoiDung(ts.gioiTinh)|| !coNoiDung(ts.queQuan)) {
    return false;
	}

    int viTri = xacDinhNhom(ts.hoTen);
    if (viTri == -1) {
        return false;
    }
    if (!kiemTraNgaySinh(ts.ngaySinh)) {
        return false;
    }

    for (int i = 0; i < SO_NHOM; i++) {
        Node* p = bang.bucket[i].head;

        while (p != nullptr) {
            if (p->data.maDuThi == ts.maDuThi) {
                return false;
            }

            p = p->next;
        }
        
    }
    themCuoi(bang.bucket[viTri], ts);
    return true;
} 
bool kiemTraNgaySinh(const string& ngaySinh) {
    if (ngaySinh.length() != 10) {
        return false;
    }
    if (ngaySinh[2] != '/' || ngaySinh[5] != '/') {
        return false;
    }
    for (int i = 0; i < 10; i++) {
        if (i == 2 || i == 5) {
            continue;
        }

        if (ngaySinh[i] < '0' || ngaySinh[i] > '9') {
            return false;
        }
    }
    int ngay = (ngaySinh[0] - '0') * 10
             + (ngaySinh[1] - '0');

    int thang = (ngaySinh[3] - '0') * 10
              + (ngaySinh[4] - '0');
    int nam = (ngaySinh[6] - '0') * 1000
            + (ngaySinh[7] - '0') * 100
            + (ngaySinh[8] - '0') * 10
            + (ngaySinh[9] - '0');
    if (nam < 1 || thang < 1 || thang > 12) {
        return false;
    }
    int soNgay[12] = {
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };
    bool namNhuan = (nam % 400 == 0)
                || (nam % 4 == 0 && nam % 100 != 0);

    if (namNhuan) {
        soNgay[1] = 29;
    }
    return ngay >= 1 && ngay <= soNgay[thang - 1];
}
