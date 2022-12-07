#include <bits/stdc++.h>
using namespace std;

struct Datetime
{
    int ngay, thang, nam;
};


struct NhanVien
{
    string MaNV;
    string TenNV;
    Datetime Ngayvaolam;
    int Luongcb;
    int phuCap;
    int tongLuong;
};
typedef struct NhanVien NV;

// Khai báo cấu trúc cho Hóa Đơn
struct HoaDonNhap
{
    string MaHD;
    string TenNVlapHD;
    Datetime Ngaylap;
    int soLuong;
    int donGia;
    int TonggiaHang;
};
typedef struct HoaDonNhap HD;

struct Node
{
    HoaDonNhap inforHD;
    NhanVien inforNV;
    struct Node *next;
    struct Node *prev;
};
typedef struct Node NODE;

struct QUEUE
{
    NODE *front;
    NODE *rear;
};

// Khởi tạo hàng đợi rỗng
void KhoiTao(QUEUE &q)
{
    q.front = NULL;
    q.rear = NULL;
}

// Tạo node Nhân viên
NODE* TaoNodeNV (NV x)
{
    NODE *p;
    p = new NODE;
    if (p == NULL)
    {
        cout << "\nKhong du bo nho";
        return NULL;
    }
    p->inforNV = x;
    p->next = NULL;
    p->prev = NULL;
    return p;
}

//Tạo node hóa đơn
NODE* TaoNodeHD (HD y)
{
    NODE *q = new NODE;
    if (q == NULL)
    {
        cout << "\nKhong du bo nho";
        return NULL;
    }
    q->inforHD = y;
    q->next = NULL;
   // q->prev = NULL;
    return q;
}

int Kiemtrarong(QUEUE q){
    if (q.front == NULL)
    {
        return 1;
    }
    return 0;
}

void Them(QUEUE &q, NODE *NewNode)
{
    if(q.front == NULL)
    {
        q.front = NewNode;
        q.rear = NewNode;
    }
    else
    {
        q.rear->next = NewNode;
        q.rear = NewNode;
    }
}

NV Xoa(QUEUE &q)
{
    NV x;
    NODE *p = NULL;
    if (!Kiemtrarong(q))
    {
        int chonXoa;
        do
        {
            cout << "\n1. Xoa nhan vien dau tien";
            cout << "\n2. Xoa nhan vien moi nhat";
            cout << "\n3. Xoa nhan vien thu n";
            cout << "\n0. Khong xoa nua? Nhap 0 de quay lai";
            cout << "\n Moi chon: ";
            cin >> chonXoa;
            switch(chonXoa)
            {
                case 1:
                    p = q.front;
                    x = p->inforNV;
                    q.front = q.front->next;
                    delete p;
                    if (q.front == NULL){
                        q.rear = NULL;
                    }
                    cout << "Xoa thanh cong!"; break;
                case 2:
                    p = q.rear;
                    x = p->inforNV;
                    q.rear = q.rear->prev;
                    delete p;
                    if (q.rear == NULL){
                        q.front = NULL;
                    }
                    cout << "Xoa thanh cong!"; break;
                case 0: break;
            }
        } while (chonXoa != 0);
    }
    return x;
}

