#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include "../../Header Files/Controller/Controller.h"

using namespace std;

Controller* controller;
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
    View* view = new View;
    controller = new Controller(game, view);
    SetConsoleCtrlHandler(&MyHandlerRoutine, TRUE);
    controller->StartGame();
    SetConsoleCtrlHandler(&MyHandlerRoutine, FALSE);
    return 0;
}