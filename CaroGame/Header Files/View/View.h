#ifndef VIEW_H
#define VIEW_H
#include "../Model/Game.h"
enum textColor
{
	BLACK,
	BLUE,
	GREEN,
	CYAN,
	RED,
	MAGENTA,
	BROWN,
	LIGHT_GRAY,
	DARK_GRAY,
	LIGHT_BLUE,
	LIGHT_GREEN,
	LIGHT_CYAN,
	LIGHT_RED,
	LIGHT_MAGENTA,
	YELLOW,
	WHITE
};
enum playerColor
{
	P1 = RED,
	P2 = BLUE
};
enum menuHeader
{
	MAIN_MENU,
	PLAY_WITH_OTHER,
	REPLAY,
	PLAYER_INFORMATION,
	SHOW_ALL_PLAYER,
	SEARCH_PLAYER_BY_NAME,
	PLAY_ONLINE,
	USER_INFORMATION,
	GUIDE
};
class View
{
public:
	static void SetColor(int ForgC);
	void prompt(string s);
	void prompt(string s, int Color);
	void screenGetCommand(char& command);
	void screenGetStringName(string &name);
	void screenGetIPAddress(string &ipAddress);
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
	void PlayOnline();
	void PlayOnlineAfterLogin();
};
#endif // VIEW_H

