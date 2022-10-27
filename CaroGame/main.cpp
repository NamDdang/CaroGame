#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include "Controller.h"

using namespace std;
using namespace Controller;

GameController* controller;
BOOL WINAPI MyHandlerRoutine(DWORD dwCtrlType)
{
    if (dwCtrlType == CTRL_CLOSE_EVENT || dwCtrlType == CTRL_SHUTDOWN_EVENT)
    {
        OutputDebugStringA("Ctrl-Close\n");
        controller->Logout();
    }
    return FALSE;
}

int main()
{
    Game* game = new Game(BOARD_SIZE);
    GameView* view = new GameView;
    controller = new GameController(game, view);
    SetConsoleCtrlHandler(&MyHandlerRoutine, TRUE);
    controller->StartGame();
    SetConsoleCtrlHandler(&MyHandlerRoutine, FALSE);
    return 0;
}