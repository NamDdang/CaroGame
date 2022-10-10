#include "Controller.h"
#include "SaveDataToFile.h"
using namespace Controller;
// Game Controller
GameController::GameController(Game* model, GameView* view)
{
    this->model = model;
    this->view = view;
}

Model::Player& GameController::GetUser1() { return model->GetUser1(); }
Model::Player& GameController::GetUser2() { return model->GetUser2(); }
void GameController::SetTurn(bool value) { model->SetTurn(value); }
bool GameController::GetTurn() { return model->GetTurn(); }
Board* GameController::GetBoard() { return model->GetBoard(); }
void GameController::SetExit(bool value) { model->SetExit(value); }
bool GameController::GetExit() { return model->GetExit(); }
void GameController::SetOption(char value) { model->SetOption(value); }
char GameController::GetOption() { return model->GetOption(); }

bool GameController::isWonGame()
{
	return model->isWonGame();
}
void GameController::SetWonGame(bool value)
{
	model->SetWonGame(value);
}
int GameController::GetPlayerWon()
{
	return model->GetPlayerWon();
}
void GameController::SetPlayerWon(int value)
{
	model->SetPlayerWon(value);
}
int GameController::getCommand() { return model->getCommand(); }

void GameController::DrawBoard()
{
    view->DrawBoard(model->GetBoard());
}
void GameController::DrawGameScreen()
{
    view->DrawGameScreen(model);
}

void GameController::ResetBoard()
{
    if (model->GetBoard()->getSize() == 0) return; // Phai goi constructor truoc khi reset data
    for (int i = 0; i < model->GetBoard()->getSize(); i++)
    {
        for (int j = 0; j < model->GetBoard()->getSize(); j++)
        {
            model->GetBoard()->SetXO(i, j, 0);
        }
    }
}
bool GameController::CheckFullBoard()
{
    int count = 0;
    for (int x = 0; x <= model->GetBoard()->getSize() - 1; x++)
        for (int y = 0; y <= model->GetBoard()->getSize() - 1; y++)
            if (model->GetBoard()->GetXO(x, y) == 0)
                count++;
    if (count == 0)
        return 1;
    return 0;
}
bool GameController::HoriWin(int x, int y)
{
    if (model->GetBoard()->GetXO(x, y) == 0) return false;
    int pl = model->GetBoard()->GetXO(x, y);
    int count = 0;
    int opcount = 0;
    for (int i = x; i >= 0; i--)
    {
        if (model->GetBoard()->GetXO(i, y) == pl) count++;
        else if (model->GetBoard()->GetXO(i, y) != 0)
        {
            opcount++;
            break;
        }
        else break;
    }
    for (int i = x + 1; i <= model->GetBoard()->getSize() - 1; i++)
    {
        if (model->GetBoard()->GetXO(i, y) == pl) count++;
        else if (model->GetBoard()->GetXO(i, y) != 0)
        {
            opcount++;
            break;
        }
        else break;
    }
    if (opcount >= 2) return false;
    if (count >= 4) return true;
    return false;
}
bool GameController::VertiWin(int x, int y)
{
    if (model->GetBoard()->GetXO(x, y) == 0) return false;
    int pl = model->GetBoard()->GetXO(x, y);
    int count = 0;
    int opcount = 0;
    for (int i = y; i >= 0; i--)
    {
        if (model->GetBoard()->GetXO(x, i) == pl) count++;
        else if (model->GetBoard()->GetXO(x, i) != 0)
        {
            opcount++;
            break;
        }
        else break;
    }
    for (int i = y + 1; i <= model->GetBoard()->getSize() - 1; i++)
    {
        if (model->GetBoard()->GetXO(x, i) == pl) count++;
        else if (model->GetBoard()->GetXO(x, i) != 0)
        {
            opcount++;
            break;
        }
        else break;
    }
    if (opcount >= 2) return false;
    if (count >= 4) return true;
    return false;
}
bool GameController::LCrossWin(int x, int y)
{
    if (model->GetBoard()->GetXO(x, y) == 0) return false;
    int pl = model->GetBoard()->GetXO(x, y);
    int count = 0;
    int opcount = 0;
    int m = min(x, y);
    for (int i = 0; i <= m; i++)
    {
        if (model->GetBoard()->GetXO(x - i, y - i) == pl) count++;
        else if (model->GetBoard()->GetXO(x - i, y - i) != 0)
        {
            opcount++;
            break;
        }
        else break;
    }
    m = min(model->GetBoard()->getSize() - x, model->GetBoard()->getSize() - y);
    for (int i = 1; i <= m; i++)
    {
        if (model->GetBoard()->GetXO(x + i, y + i) == pl) count++;
        else if (model->GetBoard()->GetXO(x + i, y + i) != 0)
        {
            opcount++;
            break;
        }
        else break;
    }
    if (opcount >= 2) return false;
    if (count >= 4) return true;
    return false;
}
bool GameController::RCrossWin(int x, int y)
{
    if (model->GetBoard()->GetXO(x, y) == 0) return false;
    int pl = model->GetBoard()->GetXO(x, y);
    int count = 0;
    int opcount = 0;
    int m = min(x, model->GetBoard()->getSize() - y);
    for (int i = 0; i <= m; i++)
    {
        if (model->GetBoard()->GetXO(x - i, y + i) == pl) count++;
        else if (model->GetBoard()->GetXO(x - i, y + i) != 0)
        {
            opcount++;
            break;
        }
        else break;
    }
    m = min(model->GetBoard()->getSize() - x, y);
    for (int i = 1; i <= m; i++)
    {
        if (model->GetBoard()->GetXO(x + i, y - i) == pl) count++;
        else if (model->GetBoard()->GetXO(x + i, y - i) != 0)
        {
            opcount++;
            break;
        }
        else break;
    }
    if (opcount >= 2) return false;
    if (count >= 4) return true;
    return false;
}

