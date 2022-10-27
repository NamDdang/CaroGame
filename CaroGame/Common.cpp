#include "Common.h"
#include <windows.h>
#include <conio.h>
void SetColor(int ForgC)
{
    WORD wColor;

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    //We use csbi for the wAttributes word.
    if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        //Mask out all but the background attribute, and add in the forgournd color
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
    return;
}
char* InputStringName(const int k)
{
    char* kq = new char[k + 1]; // tao mang
    int n, index = 0;
    do
    {
    loop:;
        n = _getch(); // lay ma ASCII
        // Neu thuoc 0-9, A-Z, a-z hoac dau '.' va chuoi đang co it hon k ky tu thi cho phep
        if (((n >= '0' && n <= '9') || (n >= 'A' && n <= 'Z') || (n >= 'a' && n <= 'z') || n == '.') && index < k)
        {
            cout << char(n); // xuat ky tu do ra man hinh
            kq[index++] = n; // Luu vao mang
        }
        else if (n == '\b' && index > 0) // Neu nhan dau BackSpace ma chuoi khong rong
        {
            cout << "\b \b"; // Xoa 1 ky tu tren man hinh
            kq[--index] = 0; // Xoa 1 ky tu trong chuoi kq
        }
        if (n == 13 && index == 0) goto loop; // Neu nhan Enter ma chua nhap gi thi khong cho phep
    } while (n != 13); // Cu lap lai trong khi chua nhap Enter

    kq[index] = 0; // Ket thuc chuoi
    cout << '\n';
    return kq;
}
bool isIPAddress(string ip)
{
    int count = 0;
    for (int i = 0; i < ip.size(); i++)
    {
        if ((ip[i] < '0' || ip[i] > '9') && ip[i] != '.')
        {
            return false;
        }
        if (ip[i] == '.')
        {
            count++;
            if (i == 0) return false;
            if (i >= 1 && ip[i - 1] == '.') return false;
            if (i == 2 && ip[i - 2] == '0') return false;
            if (i >= 3 && ip[i - 1] == '0' && ip[i - 2] == '0' && ip[i - 3] != '1' && ip[i - 3] != '2') return false;
            if (i >= 3 && ip[i - 1] >= '6' && ip[i - 1] <= '9' && ip[i - 2] == '5' && ip[i - 3] == '2') return false;
            if (i >= 3 && ip[i - 2] >= '6' && ip[i - 2] <= '9' && ip[i - 3] == '2') return false;
            if (i >= 4 && ip[i - 1] != '.' && ip[i - 2] != '.' && ip[i - 3] != '.' && ip[i - 4] != '.') return false;
        }
        if (count > 0) // Tranh truy cap ra ngoai mang string
        {
            if (i == ip.size() - 1)
            {
                if (ip[i] == '.') return false;
                if (ip[i] == '0' && ip[i - 1] == '0' && ip[i - 2] != '1' && ip[i - 2] != '2') return false;
                if (ip[i] >= '6' && ip[i] <= '9' && ip[i - 1] == '5' && ip[i - 2] == '2') return false;
                if (ip[i - 1] >= '6' && ip[i - 1] <= '9' && ip[i - 2] == '2') return false;
                if (ip[i] != '.' && ip[i - 1] != '.' && ip[i - 2] != '.' && ip[i - 3] != '.') return false;
            }
        }
    }
    if (count != 3) return false;
    return true;
}

