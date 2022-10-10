#ifndef MODEL_H
#define MODEL_H
#include "Common.h"
#include <iostream>
#include <string>
using namespace std;
namespace Model
{
	// Point
	class Point
	{
		int x, y, check;

	public:
		Point();
		Point(int, int);
		bool setCheck(int);
		int getX();
		int getY();
		int getCheck();
		void setX(int);
		void setY(int);
	};
	// Board
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
	// Player
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
	// Game
	class Game
	{
	private:
		Player user1;
		Player user2;
		Board* board;// mot ban co
		bool turn;// luot choi: true luot nguoi mot & false luot nguoi hai
		int command; // phim go tu nguoi dung
		bool exit; // Bien quyet dinh thoat game hay khong
		char option;
		bool wongame; // Bien kiem tra game da co nguoi thang hay chua
		int playerwon; // Luu nguoi thang game

	public:
		Game(int);
		~Game();
		void Init(int);
		int getCommand();
		char waitKeyBoard();

		Player& GetUser1();
		Player& GetUser2();
		void SetTurn(bool);
		bool GetTurn();
		Board* GetBoard();
		void SetExit(bool);
		bool GetExit();
		void SetOption(char);
		char GetOption();
		bool isWonGame();
		void SetWonGame(bool);
		int GetPlayerWon();
		void SetPlayerWon(int);
	};
}
#endif // MODEL_H

