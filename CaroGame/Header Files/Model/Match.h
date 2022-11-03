#ifndef MATCH_H
#define MATCH_H
#include <string>
using namespace std;
class Match
{
private:
	int matchId;
	string player1;
	string player2;
	string playerwin;
public:
	Match();
	Match(int, string, string, string);
	int GetMatchId();
	void SetMatchId(int);
	string GetPlayer1();
	void SetPlayer1(string);
	string GetPlayer2();
	void SetPlayer2(string);
	string GetPlayerWin();
	void SetPlayerWin(string);
};
#endif // MATCH_H
