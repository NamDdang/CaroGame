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

void createFile()
{
    ofstream fout;
    fout.open(filename, ios::out | ios::app);
    fout << "  Account    Win  Lose  Draw\n";
    fout.close();
}

void writeInFile(Player player)
{
    char arr[] = "     ";
    ofstream fout;
    fout.open(filename, ios::out | ios::app);
    fout << setw(8) << player.GetName(); fout << arr;
    fout << player.GetWin(); fout << arr;
    fout << player.GetLose(); fout << arr;
    fout << player.GetDraw(); fout << arr;
    fout << '\n';
    fout.close();
}
void showAllInFile()
{
    if (!is_file_exist(filename)) { createFile(); }
    ifstream fin;
    fin.open(filename);
    char charsInLine[200];
    int count = 0;
    while (!fin.eof()) {
        fin.getline(charsInLine, 200);
        cout << charsInLine << endl;
    }
    fin.close();
}
bool checkName(string name)
{
    if (!is_file_exist(filename)) { createFile(); }
    ifstream fin;
    fin.open(filename);
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
void searchByName(string name)
{
    if (!is_file_exist(filename)) { createFile(); }
    string namePlayer;
    int numWin, numLose, numDraw;
    ifstream fin;
    fin.open(filename);
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
}
void findPlayerSameRank(string name, int win, int lose)
{
    if (!is_file_exist(filename)) { createFile(); }
    string namePlayer;
    string temp; // bien tranh ghi lai mot ten nhieu lan
    int numWin, numLose, numDraw;
    ifstream fin;
    fin.open(filename);
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
}
void eraseOldResult(string name)
{
    if (!is_file_exist(filename)) { createFile(); }
    string line;
    ifstream myfile;
    myfile.open(filename);
    ofstream temp;
    temp.open("temp.ini");
    while (getline(myfile, line))
    {
        if (line.substr(8 - name.size(), name.size()) != name)
            temp << line << endl;
    }
    myfile.close();
    temp.close();
    remove(filename);
    rename("temp.ini", filename);
}
void updateCurrentResult(Player& player)
{
    if (!is_file_exist(filename)) { createFile(); }
    char arr[] = "     ";
    string namePlayer; int numWin, numLose, numDraw;
    ifstream fin;
    fin.open(filename);
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