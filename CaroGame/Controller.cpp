#include "Controller.h"
#include "SaveDataToFile.h"
#include "MySQLConnect.h"
//#include <Windows.h>
#include <WS2tcpip.h>
#pragma comment (lib, "ws2_32.lib")

using namespace Controller;
// Game Controller
GameController::GameController(Game* model, GameView* view)
{
    this->model = model;
    this->view = view;
}
GameController::~GameController()
{
    delete model;
    delete view;
}
Model::Player& GameController::GetPlayer1() { return model->GetPlayer1(); }
Model::Player& GameController::GetPlayer2() { return model->GetPlayer2(); }
Model::User& GameController::GetUser() { return model->GetUser(); }
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
        model->GetPlayer1().IncreWin();
        model->GetPlayer2().IncreLose();
    }
    else if (GetPlayerWon() == VO)
    {
        model->GetPlayer1().IncreLose();
        model->GetPlayer2().IncreWin();
    }
    eraseOldResult(model->GetPlayer1().GetName());
    writePlayerInFile(model->GetPlayer1());
    eraseOldResult(model->GetPlayer2().GetName());
    writePlayerInFile(model->GetPlayer2());
}
void GameController::UpdateDrawRecord()
{
    model->GetPlayer1().IncreDraw();
    model->GetPlayer2().IncreDraw();
    eraseOldResult(model->GetPlayer1().GetName());
    writePlayerInFile(model->GetPlayer1());
    eraseOldResult(model->GetPlayer2().GetName());
    writePlayerInFile(model->GetPlayer2());
}
void GameController::ReplayLastGame() {
    list<Move>::iterator i;
    Game* replayGame = new Game(model->GetBoard()->getSize());
    list<Move> replayMoves = model->GetReplayMoves();
    i = replayMoves.begin();
    while (i != replayMoves.end()) {
        system("cls");
        replayGame->SetPlayer1(model->GetPlayer1());
        replayGame->SetPlayer2(model->GetPlayer2());
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
        replayGame->GetPlayer1().SetName(user1);
        replayGame->GetPlayer2().SetName(user2);
        replayGame->GetBoard()->SetXO((*i).col, (*i).row, (*i).value);
        view->DrawGameScreen(replayGame);
        //delay
        Sleep(1000);
        i++;
    }
}
void GameController::PlayerInputAccount()
{
    view->prompt("Input player 1: ");
    model->GetPlayer1().Input();
    if (checkPlayerName(model->GetPlayer1().GetName()) == 0)
    {
        writePlayerInFile(model->GetPlayer1());
    }
    updateCurrentResult(model->GetPlayer1());
    view->prompt("Input player 2: ");
    model->GetPlayer2().Input();
    while (model->GetPlayer2().GetName() == model->GetPlayer1().GetName())
    {
        view->prompt("Same name as player 1\n", RED);
        SetColor(WHITE);
        view->prompt("Input player 2: ");
        model->GetPlayer2().Input();
    }
    if (checkPlayerName(model->GetPlayer2().GetName()) == 0)
    {
        writePlayerInFile(model->GetPlayer2());
    }
    updateCurrentResult(model->GetPlayer2());
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
        view->prompt(model->GetPlayer1().GetName() + "'s ", P1);
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
        view->prompt(model->GetPlayer2().GetName() + "'s ", P2);
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
            PlayOnline();
            break;
        case '5':
            Guide();
            break;
        case '6':
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
                view->prompt(model->GetPlayer1().GetName(), P1);
            }
            else if (GetPlayerWon() == VO)
            {
                view->prompt(model->GetPlayer2().GetName(), P2);
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
void GameController::PlayOnline()
{
    char key;
    do
    {
        system("cls");
        view->MenuHeader(PLAY_ONLINE);
        view->PlayOnline();
        cin >> key;
        switch (key)
        {
        case '1':
            Login();
            if (model->GetUser().GetUserName() == "")
            {
                key = '2';
            }
            else
            {
                PlayOnlineAfterLogin();
            }
            break;
        case '2':
            Register();
            break;
        case '3':
            MainMenu();
            break;
        default:
            break;
        }
    } while (key < '1' || key > '3' || key == '2');
}
void GameController::PlayOnlineAfterLogin()
{
    char key;
    do
    {
        system("cls");
        view->MenuHeader(PLAY_ONLINE);
        view->PlayOnlineAfterLogin();
        cin >> key;
        switch (key)
        {
        case '1':
            PlayOnlineServer();
            break;
        case '2':
            PlayOnlineClient();
            break;
        case '3':
            UserInformation();
            break;
        case '4':
            Logout();
            MainMenu();
            break;
        default:
            break;
        }
    } while (key < '1' || key > '4' || key == '3');
}
void assignMove(string s, char& col, char& row)
{
    string assign;
    int count = 0;
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] != ',')
        {
            assign += s[i];
        }
        else
        {
            if (count == 0)
            {
                col = stoi(assign);
                assign = "";
                count++;
            }
            else if (count == 1)
            {
                row = stoi(assign);
                assign = "";
            }
        }
    }
}
void GameController::PlayOnlineServer()
{
    // Cap nhat lai user moi khi choi lai game
    string username = model->GetUser().GetUserName();
    model->SetUser(GetUserFromDatabase(username));
    // Dua thong tin user vao player 1
    model->GetPlayer1().SetName(model->GetUser().GetUserName());
    model->GetPlayer1().SetWin(model->GetUser().GetWin());
    model->GetPlayer1().SetLose(model->GetUser().GetLose());
    model->GetPlayer1().SetDraw(model->GetUser().GetDraw());

    WSADATA wsData;
    WORD ver = MAKEWORD(2, 2);

    int wsOk = WSAStartup(ver, &wsData);
    if (wsOk != 0)
    {
        cerr << "Can't Initialize winsock! Quitting" << endl;
        return;
    }

    // Create a socket
    SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening == INVALID_SOCKET)
    {
        cerr << "Can't create a socket! Quitting" << endl;
        return;
    }

    // Bind the ip address and port to a socket
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(PORT);
    hint.sin_addr.S_un.S_addr = INADDR_ANY; // Could also use inet_pton .... 

    bind(listening, (sockaddr*)&hint, sizeof(hint));
    
    // Tell Winsock the socket is for listening 
    listen(listening, SOMAXCONN);
    view->prompt("Wait other player...");

    // Wait for a connection
    sockaddr_in client;
    int clientSize = sizeof(client);
    SOCKET clientSocket = accept(listening, (sockaddr*)&client, &clientSize);
    int connResult = connect(clientSocket, (sockaddr*)&hint, sizeof(hint));
    
    char host[NI_MAXHOST];		// Client's remote name
    char service[NI_MAXSERV];	// Service (i.e. port) the client is connect on

    ZeroMemory(host, NI_MAXHOST); // same as memset(host, 0, NI_MAXHOST);
    ZeroMemory(service, NI_MAXSERV);
    if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
    {
        cout << host << " connected on port " << service << endl;
    }
    else
    {
        inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
        cout << host << " connected on port " <<
            ntohs(client.sin_port) << endl;
    }

    // Close listening socket
    closesocket(listening);

    //While loop: accept and echo message back to client
    string player1Name, player2Name, player1Move, player2Move;
    char buffer[4096];
    player1Name = model->GetPlayer1().GetName();
    int sendResult = send(clientSocket, player1Name.c_str(), player1Name.size() + 1, 0);
    ZeroMemory(buffer, 4096);
    int bytesReceived = recv(clientSocket, buffer, 4096, 0);
    player2Name = string(buffer, 0, bytesReceived);
    // Nhan ten player 2 tu client
    model->GetPlayer2().SetName(player2Name);
    model->GetPlayer2().SetWin(0);
    model->GetPlayer2().SetLose(0);
    model->GetPlayer2().SetDraw(0);

    ResetReplayMoves();
    do
    {
        if (isWonGame() == false)
        {
            system("cls");
            DrawGameScreen();
            if (CheckFullBoard() == false)
            {
                // Player Input Move
                char charCol, charRow; // ky tu nguoi choi nhap
                int inputCol = -1, inputRow = -1; // chi so hang, cot nguoi choi nhap
                if (GetTurn() == true)
                {
                    view->prompt("Player ", WHITE);
                    view->prompt(model->GetPlayer1().GetName() + "'s ", P1);
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
                    player1Move = to_string(charCol) + "," + to_string(charRow) + ",";
                    int sendResult = send(clientSocket, player1Move.c_str(), player1Move.size() + 1, 0);
                }
                if (GetTurn() == false)
                {
                    ZeroMemory(buffer, 4096);
                    int bytesReceived = recv(clientSocket, buffer, 4096, 0);
                    player2Move = string(buffer, 0, bytesReceived);
                    // Nhan nuoc di cua Player 2 tu client
                    assignMove(player2Move, charCol, charRow);
                    inputRow = (int)charRow - 48;
                    inputCol = (int)charCol - 48;
                    model->GetBoard()->SetXO(inputCol, inputRow, VO);
                    SaveMove(inputCol, inputRow, VO);
                }
                ChangePlayer();
                CheckWinGame();
            }
        }
        if (isWonGame() == true)
        {
            UpdateUserInDatabase(SERVER);
            InsertMatchToDatabase();
            system("cls");
            DrawGameScreen();
            view->prompt("Player ", WHITE);
            if (GetPlayerWon() == VX)
            {
                view->prompt(model->GetPlayer1().GetName(), P1);
            }
            else if (GetPlayerWon() == VO)
            {
                view->prompt(model->GetPlayer2().GetName(), P2);
            }
            view->prompt(" won!\n", YELLOW);
            AskToSaveReplay();
        }
    } while (isWonGame() == false && CheckFullBoard() == false);
    if (CheckFullBoard())
    {
        UpdateUserInDatabase(SERVER);
        InsertMatchToDatabase();
        view->prompt("DRAW!\n", YELLOW);
        AskToSaveReplay();
    }
    // Close the socket
    closesocket(clientSocket);

    // Cleanup winsock
    WSACleanup();
    GameOverMenuOnline(SERVER);
}
void GameController::PlayOnlineClient()
{
    // Cap nhat lai user moi khi choi lai game
    string username = model->GetUser().GetUserName();
    model->SetUser(GetUserFromDatabase(username));
    // Dua thong tin user vao player 2
    model->GetPlayer2().SetName(model->GetUser().GetUserName());
    model->GetPlayer2().SetWin(model->GetUser().GetWin());
    model->GetPlayer2().SetLose(model->GetUser().GetLose());
    model->GetPlayer2().SetDraw(model->GetUser().GetDraw());
    string ipAddress;			            // IP Address of the server
    int port = PORT;						// Listening port # on the server
    view->prompt("(Input \"localhost\" if server is working on your PC)\n", YELLOW);
    do
    {
        view->prompt("Input server's ip address: ", WHITE);
        cin >> ipAddress;
        if (ipAddress == "localhost") ipAddress = "127.0.0.1";
        if (!isIPAddress(ipAddress))
        {
            view->prompt("Invalid ip address.\n", YELLOW);
        }
    } while (!isIPAddress(ipAddress));
    
    // Initialize WinSock
    WSAData data;
    WORD ver = MAKEWORD(2, 2);
    int wsResult = WSAStartup(ver, &data);
    if (wsResult != 0)
    {
        cerr << "Can't start Winsock, Err #" << wsResult << endl;
        return;
    }

    // Create socket
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET)
    {
        cerr << "Can't create socket, Err #" << WSAGetLastError() << endl;
        WSACleanup();
        return;
    }

    // Fill in a hint structure
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);
    // Connect to server
    int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
    if (connResult == SOCKET_ERROR)
    {
        cerr << "Can't connect to server, Err #" << WSAGetLastError() << endl;
        closesocket(sock);
        WSACleanup();
        //delay
        Sleep(1000);
        PlayOnlineAfterLogin();
        return;
    }

    // Do-while loop to send and receive data
    string player1Name, player2Name, player1Move, player2Move;
    char buffer[4096];
    ZeroMemory(buffer, 4096);
    int bytesReceived = recv(sock, buffer, 4096, 0);
    player1Name = string(buffer, 0, bytesReceived);
    // Nhan ten player 1 tu server
    model->GetPlayer1().SetName(player1Name);
    model->GetPlayer1().SetWin(0);
    model->GetPlayer1().SetLose(0);
    model->GetPlayer1().SetDraw(0);
    
    player2Name = model->GetPlayer2().GetName();
    int sendResult = send(sock, player2Name.c_str(), player2Name.size() + 1, 0);
    ResetReplayMoves();
    do
    {
        if (isWonGame() == false)
        {
            system("cls");
            DrawGameScreen();
            if (CheckFullBoard() == false)
            {
                // Player Input Move
                char charCol, charRow; // ky tu nguoi choi nhap
                int inputCol = -1, inputRow = -1; // chi so hang, cot nguoi choi nhap
                if (GetTurn() == true)
                {
                    int bytesReceived = recv(sock, buffer, 4096, 0);
                    player1Move = string(buffer, 0, bytesReceived);
                    // Nhan nuoc di cua player 1 tu server
                    assignMove(player1Move, charCol, charRow);
                    inputRow = (int)charRow - 48;
                    inputCol = (int)charCol - 48;
                    model->GetBoard()->SetXO(inputCol, inputRow, VX);
                    SaveMove(inputCol, inputRow, VX);
                }
                if (GetTurn() == false)
                {
                    view->prompt("Player ", WHITE);
                    view->prompt(model->GetPlayer2().GetName() + "'s ", P2);
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
                    player2Move = to_string(charCol) + "," + to_string(charRow) + ",";
                    sendResult = send(sock, player2Move.c_str(), player2Move.size() + 1, 0);
                }
                ChangePlayer();
                CheckWinGame();
            }
        }
        if (isWonGame() == true)
        {
            UpdateUserInDatabase(CLIENT);
            system("cls");
            DrawGameScreen();
            view->prompt("Player ", WHITE);
            if (GetPlayerWon() == VX)
            {
                view->prompt(model->GetPlayer1().GetName(), P1);
            }
            else if (GetPlayerWon() == VO)
            {
                view->prompt(model->GetPlayer2().GetName(), P2);
            }
            view->prompt(" won!\n", YELLOW);
            AskToSaveReplay();
        }
    } while (isWonGame() == false && CheckFullBoard() == false);
    if (CheckFullBoard())
    {
        UpdateUserInDatabase(CLIENT);
        view->prompt("DRAW!\n", YELLOW);
        AskToSaveReplay();
    }
    // Gracefully close down everything
    closesocket(sock);
    GameOverMenuOnline(CLIENT);
}
void GameController::GameOverMenuOnline(int SoC)
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
            if (SoC == SERVER) PlayOnlineServer();
            else if(SoC == CLIENT) PlayOnlineClient();
            break;
        case '2':
            ResetGame();
            Logout();
            MainMenu();
            break;
        default:
            view->prompt("Press again\n");
            break;
        }
    } while (key < '1' || key > '2');
}
void GameController::UserInformation()
{
    system("cls");
    view->MenuHeader(USER_INFORMATION);
    GetUserInfoFromDatabase();
    system("pause");
}
void GameController::StartGame()
{
    ResetGame();
    while (isContinue())
    {
        MainMenu();
    }
}
void GameController::Login()
{
    string username, password;
    view->prompt("Login:\n", YELLOW);
    view->prompt("Username: ", WHITE);
    username = InputStringName(8);
    view->prompt("Password: ", WHITE);
    password = InputStringName(8);
    MySQLConnect sql;
    sql.getConnection();
    User user;
    User temp = sql.findUserByUserNameAndPassWord(username, password);
    if (temp.isOnline())
    {
        view->prompt("This account is already logged in somewhere else\n", YELLOW);
        SetColor(WHITE);
        system("pause");
    }
    else
    {
        user = temp;
    }
    model->SetUser(user);
    if (model->GetUser().GetUserName() != "")
    {
        view->prompt("Login successful!\n");
        system("pause");
        model->GetUser().SetStatusOnline(true);
        UpdateUserInDatabase(0);
    }
}
void GameController::Register()
{
    string username, password;
    view->prompt("Register:\n", YELLOW);
    view->prompt("Username: ", WHITE);
    username = InputStringName(8);
    view->prompt("Password: ", WHITE);
    password = InputStringName(8);
    User user;
    user.SetUserName(username);
    user.SetPassWord(password);
    user.SetWin(0);
    user.SetLose(0);
    user.SetDraw(0);
    MySQLConnect sql;
    sql.getConnection();
    sql.insertUser(user);
}
User GameController::GetUserFromDatabase(string username)
{
    MySQLConnect sql;
    sql.getConnection();
    User user = sql.findUserByUserName(username);
    return user;
}
void GameController::GetUserInfoFromDatabase()
{
    MySQLConnect sql;
    sql.getConnection();
    SetColor(WHITE);
    sql.getUserInfoByUserName(model->GetUser().GetUserName());
    view->prompt("History match:\n", YELLOW);
    SetColor(WHITE);
    sql.findMatchByUserName(model->GetUser().GetUserName());
}
void GameController::InsertMatchToDatabase()
{
    Match match;
    match.SetPlayer1(model->GetPlayer1().GetName());
    match.SetPlayer2(model->GetPlayer2().GetName());
    if (isWonGame() == true && model->GetPlayerWon() == VX)
    {
        match.SetPlayerWin(model->GetPlayer1().GetName());
    }
    else if (isWonGame() == true && model->GetPlayerWon() == VO)
    {
        match.SetPlayerWin(model->GetPlayer2().GetName());
    }
    else if (isWonGame() == false && CheckFullBoard() == true)
    {
        match.SetPlayerWin("DRAW");
    }
    MySQLConnect sql;
    sql.getConnection();
    sql.insertMatch(match);
}
void GameController::UpdateUserInDatabase(int SoC)
{
    MySQLConnect sql;
    sql.getConnection();
    if (SoC == 0)
    {
        User user = model->GetUser();
        sql.updateUser(user);
        return;
    }
    if (isWonGame() == true && model->GetPlayerWon() == VX)
    {
        model->GetPlayer1().IncreWin();
        model->GetPlayer2().IncreLose();
    }
    else if (isWonGame() == true && model->GetPlayerWon() == VO)
    {
        model->GetPlayer1().IncreLose();
        model->GetPlayer2().IncreWin();
    }
    else if (isWonGame() == false && CheckFullBoard() == true)
    {
        model->GetPlayer1().IncreDraw();
        model->GetPlayer2().IncreDraw();
    }
    if (SoC == SERVER)
    {
        // User 1
        User user1 = sql.findUserByUserName(model->GetPlayer1().GetName());
        user1.SetWin(model->GetPlayer1().GetWin());
        user1.SetLose(model->GetPlayer1().GetLose());
        user1.SetDraw(model->GetPlayer1().GetDraw());
        sql.updateUser(user1);
    }
    else if (SoC == CLIENT)
    {
        // User 2
        User user2 = sql.findUserByUserName(model->GetPlayer2().GetName());
        user2.SetWin(model->GetPlayer2().GetWin());
        user2.SetLose(model->GetPlayer2().GetLose());
        user2.SetDraw(model->GetPlayer2().GetDraw());
        sql.updateUser(user2);
    }
}
void GameController::Logout()
{
    User user = GetUserFromDatabase(model->GetUser().GetUserName());
    model->SetUser(user);
    model->GetUser().SetStatusOnline(false);
    UpdateUserInDatabase(0);
}
// Point Controller
PointController::PointController(Point* model)
{
    this->model = model;
}
PointController::~PointController()
{
    delete model;
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
BoardController::~BoardController()
{
    delete model;
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
PlayerController::~PlayerController()
{
    delete model;
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