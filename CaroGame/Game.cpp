#include "Game.h"
#include "SaveDataToFile.h"
#include <conio.h>

Game::Game(int pSize)
{
	board = new Board(pSize);
	exit = false;
	command = -1; // Gan luot va phim mac dinh
    wongame = false;
    playerwon = 0;
	user1.SetLose(0);
	user1.SetWin(0);
	user1.SetDraw(0);
	user2.SetLose(0);
	user2.SetWin(0);
	user2.SetDraw(0);
}

Game::~Game() { delete board; }

void Game::Init(int pSize)
{
	board = new Board(pSize);
	exit = false;
	command = -1; // Gan luot va phim mac dinh
    wongame = false;
    playerwon = 0;
	user1.SetLose(0);
	user1.SetWin(0);
	user1.SetDraw(0);
	user2.SetLose(0);
	user2.SetWin(0);
	user2.SetDraw(0);
	option = 0;
}

Player& Game::GetUser1() { return user1; }
Player& Game::GetUser2() { return user2; }
void Game::SetTurn(bool value) { turn = value; }
bool Game::GetTurn() { return turn; }
Board* Game::GetBoard() { return board; }
void Game::SetExit(bool value) { exit = value; }
bool Game::GetExit() { return exit; }
void Game::SetOption(char value) { option = value; }
char Game::GetOption() { return option; }
void Game::InputOption()
{
    char key;
    cin >> key;
    if (key >= '0' && key <= '9')
        option = key;
}

bool Game::isWonGame()
{
    return wongame;
}
void Game::SetWonGame(bool value)
{
    wongame = value;
}
int Game::GetPlayerWon()
{
    return playerwon;
}
void Game::SetPlayerWon(int value)
{
    playerwon = value;
}
int Game::getCommand() { return command; }

bool Game::isContinue() { return !exit; }

char Game::waitKeyBoard()
{
	if (_kbhit()) command = toupper(_getch());
	else command = NULL;
	return command;
}

char Game::askContinue()
{
	return command;
}

void Game::exitGame()
{
	system("cls");

	exit = true;
}

