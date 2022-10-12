#ifndef VIEW_H
#define VIEW_H
#include "Common.h"
#include "Model.h"
using namespace Model;
#define MAIN_MENU 0
#define PLAY_WITH_OTHER 1
#define REPLAY 2
#define PLAYER_INFORMATION 3
#define SHOW_ALL_PLAYER 4
#define SEARCH_PLAYER_BY_NAME 5
#define GUIDE 6
namespace View
{
	// Game View
	class GameView
	{
	public:
		void prompt(string s);
		void prompt(string s, int Color);
		void DrawBoard(Board*);
		void DrawGameScreen(Game*);
		void MenuHeader(int);
		void MainMenu();
		void GameOverMenu();
		void AskToSaveReplay();
		void Replay();
		void PlayerInfomationMenu();
		void ShowAllPlayer();
		void SearchPlayerByName();
		void Guide();
	};
}
#endif // VIEW_H

