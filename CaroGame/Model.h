#ifndef MODEL_H
#define MODEL_H
#include "Common.h"
#include <iostream>
#include <string>
#include <list>
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
	// User
	class User
	{
	private:
		int id;
		string username;
		string password;
		int win;
		int lose;
		int draw;
		bool online;
	public:
		User();
		User(int, string, string, int, int, int, bool);
		int GetId();
		void SetId(int);
		string GetUserName();
		void SetUserName(string);
		string GetPassWord();
		void SetPassWord(string);
		int GetWin();
		void SetWin(int);
		int GetLose();
		void SetLose(int);
		int GetDraw();
		void SetDraw(int);
		bool isOnline();
		void SetStatusOnline(bool);
	};
	// Game
	struct Move {
		int col, row, value;
	};
	class Game
	{
	private:
		Player player1;
		Player player2;
		Board* board;// mot ban co
		bool turn;// luot choi: true luot nguoi mot & false luot nguoi hai
		bool exit; // Bien quyet dinh thoat game hay khong
		bool wongame; // Bien kiem tra game da co nguoi thang hay chua
		int playerwon; // Luu nguoi thang game
		list<Move> replayMoves; // Luu nuoc di nguoi choi nhap
		User user;
	public:
		Game(int);
		~Game();
		void Init(int);

		Player& GetPlayer1();
		Player& GetPlayer2();
		void SetPlayer1(Player);
		void SetPlayer2(Player);
		User& GetUser();
		void SetUser(User);
		void SetTurn(bool);
		bool GetTurn();
		Board* GetBoard();
		void SetExit(bool);
		bool GetExit();
		bool isWonGame();
		void SetWonGame(bool);
		int GetPlayerWon();
		void SetPlayerWon(int);
		void SaveMove(int, int, int);
		list<Move> GetReplayMoves();
		void ResetReplayMoves();
	};
	// Match
	class Match
	{
	private:
		int matchId;
		string player1;
		string player2;
		string playerwin;
	public:
		Match();
		Match(int, string, string, string);
		int GetMatchId();
		void SetMatchId(int);
		string GetPlayer1();
		void SetPlayer1(string);
		string GetPlayer2();
		void SetPlayer2(string);
		string GetPlayerWin();
		void SetPlayerWin(string);
	};
}
#endif // MODEL_H