// Thao tác với nhân viên
void NhapNV(QUEUE &q, int n)
{
    for(int i = 0; i< n; i++)
    {
        NV x;
        cout << "Nhap ma NV: ";
        cin.ignore();
        cin >> x.MaNV;
        cout << "Nhap ten nhan vien: ";
        cin.ignore();
        cin >> x.TenNV;
        cout << "Nhap ngay vao lam:";
        cout << "\nNgay: ";
        cin >> x.Ngayvaolam.ngay;
        cout << "Thang: ";
        cin >> x.Ngayvaolam.thang;
        cout << "Nam: ";
        cin >> x.Ngayvaolam.nam;
        cout << "Nhap luong co ban: ";
        cin >> x.Luongcb;
        cout << "Nhap phu cap: ";
        cin >> x.phuCap;
        x.tongLuong = x.Luongcb + x.phuCap;

        NODE *p;
        p = TaoNodeNV(x);
        Them(q, p);
    }
}
void XuatNV(QUEUE q)
{
    if(Kiemtrarong(q))
    {
        cout << "\n----- Hang doi Nhan vien rong -----\n";
    } else
    {
        cout << "\t\t\t\tTHONG TIN NHAN VIEN TRONG HANG DOI\n";
        cout << "\n" << "\t" << left << setw(10) << "Ma NV";
        cout << setw(15) << "Ten NV";
        cout << setw(15) << "Ngay vao lam";
        cout << setw(15) << "Luong cb";
        cout << setw(15) << "Phu cap";
        cout << setw(15) << "Tong luong";

        for (NODE *p = q.front; p != NULL; p = p->next)
        {
            cout << "\n" << "\t"  << left << setw(10) << p->inforNV.MaNV;
            cout << setw(15) << p->inforNV.TenNV;
            cout << p->inforNV.Ngayvaolam.ngay << "/" << p->inforNV.Ngayvaolam.thang << "/" << setw(10) << p->inforNV.Ngayvaolam.nam;
            cout << setw(15) << p->inforNV.Luongcb;
            cout << setw(15) << p->inforNV.phuCap;
            cout << setw(15) << p->inforNV.tongLuong;
        }
        cout << "\n";
    }
}

void themRear(QUEUE &q, int n)
{
    NV x;
    NODE *p = new NODE;
    NhapNV(q, n);
    if(p == NULL)
    {
        cout << "Khong bo sung duoc";
        exit(0);
    }
    p ->inforNV = x;
    p->next = NULL;
    p->prev = NULL;
    if(q.rear == NULL)
    {
        q.front = p;
        q.rear = p;
    }
    else
    {
        p->next = q.front;
        q.front->prev = p;
        q.front = p;
    }
}

void write2file(char *filename, QUEUE q){
    ofstream fs(filename, ios::binary | ios::out );//| ios::app
    NODE *p = q.front;
    while(p!=NULL){
    fs.write((char*)&p->inforNV,sizeof(int));
    p=p->next;
    }
    fs.close();
}

void readfromfile(char * filename, QUEUE &q)
{
    KhoiTao(q);
    ifstream infile(filename,ios::in|ios::binary);
    NV x;
    infile.read((char*)&x,sizeof(int));
    while(!infile.eof())
    {
        NODE * p = TaoNodeNV(x);
        Them(q, p);
        infile.read((char*)&x,sizeof(int));
    }
    infile.close();
}

// Thao tác với hóa đơn
void NhapHD(QUEUE &q, int n)
{
    for(int i = 0; i< n; i++)
    {
        HD y;
        cout << "\nNhap ma HD: ";
        cin.ignore();
        cin >> y.MaHD;
        cout << "Nhap ten nhan vien nhap hoa don: ";
        cin.ignore();
        cin >> y.TenNVlapHD;
        cout << "Nhap ngay lap hoa don:";
        cout << "\nNgay: ";
        cin >> y.Ngaylap.ngay;
        cout << "Thang: ";
        cin >> y.Ngaylap.thang;
        cout << "Nam: ";
        cin >> y.Ngaylap.nam;
        cout << "Nhap so luong hang: ";
        cin >> y.soLuong;
        cout << "Nhap don gia san pham: ";
        cin >> y.donGia;
        y.TonggiaHang = y.soLuong * y.donGia;

        NODE *p;
        p = TaoNodeHD(y);
        Them(q, p);
    }
}
void XuatHD(QUEUE q)
{
    if(Kiemtrarong(q))
    {
        cout << "\n----- Hang doi Hoa don rong -----\n";
    } else
    {
        cout << "\t\t\t\t\tTHONG TIN HOA DON TRONG HANG DOI\n";
        cout << "\n" << "\t" << left << setw(10) << "Ma HD";
        cout << setw(25) << "Ten nguoi lap";
        cout << setw(15) << "Ngay lap";
        cout << setw(15) << "So luong";
        cout << setw(15) << "Don gia";
        cout << setw(15) << "Thanh tien";

        for (NODE *p = q.front; p != NULL; p = p->next)
        {
            cout << "\n" << "\t"  << left << setw(10) << p->inforHD.MaHD;
            cout << setw(25) << p->inforHD.TenNVlapHD;
            cout << p->inforHD.Ngaylap.ngay << "/" << p->inforHD.Ngaylap.thang << "/" << setw(10) << p->inforHD.Ngaylap.nam;
            cout << setw(15) << p->inforHD.soLuong;
            cout << setw(15) << p->inforHD.donGia;
            cout << setw(15) << p->inforHD.TonggiaHang;
        }
        cout << "\n";
    }
}

