#ifndef SAVEDATATOFILE_H
#define SAVEDATATOFILE_H
#include "Player.h"
static const char* filename = "PlayersRecord.ini";
bool is_file_exist(const char*);
void createFile();
void writeInFile(Player player);
void showAllInFile();
bool checkName(string name);
void searchByName(string name);
void eraseOldResult(string name);
void updateCurrentResult(Player& player);
#endif // SAVEDATATOFILE_H
