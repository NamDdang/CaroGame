#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include "Game.h"
#include "SaveDataToFile.h"

using namespace std;

Game* game = new Game(BOARD_SIZE);

int main()
{
    game->StartGame("");
    return 0;
}