#include "../../Header Files/Model/Game.h"

Game::Game(int pSize)
{
	board = new Board(pSize);
	exit = false;
	turn = true;
	wongame = false;
	playerwon = 0;
	player1.SetLose(0);
	player1.SetWin(0);
	player1.SetDraw(0);
	player2.SetLose(0);
	player2.SetWin(0);
	player2.SetDraw(0);
}

Game::~Game() { delete board; }

void Game::Init(int pSize)
{
	board = new Board(pSize);
	exit = false;
	turn = true;
	wongame = false;
	playerwon = 0;
	player1.SetLose(0);
	player1.SetWin(0);
	player1.SetDraw(0);
	player2.SetLose(0);
	player2.SetWin(0);
	player2.SetDraw(0);
}

Player& Game::GetPlayer1() { return player1; }
Player& Game::GetPlayer2() { return player2; }
void Game::SetPlayer1(Player value)
{
	player1 = value;
}
void Game::SetPlayer2(Player value)
{
	player2 = value;
}
void Game::SetTurn(bool value) { turn = value; }
bool Game::GetTurn() { return turn; }
Board* Game::GetBoard() { return board; }
void Game::SetExit(bool value) { exit = value; }
bool Game::GetExit() { return exit; }

bool Game::isWonGame()
{
	return wongame;
}
void Game::SetWonGame(bool value)
{
	wongame = value;
}
int Game::GetPlayerWon()
{
	return playerwon;
}
void Game::SetPlayerWon(int value)
{
	playerwon = value;
}
void Game::SaveMove(int col, int row, int value) {
	Move temp;
	temp.col = col;
	temp.row = row;
	temp.value = value;
	replayMoves.push_back(temp);
}
list<Move> Game::GetReplayMoves()
{
	return replayMoves;
}
void Game::ResetReplayMoves() {
	replayMoves.clear();
}
User& Game::GetUser() { return user; }
void Game::SetUser(User value)
{
	user = value;
}