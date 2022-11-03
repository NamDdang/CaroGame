#ifndef BOARD_H
#define BOARD_H
#include "Point.h"
#define BOARD_SIZE 10
class Board
{
private:
	int size;
	Point** pArr;

public:
	Board();
	Board(int);
	Board(const Board&);
	~Board();

	int getSize();
	int getXAt(int, int);
	int getYAt(int, int);
	int GetXO(int, int);
	void SetXO(int, int, int);
};
#endif // BOARD_H
