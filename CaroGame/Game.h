#ifndef GAME_H
#define GAME_H
#include "Board.h"
#include "Player.h"

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
	int getCommand();
	bool isContinue();
	char waitKeyBoard(); // Ham nhan phim tu nguoi dung
	char askContinue();
	void exitGame(); // Ham thoat game

	Player& GetUser1();
	Player& GetUser2();
	void SetTurn(bool);
	bool GetTurn();
	Board* GetBoard();
	void SetExit(bool);
	bool GetExit();
	void SetOption(char);
	char GetOption();
	void InputOption();
	bool isWonGame();
	void SetWonGame(bool);
	int GetPlayerWon();
	void SetPlayerWon(int);

	void CheckWinGame();
	void UpdateWinLoseRecord();
	void UpdateDrawRecord();
	void PlayerInputAccount();
	void PlayerChooseAccount();
	void PlayerInputMove();
	void ChangePlayer();
	void PlayInBoard();
	void DrawGameScreen();
	void NewGame();
	void MainMenu();
	void Guide();
	void StartGame(string);

	void Init(int);
};
#endif // GAME_H