void GameController::InitGame(int pSize)
{
    model->Init(pSize);
}

void GameController::InputOption()
{
    char key;
    cin >> key;
    if (key >= '0' && key <= '9')
        model->SetOption(key);
    else model->SetOption('0');
}
bool GameController::isContinue() { return !model->GetExit(); }

char GameController::waitKeyBoard()
{
    return model->waitKeyBoard();
}

char GameController::askContinue()
{
    return model->getCommand();
}

void GameController::exitGame()
{
    system("cls");

    model->SetExit(true);
}

void GameController::CheckWinGame()
{
    for (int x = 0; x <= model->GetBoard()->getSize() - 1; x++)
    {
        for (int y = 0; y <= model->GetBoard()->getSize() - 1; y++)
        {
            if (HoriWin(x, y) || VertiWin(x, y) || LCrossWin(x, y) || RCrossWin(x, y))
            {
                SetWonGame(true);
                SetPlayerWon(model->GetBoard()->GetXO(x, y));
                if (isWonGame() == true) break;
            }
        }
        if (isWonGame() == true) break;
    }
}
void GameController::UpdateWinLoseRecord()
{
    if (GetPlayerWon() == VX)
    {
        model->GetUser1().IncreWin();
        model->GetUser2().IncreLose();
    }
    else if (GetPlayerWon() == VO)
    {
        model->GetUser1().IncreLose();
        model->GetUser2().IncreWin();
    }
    eraseOldResult(model->GetUser1().GetName());
    writeInFile(model->GetUser1());
    eraseOldResult(model->GetUser2().GetName());
    writeInFile(model->GetUser2());
}
void GameController::UpdateDrawRecord()
{
    model->GetUser1().IncreDraw();
    model->GetUser2().IncreDraw();
    eraseOldResult(model->GetUser1().GetName());
    writeInFile(model->GetUser1());
    eraseOldResult(model->GetUser2().GetName());
    writeInFile(model->GetUser2());
}
void GameController::PlayerInputAccount()
{
    model->GetUser1().Input();
    view->prompt("Input player 1: ");
    model->GetUser1().Input();
    if (checkName(model->GetUser1().GetName()) == 0)
    {
        writeInFile(model->GetUser1());
    }
    updateCurrentResult(model->GetUser1());
    view->prompt("Input player 2: ");
    model->GetUser2().Input();
    if (checkName(model->GetUser2().GetName()) == 0)
    {
        writeInFile(model->GetUser2());
    }
    updateCurrentResult(model->GetUser2());
}
void GameController::PlayerChooseAccount()
{
    view->prompt("List Account: \n", YELLOW);
    SetColor(WHITE);
    showAllInFile();
    view->prompt("Input name account you want to play or create new account:\n");
    PlayerInputAccount();
}
// Ham de nguoi choi nhap o can danh
void GameController::PlayerInputMove()
{
    int inputCol, inputRow;
    if (GetTurn() == true)
    {
        view->prompt("Player ", WHITE);
        view->prompt(model->GetUser1().GetName() + "'s ", P1);
        view->prompt("turn", WHITE);
        view->prompt(": ", YELLOW);
        do
        {
            cin >> inputRow;
            cin >> inputCol;
        } while (inputCol < 0 || inputCol > model->GetBoard()->getSize() - 1 || inputRow < 0 || inputRow > model->GetBoard()->getSize() - 1 || model->GetBoard()->GetXO(inputCol, inputRow) != 0);
        model->GetBoard()->SetXO(inputCol, inputRow, VX);
    }
    if (GetTurn() == false)
    {
        view->prompt("Player ", WHITE);
        view->prompt(model->GetUser2().GetName() + "'s ", P2);
        view->prompt("turn", WHITE);
        view->prompt(": ", YELLOW);
        do
        {
            cin >> inputRow;
            cin >> inputCol;
        } while (inputCol < 0 || inputCol > model->GetBoard()->getSize() - 1 || inputRow < 0 || inputRow > model->GetBoard()->getSize() - 1 || model->GetBoard()->GetXO(inputCol, inputRow) != 0);
        model->GetBoard()->SetXO(inputCol, inputRow, VO);
    }
}
void GameController::ChangePlayer()
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
void GameController::PlayInBoard()
{
    PlayerInputMove();
    ChangePlayer();
    CheckWinGame();
}
void GameController::NewGame()
{
    ResetBoard();
    SetTurn(true);
    SetExit(false);
    SetWonGame(false);
    SetPlayerWon(0);
}
void GameController::StartGame(string nameSearch)
{
    NewGame();
    while (isContinue())
    {
        system("cls");
        view->MainMenu();
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
                    if (CheckFullBoard())
                    {
                        UpdateDrawRecord();
                        view->prompt("DRAW!\n", YELLOW);
                        view->prompt("1.Play ", RED);
                        view->prompt("again\n", WHITE);
                        view->prompt("2.Back ", RED);
                        view->prompt("to MAIN MENU\n", WHITE);
                        view->prompt("Press number to choice: ", WHITE);
                        InputOption();
                        while (GetOption() < '1' || GetOption() > '2')
                        {
                            view->prompt("Press again\n");
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
                    view->prompt("Player ", WHITE);
                    if (GetPlayerWon() == VX)
                    {
                        view->prompt(model->GetUser1().GetName(), P1);
                    }
                    else if (GetPlayerWon() == VO)
                    {
                        view->prompt(model->GetUser2().GetName(), P2);
                    }
                    view->prompt(" won!\n", YELLOW);
                    view->prompt("1.Play ", RED);
                    view->prompt("again\n", WHITE);
                    view->prompt("2.Back ", RED);
                    view->prompt("to MAIN MENU\n", WHITE);
                    view->prompt("Press number to choice: ", WHITE);
                    InputOption();
                    while (GetOption() < '1' || GetOption() > '2')
                    {
                        view->prompt("Press again\n");
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
                view->prompt("This is DEMO version, please wait for a full version. We will update soon ;)\n");
                view->prompt("1.Back ", RED);
                view->prompt("to MAIN MENU\n", WHITE);
                view->prompt("Press number to choice: ", WHITE);
                InputOption();
                if (GetOption() == '1') SetOption('0');
            }
            break;
        case '3': // Player's Infomation
            while (GetOption() != '0')
            {
                system("cls");
                view->prompt("*-------", YELLOW);
                view->prompt("Players's Information", WHITE);
                view->prompt("-------*\n", YELLOW);
                view->prompt("1.Show ", RED);
                view->prompt("All Player\n", WHITE);
                view->prompt("2.Search ", RED);
                view->prompt("player by Name\n", WHITE);
                view->prompt("3.Back ", RED);
                view->prompt("to MAIN MENU\n", WHITE);
                view->prompt("Press number to choice:", WHITE);
                InputOption();
                switch (GetOption())
                {
                case '1': // Show All Player
                    while (GetOption() == '1')
                    {
                        system("cls");
                        view->prompt("*-------", YELLOW);
                        view->prompt("Players's Records", WHITE);
                        view->prompt("-------*\n", YELLOW);
                        SetColor(15);
                        showAllInFile();
                        view->prompt("1.Back ", RED);
                        view->prompt("to Player's Infomation\n", WHITE);
                        view->prompt("2.Back ", RED);
                        view->prompt("to MAIN MENU\n", WHITE);
                        view->prompt("Press number to choice:", WHITE);
                        InputOption();
                        while (GetOption() < '1' || GetOption() > '2')
                        {
                            view->prompt("Press again\n");
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
                        view->prompt("*-------", YELLOW);
                        view->prompt("Search Player by Name", WHITE);
                        view->prompt("-------*\n", YELLOW);
                        view->prompt("Input player's name: ", YELLOW);
                        cin >> nameSearch;
                        searchByName(nameSearch);
                        view->prompt("1.Continue ", RED);
                        view->prompt("Search\n", WHITE);
                        view->prompt("2.Back ", RED);
                        view->prompt("to Player's Infomation\n", WHITE);
                        view->prompt("3.Back ", RED);
                        view->prompt("to MAIN MENU\n", WHITE);
                        view->prompt("Press number to choice:", WHITE);
                        InputOption();
                        while (GetOption() < '1' || GetOption() > '3')
                        {
                            view->prompt("Press again\n");
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
                view->Guide();
                view->prompt("1.Back ", RED);
                view->prompt("to MAIN MENU\n", WHITE);
                view->prompt("Press number to choice: ", WHITE);
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
// Point Controller
PointController::PointController(Point* model)
{
    this->model = model;
}
int PointController::getX() { return model->getX(); }

int PointController::getY() { return model->getY(); }

int PointController::getCheck() { return model->getCheck(); }

void PointController::setX(int pX) { model->setX(pX); }

void PointController::setY(int pY) { model->setY(pY); }

bool PointController::setCheck(int pCheck)
{
    return model->setCheck(pCheck);
}

// Board Controller
BoardController::BoardController(Board* model)
{
    this->model = model;
}
int BoardController::getSize() { return model->getSize(); }

int BoardController::getXAt(int i, int j) { return model->getXAt(i, j); }

int BoardController::getYAt(int i, int j) { return model->getYAt(i, j); }

void BoardController::SetXO(int i, int j, int value)
{
    model->SetXO(i, j, value);
}
int BoardController::GetXO(int x, int y)
{
    return model->GetXO(x, y);
}

// Player Controller
PlayerController::PlayerController(Player* model)
{
    this->model = model;
}
string PlayerController::GetName() { return model->GetName(); }
void PlayerController::SetName(string value) { model->SetName(value); }
void PlayerController::Input()
{
    model->Input();
}

void PlayerController::SetWin(int value) { model->SetWin(value); }
void PlayerController::SetLose(int value) { model->SetLose(value); }
void PlayerController::SetDraw(int value) { model->SetDraw(value); }
int PlayerController::GetWin() { return model->GetWin(); }
int PlayerController::GetLose() { return model->GetLose(); }
int PlayerController::GetDraw() { return model->GetDraw(); }
void PlayerController::IncreWin() { model->IncreWin(); }
void PlayerController::IncreLose() { model->IncreLose(); }
void PlayerController::IncreDraw() { model->IncreDraw(); }