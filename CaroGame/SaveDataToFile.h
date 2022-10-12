#ifndef SAVEDATATOFILE_H
#define SAVEDATATOFILE_H
#include "Model.h"
using namespace Model;
static const char* recordfile = "PlayersRecord.ini";
static const char* replayfile = "HistoryGame.ini";
bool is_file_exist(const char*);
// record
void createRecordFile();
void writePlayerInFile(Player player);
void showAllRecordInFile();
bool checkPlayerName(string name);
void searchPlayerByName(string name);
void findPlayerSameRank(string name, int win, int lose);
void eraseOldResult(string name);
void updateCurrentResult(Player& player);
// replay
void createReplayFile();
bool checkGameId(char id);
void saveReplayInFile(Game* game);
void showAllReplayGameInFile();
list<Move> getReplayMoveById(char id);
string getReplayPlayerById(char id, int user);
#endif // SAVEDATATOFILE_H
