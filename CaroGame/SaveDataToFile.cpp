#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <vector>
#include <iomanip>
#include "SaveDataToFile.h"
#include "Common.h"

using namespace std;

bool is_file_exist(const char* fileName)
{
    std::ifstream infile(fileName);
    return infile.good();
}
// record
void createRecordFile()
{
    ofstream fout;
    fout.open(recordfile, ios::out | ios::app);
    fout << "  Account    Win    Lose    Draw\n";
    fout.close();
}

void writePlayerInFile(Player player)
{
    ofstream fout;
    fout.open(recordfile, ios::out | ios::app);
    fout << setw(8) << player.GetName();
    fout << setw(8) << player.GetWin();
    fout << setw(8) << player.GetLose();
    fout << setw(8) << player.GetDraw();
    fout << '\n';
    fout.close();
}
void showAllRecordInFile()
{
    if (!is_file_exist(recordfile)) { createRecordFile(); }
    ifstream fin;
    fin.open(recordfile);
    char charsInLine[200];
    int count = 0;
    while (!fin.eof()) {
        fin.getline(charsInLine, 200);
        cout << charsInLine << endl;
    }
    fin.close();
}
bool checkPlayerName(string name)
{
    if (!is_file_exist(recordfile)) { createRecordFile(); }
    ifstream fin;
    fin.open(recordfile);
    string namePlayer;
    string charsInLine;
    while (!fin.eof())
    {
        getline(fin, charsInLine);
        fin >> namePlayer;
        if (namePlayer == name)
        {
            return true;
        }
    }
    fin.close();
    return false;
}
void searchPlayerByName(string name)
{
    if (!is_file_exist(recordfile)) { createRecordFile(); }
    string namePlayer;
    int numWin, numLose, numDraw;
    ifstream fin;
    fin.open(recordfile);
    string charsInLine;
    while (!fin.eof())
    {
        getline(fin, charsInLine);
        fin >> namePlayer >> numWin >> numLose >> numDraw;
        if (namePlayer == name)
        {
            SetColor(YELLOW);
            cout << "Player's Information\n";
            SetColor(WHITE);
            cout << "Name: " << namePlayer << endl;
            cout << "Number of Wins: " << numWin << endl;
            cout << "Number of Losses: " << numLose << endl;
            cout << "Number of Draws: " << numDraw << endl;
            findPlayerSameRank(namePlayer, numWin, numLose);
            return;
        }
    }
    fin.close();
    SetColor(YELLOW);
    cout << "Don't find any player name: " << name << endl;
}
void findPlayerSameRank(string name, int win, int lose)
{
    if (!is_file_exist(recordfile)) { createRecordFile(); }
    string namePlayer;
    string temp; // bien tranh ghi lai mot ten nhieu lan
    int numWin, numLose, numDraw;
    ifstream fin;
    fin.open(recordfile);
    string charsInLine;
    while (!fin.eof())
    {
        getline(fin, charsInLine);
        fin >> namePlayer >> numWin >> numLose >> numDraw;
        if ((namePlayer != name) && (numWin == win) && (numLose - lose >= -1) && (numLose - lose <= 1))
        {
            if (temp == namePlayer) return;
            SetColor(YELLOW);
            cout << "Player Same Rank\n";
            SetColor(WHITE);
            cout << "Name: " << namePlayer << endl;
            cout << "Number of Wins: " << numWin << endl;
            cout << "Number of Losses: " << numLose << endl;
            cout << "Number of Draws: " << numDraw << endl;
            temp = namePlayer;
        }
    }
    fin.close();
}
void eraseOldResult(string name)
{
    if (!is_file_exist(recordfile)) { createRecordFile(); }
    string line;
    ifstream myfile;
    myfile.open(recordfile);
    ofstream temp;
    temp.open("temp.ini");
    while (getline(myfile, line))
    {
        if (line.substr(8 - name.size(), name.size()) != name)
            temp << line << endl;
    }
    myfile.close();
    temp.close();
    remove(recordfile);
    rename("temp.ini", recordfile);
}
void updateCurrentResult(Player& player)
{
    if (!is_file_exist(recordfile)) { createRecordFile(); }
    char arr[] = "     ";
    string namePlayer; int numWin, numLose, numDraw;
    ifstream fin;
    fin.open(recordfile);
    string charsInLine;
    while (!fin.eof())
    {
        getline(fin, charsInLine);
        fin >> namePlayer >> numWin >> numLose >> numDraw;
        if (player.GetName() == namePlayer)
        {
            player.SetWin(numWin);
            player.SetLose(numLose);
            player.SetDraw(numDraw);
        }
    }
    fin.close();
}

