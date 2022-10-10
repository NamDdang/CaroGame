#ifndef BOARD_H
#define BOARD_H
#include "Point.h"

class Board
{
private:
	int size;
	Point** pArr;

public:
	Board();
	Board(int);
	~Board();

	int getSize();
	int getXAt(int, int);
	int getYAt(int, int);
	void ResetBoard();
	void DrawBoard();
	bool CheckFullBoard();
	bool HoriWin(int, int);
	bool VertiWin(int, int);
	bool LCrossWin(int, int);
	bool RCrossWin(int, int);
	int GetXO(int, int);
	void SetXO(int, int, int);
};
#endif // BOARD_H