void Game::CheckWinGame()
{
    for (int x = 0; x <= board->getSize() - 1; x++)
    {
        for (int y = 0; y <= board->getSize() - 1; y++)
        {
            if (board->HoriWin(x, y) || board->VertiWin(x, y) || board->LCrossWin(x, y) || board->RCrossWin(x, y))
            {
                SetWonGame(true);
                SetPlayerWon(board->GetXO(x, y));
                if (isWonGame() == true) break;
            }
        }
        if (isWonGame() == true) break;
    }
}
void Game::UpdateWinLoseRecord()
{
    if (GetPlayerWon() == VX)
    {
        user1.IncreWin();
        user2.IncreLose();
    }
    else if (GetPlayerWon() == VO)
    {
        user1.IncreLose();
        user2.IncreWin();
    }
    eraseOldResult(user1.GetName());
    writeInFile(user1);
    eraseOldResult(user2.GetName());
    writeInFile(user2);
}
void Game::UpdateDrawRecord()
{
    user1.IncreDraw();
    user2.IncreDraw();
    eraseOldResult(user1.GetName());
    writeInFile(user1);
    eraseOldResult(user2.GetName());
    writeInFile(user2);
}
void Game::PlayerInputAccount()
{
    user1.Input();
    prompt("Input player 1: ");
    user1.Input();
    if (checkName(user1.GetName()) == 0)
    {
        writeInFile(user1);
    }
    updateCurrentResult(user1);
    prompt("Input player 2: ");
    user2.Input();
    if (checkName(user2.GetName()) == 0)
    {
        writeInFile(user2);
    }
    updateCurrentResult(user2);
}
void Game::PlayerChooseAccount()
{
    prompt("List Account: \n", YELLOW);
    SetColor(WHITE);
    showAllInFile();
    prompt("Input name account you want to play or create new account:\n");
    PlayerInputAccount();
}
// Ham de nguoi choi nhap o can danh
void Game::PlayerInputMove()
{
    int inputCol, inputRow;
    if (GetTurn() == true)
    {
        prompt("Player ", WHITE);
        prompt(user1.GetName() + "'s ", P1);
        prompt("turn",WHITE);
        prompt(": ", YELLOW);
        do
        {
            cin >> inputRow;
            cin >> inputCol;
        } while (inputCol < 0 || inputCol > board->getSize() - 1 || inputRow < 0 || inputRow > board->getSize() - 1 || board->GetXO(inputCol, inputRow) != 0);
        board->SetXO(inputCol, inputRow, VX);
    }
    if (GetTurn() == false)
    {
        prompt("Player ", WHITE);
        prompt(user2.GetName() + "'s ", P2);
        prompt("turn", WHITE);
        prompt(": ", YELLOW);
        do
        {
            cin >> inputRow;
            cin >> inputCol;
        } while (inputCol < 0 || inputCol > board->getSize() - 1 || inputRow < 0 || inputRow > board->getSize() - 1 || board->GetXO(inputCol, inputRow) != 0);
        board->SetXO(inputCol, inputRow, VO);
    }
}
void Game::ChangePlayer()
{
    if (GetTurn() == true)
    {
        SetTurn(false);
    }
    else if (GetTurn() == false)
    {
        SetTurn(true);
    }
}
void Game::PlayInBoard()
{
    PlayerInputMove();
    ChangePlayer();
    CheckWinGame();
}
void Game::NewGame()
{
    board->ResetBoard();
    SetTurn(true);
    SetExit(false);
    SetWonGame(false);
    SetPlayerWon(0);
}
void Game::DrawGameScreen()
{
    prompt("=> ", YELLOW);
    prompt("Player ", WHITE);
    prompt(user1.GetName() + " ", P1);
    prompt("= ", YELLOW);
    prompt("X", WHITE);
    prompt(", ", YELLOW);
    prompt("Player ", WHITE);
    prompt(user2.GetName() + " ", P2);
    prompt("= ", YELLOW);
    prompt("O", WHITE);
    prompt(": \n", YELLOW);
    board->DrawBoard();
}
void Game::MainMenu()
{
    prompt("*-------", YELLOW);
    prompt("MAIN MENU", WHITE);
    prompt("-------*\n", YELLOW);
    prompt("1.New ", RED);
    prompt("game \n", WHITE);
    prompt("2.Replay\n", RED);
    prompt("3.Players' ", RED);
    prompt("Information\n", WHITE);
    prompt("4.Guide\n", RED);
    prompt("5.Exit\n", RED);
    prompt("Press number to choice:", WHITE);
}
void Game::Guide()
{
    prompt("*-------", YELLOW);
    prompt("Guide", WHITE);
    prompt("-------*\n", YELLOW);
    SetColor(WHITE);
    prompt("*Trong qua trinh choi, ban lan luot nhap toa do vi tri muon danh = (so dong, so cot)\n");
    prompt("*Ban khong duoc nhap vao vi tri da duoc danh dau hoac ngoai pham vi ban co, neu nhap sai se phai nhap lai\n");
    prompt("*Dieu kien de chien thang tro choi la ben nao co duoc 4 quan co lien tiep theo duong cheo, hang ngang hay \ncot doc truoc va chi bi chan mot dau\n");
    prompt(" VD: XXXX -> Win\n");
    prompt("     OXXXX -> Win\n");
    prompt("     OXXXXO -> NO Win\n");
    prompt("     OXXXX O -> Win\n");
    prompt("*Neu ma tat ca cac o bi danh dau het ma chua co nguoi thang thi 2 nguoi choi se hoa nhau\n");
    prompt("*Tro choi se chi dung lai khi mot trong hai nguoi choi thang hoac ca hai hoa nhau\n");
    prompt("*Thank you! Chuc ban choi vui(^_^)\n");
}
void Game::StartGame(string nameSearch)
{
    NewGame();
    while (isContinue())
    {
        system("cls");
        MainMenu();
        InputOption();
        switch (GetOption())
        {
        case '1': // Play with Other Player
            system("cls");
            SetColor(15);
            PlayerChooseAccount();
            while (GetOption() != '0')
            {
                if (isWonGame() == false)
                {
                    system("cls");
                    DrawGameScreen();
                    if (board->CheckFullBoard())
                    {
                        UpdateDrawRecord();
                        prompt("DRAW!\n", YELLOW);
                        prompt("1.Play ", RED);
                        prompt("again\n", WHITE);
                        prompt("2.Back ", RED);
                        prompt("to MAIN MENU\n", WHITE);
                        prompt("Press number to choice: ", WHITE);
                        InputOption();
                        while (GetOption() < '1' || GetOption() > '2')
                        {
                            prompt("Press again\n");
                            InputOption();
                        }
                        switch (GetOption())
                        {
                        case '1': 
                            NewGame(); 
                            break;
                        case '2':
                            NewGame();
                            SetOption('0');
                            break;
                        }
                    }
                    else
                    {
                        PlayInBoard();
                    }
                }
                if (isWonGame() == true)
                {
                    UpdateWinLoseRecord();
                    system("cls");
                    DrawGameScreen();
                    prompt("Player ", WHITE);
                    if (GetPlayerWon() == VX)
                    {
                        prompt(user1.GetName(), P1);
                    }
                    else if (GetPlayerWon() == VO)
                    {
                        prompt(user2.GetName(), P2);
                    }
                    prompt(" won!\n", YELLOW);
                    prompt("1.Play ", RED);
                    prompt("again\n", WHITE);
                    prompt("2.Back ", RED);
                    prompt("to MAIN MENU\n", WHITE);
                    prompt("Press number to choice: ", WHITE);
                    InputOption();
                    while (GetOption() < '1' || GetOption() > '2')
                    {
                        prompt("Press again\n");
                        InputOption();
                    }
                    switch (GetOption())
                    {
                    case '1': 
                        NewGame(); 
                        break;
                    case '2':
                        NewGame();
                        SetOption('0');
                        break;
                    }
                }
            }
            break;
        case '2': // Replay
            while (GetOption() != '0')
            {
                system("cls");
                prompt("This is DEMO version, please wait for a full version. We will update soon ;)\n");
                prompt("1.Back ", RED);
                prompt("to MAIN MENU\n", WHITE);
                prompt("Press number to choice: ", WHITE);
                InputOption();
                if (GetOption() == '1') SetOption('0');
            }
            break;
        case '3': // Player's Infomation
            while (GetOption() != '0')
            {
                system("cls");
                prompt("*-------", YELLOW);
                prompt("Players's Information", WHITE);
                prompt("-------*\n", YELLOW);
                prompt("1.Show ", RED);
                prompt("All Player\n", WHITE);
                prompt("2.Search ", RED);
                prompt("player by Name\n", WHITE);
                prompt("3.Back ", RED);
                prompt("to MAIN MENU\n", WHITE);
                prompt("Press number to choice:", WHITE);
                InputOption();
                switch (GetOption())
                {
                case '1': // Show All Player
                    while (GetOption() == '1')
                    {
                        system("cls");
                        prompt("*-------", YELLOW);
                        prompt("Players's Records", WHITE);
                        prompt("-------*\n", YELLOW);
                        SetColor(15);
                        showAllInFile();
                        prompt("1.Back ", RED);
                        prompt("to Player's Infomation\n", WHITE);
                        prompt("2.Back ", RED);
                        prompt("to MAIN MENU\n", WHITE);
                        prompt("Press number to choice:", WHITE);
                        InputOption();
                        while (GetOption() < '1' || GetOption() > '2')
                        {
                            prompt("Press again\n");
                            InputOption();
                        }
                        switch (GetOption())
                        {
                        case '1':
                            SetOption('3');
                            break;
                        case '2':
                            SetOption('0');
                            break;
                        }
                    }
                    break;
                case '2': // Search play by name
                    while (GetOption() == '2')
                    {
                        system("cls");
                        prompt("*-------", YELLOW);
                        prompt("Search Player by Name", WHITE);
                        prompt("-------*\n", YELLOW);
                        prompt("Input player's name: ", YELLOW);
                        cin >> nameSearch;
                        searchByName(nameSearch);
                        prompt("1.Continue ", RED);
                        prompt("Search\n", WHITE);
                        prompt("2.Back ", RED);
                        prompt("to Player's Infomation\n", WHITE);
                        prompt("3.Back ", RED);
                        prompt("to MAIN MENU\n", WHITE);
                        prompt("Press number to choice:", WHITE);
                        InputOption();
                        while (GetOption() < '1' || GetOption() > '3')
                        {
                            prompt("Press again\n");
                            InputOption();
                        }
                        switch (GetOption())
                        {
                        case '1':
                            SetOption('2');
                            break;
                        case '2':
                            SetOption('3');
                            break;
                        case '3':
                            SetOption('0');
                            break;
                        }
                    }
                    break;
                case '3': // Back to Main Menu
                    SetOption('0');
                    break;
                default:
                    SetOption('3');
                    break;
                }
            }
            break;
        case '4': // Guide
            while (GetOption() != '0')
            {
                system("cls");
                Guide();
                prompt("1.Back ", RED);
                prompt("to MAIN MENU\n", WHITE);
                prompt("Press number to choice: ", WHITE);
                InputOption();
                if (GetOption() == '1') SetOption('0');
            }
            break;
        case '5': // Exit
            exitGame();
        default:
            break;
        }
    }
}