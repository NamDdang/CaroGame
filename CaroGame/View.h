#ifndef VIEW_H
#define VIEW_H
#include "Common.h"
#include "Model.h"
using namespace Model;
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
		void MainMenu();
		void Guide();
	};
}
#endif // VIEW_H

