#ifndef GAME_H
#define GAME_H
#include "Board.h"
#include "Player.h"
#include "User.h"
#include <list>
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
#endif // GAME_H
