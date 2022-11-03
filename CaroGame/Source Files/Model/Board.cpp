#include "../../Header Files/Model/Board.h"
#include <iostream>
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
	for (int i = 0; i <= size; i++) pArr[i] = new Point[size];
}

Board::Board(const Board& board)
{
	size = board.size;
	pArr = new Point * [size];
	for (int i = 0; i <= size; i++) pArr[i] = new Point[size];
	for (int i = 0; i <= size; i++)
		for (int j = 0; j <= size; j++)
			pArr[i][j] = board.pArr[i][j];
}

Board::~Board()
{

	for (int i = 0; i <= size; i++) delete[] pArr[i];
	delete[] pArr;
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