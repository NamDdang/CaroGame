#include "Player.h"

string Player::GetName() { return name; }
void Player::SetName(string value) { name = value; }
void Player::Input()
{
	fflush(stdin);
	getline(cin, name);
	// nhap mot ten moi thi dat so tran thang, thua, hoa ve bang 0
	win = 0;
	lose = 0;
	draw = 0;
}

void Player::SetWin(int value) { win = value; }
void Player::SetLose(int value) { lose = value; }
void Player::SetDraw(int value) { draw = value; }
int Player::GetWin() { return win; }
int Player::GetLose() { return lose; }
int Player::GetDraw() { return draw; }
void Player::IncreWin() { win++; }
void Player::IncreLose() { lose++; }
void Player::IncreDraw() { draw++; }