int main(){

    QUEUE q;
    KhoiTao(q);
    int nnv;
    int nhd;

    int chon;
    do
    {
        cout <<"\n 1. Nhan vien ";
        cout <<"\n 2. Hoa don";
        cout << "\nMoi chon: ";
        cin >> chon;
        system("cls");
        switch (chon)
        {
            case 1:
                int chonNv;
                do
                {
                    cout <<"\n 1. Nhap nhan vien";
                    cout <<"\n 2. In nhan vien";
                    cout <<"\n 3. Them nhan vien";
                    cout <<"\n 4. Xoa nhan vien";
                    cout <<"\n 5. Ttem nhan vien vao rear";
                    cout <<"\n 6.Ghi vao file";
                    cout <<"\n 7.Doc tu file";
                    cout <<"\n 0. Quay lai";
                    cout << "\n Moi chon: ";
                    cin >> chonNv;
                    switch (chonNv)
                    {
                        case 1:
                            cout << "Nhap so nhan vien: ";
                            cin >> nnv;
                            NhapNV(q, nnv); break;
                        case 2: XuatNV(q); break;
                        case 3:
                            int m;
                            cout << "Nhap so nhan vien muon them: ";
                            cin >> m;
                            NhapNV(q, m); break;
                        case 4: Xoa(q); break;
                        case 5:
                            int k;
                            cout << "Nhap so nhan vien muon them: ";
                            cin >> k;
                            themRear(q, k); break;
                        case 6:
                            char* filenameluu;
                            cout << "Nhap ten file muon luu vao: ";
                            cin >> filenameluu;
                            write2file(filenameluu, q);
                            cout << "Ghi thanh cong"; break;
                        case 7:
                            char* filenamedoc;
                            cout << "Nhap ten file muon luu vao: ";
                            cin >> filenamedoc;
                            readfromfile(filenamedoc, q);
                            cout << "Doc thanh cong!!!"; break;
                        case 0: system("cls"); break;
                    }
                } while (chonNv != 0);; break;
            case 2:
                int chonHd;
                do
                {
                    int chonhd;
                    cout <<"\n 1. Nhap hoa don";
                    cout <<"\n 2. In hoa don";
                    cout <<"\n 3. Them hoa don";
                    cout <<"\n 0. Quay lai";
                    cout << "\nMoi chon: ";
                    cin >> chonHd;
                    switch (chonHd)
                    {
                        case 1:
                            cout << "Nhap so hoa don: ";
                            cin >> nhd;
                            NhapHD(q, nhd); break;
                        case 2: XuatHD(q); break;
                        case 3:
                            int m;
                            cout << "Nhap so hoa don muon them: ";
                            cin >> m;
                            NhapHD(q, m);
                        case 0: system("cls"); break; break;
                    }
                } while (chonHd != 0);; break;
            case 0: exit(0); break;
        }
    } while (chon != 0);
}
