#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <string>
using namespace std;
class Player
{
private:
	string name;
	int win;
	int lose;
	int draw;
public:
	string GetName();
	void SetName(string);
	void Input(); 
	void SetWin(int); 
	void SetLose(int); 
	void SetDraw(int);
	int GetWin(); 
	int GetLose();
	int GetDraw();
	void IncreWin();
	void IncreLose(); 
	void IncreDraw(); 
};
#endif // PLAYER_H

