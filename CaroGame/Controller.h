#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "Model.h"
#include "View.h"
using namespace Model;
using namespace View;
namespace Controller
{
	// Game Controller
	class GameController
	{
	private:
		Game* model;
		GameView* view;
	public:
		GameController(Game*, GameView*);
		// Store, Get Data
		int getCommand();

		Model::Player& GetUser1();
		Model::Player& GetUser2();
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
		// View
		void DrawBoard();
		void DrawGameScreen();
		// Controller
		void ResetBoard();
		bool CheckFullBoard();
		bool HoriWin(int, int);
		bool VertiWin(int, int);
		bool LCrossWin(int, int);
		bool RCrossWin(int, int);

		bool isContinue();
		char waitKeyBoard(); // Ham nhan phim tu nguoi dung
		char askContinue();
		void exitGame(); // Ham thoat game
		void InputOption();

		void CheckWinGame();
		void UpdateWinLoseRecord();
		void UpdateDrawRecord();
		void PlayerInputAccount();
		void PlayerChooseAccount();
		void PlayerInputMove();
		void ChangePlayer();
		void PlayInBoard();
		void NewGame();
		void StartGame(string);

		void InitGame(int);
	};
	// Point Controller
	class PointController
	{
	private:
		Point* model;

	public:
		PointController(Point*);
		bool setCheck(int);
		int getX();
		int getY();
		int getCheck();
		void setX(int);
		void setY(int);
	};
	// Board Controller
	class BoardController
	{
	private:
		Board* model;

	public:
		BoardController(Board*);
		int getSize();
		int getXAt(int, int);
		int getYAt(int, int);
		int GetXO(int, int);
		void SetXO(int, int, int);
	};
	// Player Controller
	class PlayerController
	{
	private:
		Player* model;

	public:
		PlayerController(Player*);
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
}
#endif // CONTROLLER_H

