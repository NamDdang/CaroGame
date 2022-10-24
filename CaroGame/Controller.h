#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "Model.h"
#include "View.h"
using namespace Model;
using namespace View;
#define SERVER 0
#define CLIENT 1
#define PORT 54001
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
		Model::Player& GetUser1();
		Model::Player& GetUser2();
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
		void ResetReplayMoves();
		// View
		void DrawBoard();
		void DrawGameScreen();
		// Controller
		void InitGame(int);
		bool isContinue();
		void exitGame(); // Ham thoat game

		void ResetBoard();
		bool CheckFullBoard();
		bool HoriWin(int, int);
		bool VertiWin(int, int);
		bool LCrossWin(int, int);
		bool RCrossWin(int, int);

		void CheckWinGame();
		void UpdateWinLoseRecord();
		void UpdateDrawRecord();
		void ReplayLastGame();
		void ReplayGameById(char);
		void PlayerInputAccount();
		void PlayerChooseAccount();
		void PlayerInputMove();
		void ChangePlayer();
		void PlayInBoard();
		void ResetGame();

		void MainMenu();
		void PlayWithOtherPlayer();
		void GameOverMenu();
		void AskToSaveReplay();
		void Replay();
		void PlayerInformationMenu();
		void ShowAllPlayer();
		void SearchPlayerByName();
		void Guide();
		void PlayOnline();
		void PlayOnlineServer();
		void PlayOnlineClient();
		void GameOverMenuOnline(int);

		void StartGame();
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

