#ifndef FILE_MANIPULATE_H
#define FILE_MANIPULATE_H
#include "../Model/Player.h"
#include "../Model/Game.h"
static const char* recordfile = "PlayersRecord.ini";
static const char* replayfile = "HistoryGame.ini";
class FileManipulate
{
public:
	static bool is_file_exist(const char*);
	// record
	static void createRecordFile();
	static void writePlayerInFile(Player player);
	static void showAllRecordInFile();
	static bool checkPlayerName(string name);
	static void searchPlayerByName(string name);
	static void findPlayerSameRank(string name, int win, int lose);
	static void eraseOldResult(string name);
	static void updateCurrentResult(Player& player);
	// replay
	static void createReplayFile();
	static bool checkGameId(char id);
	static void saveReplayInFile(Game* game);
	static void showAllReplayGameInFile();
	static list<Move> getReplayMoveById(char id);
	static string getReplayPlayerById(char id, int user);
};
#endif // FILE_MANIPULATE_H
