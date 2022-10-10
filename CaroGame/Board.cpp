#include <iostream>
#include "Board.h"

using namespace std;

int Board::getSize() { return size; }

int Board::getXAt(int i, int j) { return pArr[i][j].getX(); }

int Board::getYAt(int i, int j) { return pArr[i][j].getY(); }

Board::Board()
{
	size = 0;
	pArr = NULL;
}

Board::Board(int pSize)
{
    if (pSize > 10)
    {
        size = 10;
    }
    else if (pSize < 4)
    {
        size = 4;
    }
    else
    {
        size = pSize;
    }
	pArr = new Point * [size];
	for (int i = 0; i < size; i++) pArr[i] = new Point[size];
}

Board::~Board()
{

	for (int i = 0; i < size; i++) delete[] pArr[i];
	delete[] pArr;
}

void Board::DrawBoard()
{
    for (int y = -1; y <= getSize() - 1; y++) // row
    {
        for (int x = -1; x <= getSize(); x++) // col
        {
            if (y == -1)
            {
                if (x == -1) cout << "   ";
                else if (x >= 0 && x <= getSize() - 1)
                {
                    SetColor(RED);
                    cout << "  " << x << " ";
                }
            }
            if (y >= 0 && y <= getSize() - 1)
            {
                if (x == -1)
                {
                    SetColor(RED);
                    cout << " " << y << " ";
                }
                else if (x >= 0 && x <= getSize() - 1)
                {
                    SetColor(YELLOW);
                    cout << "| ";
                    if (GetXO(x, y) == VX)
                    {
                        SetColor(P1);
                        cout << 'X';
                    }
                    else if (GetXO(x, y) == VO)
                    {
                        SetColor(P2);
                        cout << 'O';
                    }
                    else
                    {
                        cout << ' ';
                    }
                    SetColor(YELLOW);
                    cout << " ";
                }
                else cout << "|";
            }
        }
        cout << endl;
        for (int x = -1; x <= getSize(); x++)
        {
            if (x == -1) cout << "   ";
            else if (x >= 0 && x <= getSize() - 1)
            {
                SetColor(YELLOW);
                cout << "|---";
            }
            else cout << "|";
        }
        cout << endl;
    }
}

void Board::ResetBoard()
{
    if (size == 0) return; // Phai goi constructor truoc khi reset data
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            pArr[i][j].setCheck(0);
        }
    }
}
void Board::SetXO(int i, int j, int value)
{
    if (size == 0) return; // Phai goi constructor truoc khi reset data
    pArr[i][j].setCheck(value);
}
int Board::GetXO(int x, int y)
{
    return pArr[x][y].getCheck();
}
// Ham kiem tra xem ban co da day chua
bool Board::CheckFullBoard()
{
    int count = 0;
    for (int x = 0; x <= getSize() - 1; x++)
        for (int y = 0; y <= getSize() - 1; y++)
            if (GetXO(x, y) == 0)
                count++;
    if (count == 0)
        return 1;
    return 0;
}
bool Board::HoriWin(int x, int y)
{
    if (GetXO(x, y) == 0) return false;
    int pl = GetXO(x, y);
    int count = 0;
    int opcount = 0;
    for (int i = x; i >= 0; i--)
    {
        if (GetXO(i, y) == pl) count++;
        else if (GetXO(i, y) != 0)
        {
            opcount++;
            break;
        }
        else break;
    }
    for (int i = x + 1; i <= size - 1; i++)
    {
        if (GetXO(i, y) == pl) count++;
        else if (GetXO(i, y) != 0)
        {
            opcount++;
            break;
        }
        else break;
    }
    if (opcount >= 2) return false;
    if (count >= 4) return true;
    return false;
}
bool Board::VertiWin(int x, int y)
{
    if (GetXO(x, y) == 0) return false;
    int pl = GetXO(x, y);
    int count = 0;
    int opcount = 0;
    for (int i = y; i >= 0; i--)
    {
        if (GetXO(x, i) == pl) count++;
        else if (GetXO(x, i) != 0)
        {
            opcount++;
            break;
        }
        else break;
    }
    for (int i = y + 1; i <= size - 1; i++)
    {
        if (GetXO(x, i) == pl) count++;
        else if (GetXO(x, i) != 0)
        {
            opcount++;
            break;
        }
        else break;
    }
    if (opcount >= 2) return false;
    if (count >= 4) return true;
    return false;
}
bool Board::LCrossWin(int x, int y)
{
    if (GetXO(x, y) == 0) return false;
    int pl = GetXO(x, y);
    int count = 0;
    int opcount = 0;
    int m = min(x, y);
    for (int i = 0; i <= m; i++)
    {
        if (GetXO(x - i, y - i) == pl) count++;
        else if (GetXO(x - i, y - i) != 0)
        {
            opcount++;
            break;
        }
        else break;
    }
    m = min(size - x, size - y);
    for (int i = 1; i <= m; i++)
    {
        if (GetXO(x + i, y + i) == pl) count++;
        else if (GetXO(x + i, y + i) != 0)
        {
            opcount++;
            break;
        }
        else break;
    }
    if (opcount >= 2) return false;
    if (count >= 4) return true;
    return false;
}
bool Board::RCrossWin(int x, int y)
{
    if (GetXO(x, y) == 0) return false;
    int pl = GetXO(x, y);
    int count = 0;
    int opcount = 0;
    int m = min(x, size - y);
    for (int i = 0; i <= m; i++)
    {
        if (GetXO(x - i, y + i) == pl) count++;
        else if (GetXO(x - i, y + i) != 0)
        {
            opcount++;
            break;
        }
        else break;
    }
    m = min(size - x, y);
    for (int i = 1; i <= m; i++)
    {
        if (GetXO(x + i, y - i) == pl) count++;
        else if (GetXO(x + i, y - i) != 0)
        {
            opcount++;
            break;
        }
        else break;
    }
    if (opcount >= 2) return false;
    if (count >= 4) return true;
    return false;
}