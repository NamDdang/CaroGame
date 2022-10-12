#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include "Controller.h"

using namespace std;
using namespace Controller;

int main()
{
    Game* game = new Game(BOARD_SIZE);
    GameView* view = new GameView;
    GameController* controller = new GameController(game, view);
    controller->StartGame();
    return 0;
}