// replay
void createReplayFile()
{
    ofstream fout;
    fout.open(replayfile, ios::out | ios::app);
    fout << "      id    Player 1    Player 2\n";
    fout.close();
}
bool checkGameId(char id)
{
    if (!is_file_exist(replayfile)) { createReplayFile(); }
    ifstream fin;
    fin.open(replayfile);
    char idGame;
    string charsInLine;
    while (!fin.eof())
    {
        getline(fin, charsInLine);
        fin >> idGame;
        if (idGame == id)
        {
            return true;
        }
    }
    fin.close();
    return false;
}
void saveReplayInFile(Game* game)
{
    char id = '0';
    char arr[] = "         ";
    string line;
    int count = 0;
    ofstream f;
    f.open(replayfile, ios::out | ios::app);
    while (checkGameId(id) == true)
    {
        id++;
    }
    f << setw(8) << id;
    f << setw(12) << game->GetUser1().GetName();
    f << setw(12) << game->GetUser2().GetName();
    f << '\n';
    list<Move>::iterator j;
    Game* replayGame = new Game(game->GetBoard()->getSize());
    list<Move> replayMoves = game->GetReplayMoves();
    j = replayMoves.begin();
    while (j != replayMoves.end()) {
        f << setw(8) << '-' << arr << (*j).col << ' ' << (*j).row << ' ' << (*j).value << endl;
        j++;
    }
    f.close();
}
void showAllReplayGameInFile()
{
    if (!is_file_exist(replayfile)) { createReplayFile(); }
    ifstream fin;
    fin.open(replayfile);
    string line;
    while (getline(fin, line))
    {
        if (line.substr(8 - sizeof(char), sizeof(char)) != "-")
        {
            cout << line << endl;
        }
    }
    fin.close();
}
list<Move> getReplayMoveById(char id)
{
    list<Move> replayMoves;
    int col, row, value;
    if (!is_file_exist(replayfile)) { createReplayFile(); }
    char idGame;
    ifstream fin;
    fin.open(replayfile);
    string charsInLine;
    while (!fin.eof())
    {
        getline(fin, charsInLine);
        fin >> idGame;
        if (idGame == id)
        { 
            do
            {
                getline(fin, charsInLine);
                fin >> idGame >> col >> row >> value;
                if (idGame == '-')
                {
                    Move move;
                    move.col = col;
                    move.row = row;
                    move.value = value;
                    replayMoves.push_back(move);
                }
            }while (idGame == '-' && !fin.eof());
            return replayMoves;
        }
    }
    fin.close();
    SetColor(YELLOW);
    cout << "Don't find any game id: " << id << endl;
    return replayMoves;
}
string getReplayPlayerById(char id, int user)
{
    if (!is_file_exist(replayfile)) { createReplayFile(); }
    char idGame;
    string user1, user2;
    ifstream fin;
    fin.open(replayfile);
    string charsInLine;
    while (!fin.eof())
    {
        getline(fin, charsInLine);
        fin >> idGame >> user1 >> user2;
        if (idGame == id)
        {
            if (user == 1)
                return user1;
            else if (user == 2)
                return user2;
            else
                return "";
        }
    }
    fin.close();
    return "";
}