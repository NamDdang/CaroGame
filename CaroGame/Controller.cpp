#include "Controller.h"
#include "SaveDataToFile.h"
#include <Windows.h>
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

void GameController::InitGame(int pSize)
{
    model->Init(pSize);
}
void GameController::SaveMove(int col, int row, int value) {
    model->SaveMove(col, row, value);
}
void GameController::ResetReplayMoves()
{
    model->ResetReplayMoves();
}
bool GameController::isContinue() { return !model->GetExit(); }

void GameController::exitGame()
{
    system("cls");

    model->SetExit(true);
    exit(0);
}

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
    writePlayerInFile(model->GetUser1());
    eraseOldResult(model->GetUser2().GetName());
    writePlayerInFile(model->GetUser2());
}
void GameController::UpdateDrawRecord()
{
    model->GetUser1().IncreDraw();
    model->GetUser2().IncreDraw();
    eraseOldResult(model->GetUser1().GetName());
    writePlayerInFile(model->GetUser1());
    eraseOldResult(model->GetUser2().GetName());
    writePlayerInFile(model->GetUser2());
}
void GameController::ReplayLastGame() {
    list<Move>::iterator i;
    Game* replayGame = new Game(model->GetBoard()->getSize());
    list<Move> replayMoves = model->GetReplayMoves();
    i = replayMoves.begin();
    while (i != replayMoves.end()) {
        system("cls");
        replayGame->SetUser1(model->GetUser1());
        replayGame->SetUser2(model->GetUser2());
        replayGame->GetBoard()->SetXO((*i).col, (*i).row, (*i).value);
        view->DrawGameScreen(replayGame);
        //delay
        Sleep(1000);
        i++;
    }
}
void GameController::ReplayGameById(char id) {
    list<Move> replayMoves = getReplayMoveById(id);
    string user1 = getReplayPlayerById(id, 1);
    string user2 = getReplayPlayerById(id, 2);
    list<Move>::iterator i;
    Game* replayGame = new Game(model->GetBoard()->getSize());
    i = replayMoves.begin();
    while (i != replayMoves.end()) {
        system("cls");
        replayGame->GetUser1().SetName(user1);
        replayGame->GetUser2().SetName(user2);
        replayGame->GetBoard()->SetXO((*i).col, (*i).row, (*i).value);
        view->DrawGameScreen(replayGame);
        //delay
        Sleep(1000);
        i++;
    }
}
void GameController::PlayerInputAccount()
{
    //model->GetUser1().Input();
    view->prompt("Input player 1: ");
    model->GetUser1().Input();
    if (checkPlayerName(model->GetUser1().GetName()) == 0)
    {
        writePlayerInFile(model->GetUser1());
    }
    updateCurrentResult(model->GetUser1());
    view->prompt("Input player 2: ");
    model->GetUser2().Input();
    if (checkPlayerName(model->GetUser2().GetName()) == 0)
    {
        writePlayerInFile(model->GetUser2());
    }
    updateCurrentResult(model->GetUser2());
}
void GameController::PlayerChooseAccount()
{
    view->prompt("List Account: \n", YELLOW);
    SetColor(WHITE);
    showAllRecordInFile();
    view->prompt("Input name account you want to play or create new account:\n");
    PlayerInputAccount();
}
// Ham de nguoi choi nhap o can danh
void GameController::PlayerInputMove()
{
    char charCol, charRow; // ky tu nguoi choi nhap
    int inputCol = -1, inputRow = -1; // chi so hang, cot nguoi choi nhap
    if (GetTurn() == true)
    {
        view->prompt("Player ", WHITE);
        view->prompt(model->GetUser1().GetName() + "'s ", P1);
        view->prompt("turn", WHITE);
        view->prompt(": ", YELLOW);
        do
        {
            cin >> charRow;
            cin >> charCol;
            inputRow = (int)charRow - 48;
            inputCol = (int)charCol - 48;
        } while (inputCol < 0 || inputCol > model->GetBoard()->getSize() - 1 || inputRow < 0 || inputRow > model->GetBoard()->getSize() - 1 || model->GetBoard()->GetXO(inputCol, inputRow) != 0);
        model->GetBoard()->SetXO(inputCol, inputRow, VX);
        SaveMove(inputCol, inputRow, VX);
    }
    if (GetTurn() == false)
    {
        view->prompt("Player ", WHITE);
        view->prompt(model->GetUser2().GetName() + "'s ", P2);
        view->prompt("turn", WHITE);
        view->prompt(": ", YELLOW);
        do
        {
            cin >> charRow;
            cin >> charCol;
            inputRow = (int)charRow - 48;
            inputCol = (int)charCol - 48;
        } while (inputCol < 0 || inputCol > model->GetBoard()->getSize() - 1 || inputRow < 0 || inputRow > model->GetBoard()->getSize() - 1 || model->GetBoard()->GetXO(inputCol, inputRow) != 0);
        model->GetBoard()->SetXO(inputCol, inputRow, VO);
        SaveMove(inputCol, inputRow, VO);
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
void GameController::ResetGame()
{
    ResetBoard();
    SetTurn(true);
    SetExit(false);
    SetWonGame(false);
    SetPlayerWon(0);
}
void GameController::MainMenu()
{
    char key;
    do
    {
        system("cls");
        view->MenuHeader(MAIN_MENU);
        view->MainMenu();
        cin >> key;
        switch (key)
        {
        case '1':
            PlayWithOtherPlayer();
            break;
        case '2':
            Replay();
            break;
        case '3':
            PlayerInformationMenu();
            break;
        case '4':
            Guide();
            break;
        case '5':
            exitGame();
            break;
        default:
            break;
        }
    } while (key < '1' || key > '5');
}
void GameController::PlayWithOtherPlayer()
{
    system("cls");
    SetColor(15);
    PlayerChooseAccount();
    ResetReplayMoves();
    do
    {
        if (isWonGame() == false)
        {
            system("cls");
            DrawGameScreen();
            if (CheckFullBoard())
            {
                UpdateDrawRecord();
                view->prompt("DRAW!\n", YELLOW);
                AskToSaveReplay();
                GameOverMenu();
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
            AskToSaveReplay();
            GameOverMenu();
        }
    } while (isWonGame() == false);
}
void GameController::GameOverMenu()
{
    char key;
    view->GameOverMenu();
    do
    {
        cin >> key;
        switch (key)
        {
        case '1':
            ResetGame();
            ResetReplayMoves();
            break;
        case '2':
            ResetGame();
            MainMenu();
            break;
        default:
            view->prompt("Press again\n");
            break;
        }
    } while (key < '1' || key > '2');
}
void GameController::AskToSaveReplay()
{
    char key;
    view->AskToSaveReplay();
    do
    {
        cin >> key;
        switch (key)
        {
        case '1':
            saveReplayInFile(model);
            view->prompt("Saved successfully!\n", YELLOW);
            break;
        case '2':
            // Do nothing
            break;
        default:
            view->prompt("Press again\n");
            break;
        }
    } while (key < '1' || key > '2');
}
void GameController::Replay()
{
    char key;
    system("cls");
    view->MenuHeader(REPLAY);
    view->prompt("History Game: \n", YELLOW);
    SetColor(WHITE);
    showAllReplayGameInFile();
    view->prompt("Input id game you want to replay:");
    char idGame;
    cin >> idGame;
    do
    {
        system("cls");
        ReplayGameById(idGame);
        view->Replay();
        cin >> key;
        while (key < '1' || key > '3')
        {
            view->prompt("Press again\n");
            cin >> key;
        }
        switch (key)
        {
        case '1':
            break;
        case '2':
            Replay();
            break;
        case '3':
            MainMenu();
            break;
        default:
            view->prompt("Press again\n");
            break;
        }
    } while (key < '2' || key > '3');
}
void GameController::PlayerInformationMenu()
{
    char key;
    do
    {
        system("cls");
        view->MenuHeader(PLAYER_INFORMATION);
        view->PlayerInfomationMenu();
        cin >> key;
        switch (key)
        {
        case '1':
            ShowAllPlayer();
            break;
        case '2':
            SearchPlayerByName();
            break;
        case '3':
            MainMenu();
            break;
        default:
            break;
        }
    } while (key < '1' || key > '3');
}
void GameController::ShowAllPlayer()
{
    char key;
    do
    {
        system("cls");
        view->MenuHeader(SHOW_ALL_PLAYER);
        SetColor(15);
        showAllRecordInFile();
        view->ShowAllPlayer();
        cin >> key;
        switch (key)
        {
        case '1':
            PlayerInformationMenu();
            break;
        case '2':
            MainMenu();
            break;
        default:
            break;
        }
    } while (key < '1' || key > '2');
}
void GameController::SearchPlayerByName()
{
    system("cls");
    string nameSearch;
    char key;
    view->MenuHeader(SEARCH_PLAYER_BY_NAME);
    view->prompt("Input player's name: ", YELLOW);
    cin >> nameSearch;
    do
    {
        system("cls");
        view->MenuHeader(SEARCH_PLAYER_BY_NAME);
        searchPlayerByName(nameSearch);
        view->SearchPlayerByName();
        cin >> key;
        switch (key)
        {
        case '1':
            SearchPlayerByName();
            break;
        case '2':
            PlayerInformationMenu();
            break;
        case '3':
            MainMenu();
            break;
        default:
            break;
        }
    } while (key < '1' || key > '3');
}
void GameController::Guide()
{
    char key;
    do
    {
        system("cls");
        view->MenuHeader(GUIDE);
        view->Guide();
        cin >> key;
        switch (key)
        {
        case '1':
            MainMenu();
            break;
        default:
            break;
        }
    } while (key != '1');
}
void GameController::StartGame()
{
    ResetGame();
    while (isContinue())
    {
        MainMenu();
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