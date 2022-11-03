#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "../Model/Game.h"
#include "../View/View.h"
#define SERVER 1
#define CLIENT 2
#define PORT 52001
#define GetUserNameW  GetUserName //avoid error

class Controller
{
private:
	Game* model;
	View* view;
public:
	Controller(Game*, View*);
	~Controller();
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
	// Control the flow of game
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
	void PlayOnlineAfterLogin();
	void PlayOnlineServer();
	void PlayOnlineClient();
	void GameOverMenuOnline(int);
	void UserInformation();

	void StartGame();
	// Connect with database
	void Login();
	void Register();
	User GetUserFromDatabase(string);
	void GetUserInfoFromDatabase();
	void InsertMatchToDatabase();
	void UpdateUserInDatabase(int);
	void Logout();
};
#endif // CONTROLLER_H

