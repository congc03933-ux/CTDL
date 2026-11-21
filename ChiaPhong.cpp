#include <iostream>
#include <iomanip>
#include "QuanLy.h"
#include "ChiaPhong.h"
using namespace std;

void khoiTaoKetQua(KetQuaChiaPhong& kq)
{
    kq.soPhong = 0;
    kq.phong = NULL;
    kq.soCapTrung = 0;
}

void giaiPhongKetQua(KetQuaChiaPhong& kq)
{
    for (int i = 0; i < kq.soPhong; i++)
    {
        PhongNode* p = kq.phong[i].head;
        while (p != NULL)
        {
            PhongNode* tam = p;
            p = p->next;
            delete tam;
        }
    }
    delete[] kq.phong;
    khoiTaoKetQua(kq);
}

void themVaoPhong(Phong& ph, const ThiSinh* ts, int nhom)
{
    PhongNode* moi = new PhongNode;

    moi->ts = ts;
    moi->nhom = nhom;
    moi->next = NULL;

    if (ph.head == NULL)
    {
        ph.head = moi;
        ph.tail = moi;
    }
    else
    {
        ph.tail->next = moi;
        ph.tail = moi;
    }

    ph.size++;
}

int demCapTrung(const KetQuaChiaPhong& kq)
{
    int tong = 0;
    for (int i = 0; i < kq.soPhong; i++)
    {
        int dem[SO_NHOM] = {0};
        for (PhongNode* p = kq.phong[i].head; p != NULL; p = p->next)
            dem[p->nhom]++;
        for (int g = 0; g < SO_NHOM; g++)
            tong += dem[g] * (dem[g] - 1) / 2;
    }
    return tong;
}

bool chiaPhong(const BangBam& bang, int soPhong, KetQuaChiaPhong& kq)
{
    giaiPhongKetQua(kq);

    if (soPhong <= 0)
        return false;

    int tong = 0;
    for (int g = 0; g < SO_NHOM; g++)
        tong += bang.bucket[g].soLuong;

    if (tong == 0)
        return false;

    kq.soPhong = soPhong;
    kq.phong = new Phong[soPhong];

    for (int i = 0; i < soPhong; i++)
    {
        kq.phong[i].head = NULL;
        kq.phong[i].tail = NULL;
        kq.phong[i].size = 0;
    }

    int luot = 0;

    for (int g = 0; g < SO_NHOM; g++)
    {
        for (Node* p = bang.bucket[g].head; p != NULL; p = p->next)
        {
            themVaoPhong(kq.phong[luot], &p->data, g);

            luot++;
            if (luot == soPhong)
                luot = 0;
        }
    }

    kq.soCapTrung = demCapTrung(kq);
    return true;
}

void xuatDanhSachPhong(ostream& os, const KetQuaChiaPhong& kq)
{
    if (kq.phong == NULL)
    {
        os << "Chưa chia phòng.\n";
        return;
    }
    for (int i = 0; i < kq.soPhong; i++)
    {
        os << "\n=== Phòng " << i + 1 << " (" << kq.phong[i].size << " người) ===\n";
        if (kq.phong[i].size == 0)
            os << "  (phòng rỗng)\n";
        int stt = 1;
        for (PhongNode* p = kq.phong[i].head; p != NULL; p = p->next)
        {
            os << setw(3) << stt << ". " << p->ts->maDuThi << " | "
               << p->ts->hoTen << " | " << p->ts->gioiTinh << " | "
               << p->ts->ngaySinh << " | " << p->ts->queQuan << "\n";
            stt++;
        }
    }
    os << "\nSố cặp cùng chữ cái đầu trong cùng phòng: " << kq.soCapTrung << "\n";
}

int nhapSoPhong()
{
    int n;
    while (true)
    {
        cout << "Nhập số phòng thi: ";
        cin >> n;
        if (cin.fail() || n <= 0)
        {
            cout << "Số phòng không hợp lệ, nhập lại.\n";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        else
        {
            cin.ignore(1000, '\n');
            return n;
        }
    }
}

void thucHienChiaPhong(const BangBam& bang, KetQuaChiaPhong& kq)
{
    int tong = 0;

    for (int g = 0; g < SO_NHOM; g++)
        tong += bang.bucket[g].soLuong;

    if (tong == 0)
    {
        cout << "Chua co thi sinh de chia phong.\n";
        return;
    }

    int soPhong = nhapSoPhong();

    if (soPhong > tong)
        cout << "Luu y: so phong lon hon so thi sinh, se co phong rong.\n";

    chiaPhong(bang, soPhong, kq);
    xuatDanhSachPhong(cout, kq);
}
