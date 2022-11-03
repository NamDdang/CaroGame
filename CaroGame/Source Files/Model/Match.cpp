#include "../../Header Files/Model/Match.h"

Match::Match()
{

}
Match::Match(int matchId, string player1, string player2, string playerwin)
{
	this->matchId = matchId;
	this->player1 = player1;
	this->player2 = player2;
	this->playerwin = playerwin;
}
int Match::GetMatchId()
{
	return matchId;
}
void Match::SetMatchId(int matchId)
{
	this->matchId = matchId;
}
string Match::GetPlayer1()
{
	return player1;
}
void Match::SetPlayer1(string player1)
{
	this->player1 = player1;
}
string Match::GetPlayer2()
{
	return player2;
}
void Match::SetPlayer2(string player2)
{
	this->player2 = player2;
}
string Match::GetPlayerWin()
{
	return playerwin;
}
void Match::SetPlayerWin(string playerwin)
{
	this->playerwin = playerwin;
}
