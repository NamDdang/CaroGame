#include "Model.h"

using namespace Model;
// Point
Point::Point() { x = y = check = 0; }

Point::Point(int pX, int pY)
{
	x = pX; y = pY;
	check = 0;
}

int Point::getX() { return x; }

int Point::getY() { return y; }

int Point::getCheck() { return check; }

void Point::setX(int pX) { x = pX; }

void Point::setY(int pY) { y = pY; }

bool Point::setCheck(int pCheck)
{

	if (pCheck == 0 || pCheck == VX || pCheck == VO)
	{
		check = pCheck;
		return true;
	}
	return false;
}
// Board
int Board::getSize() { return size; }

int Board::getXAt(int i, int j) { return pArr[i][j].getX(); }

int Board::getYAt(int i, int j) { return pArr[i][j].getY(); }

Board::Board()
{
	size = 0;
	pArr = NULL;
}

Board::Board(int pSize)
{
	if (pSize > 10)
	{
		size = 10;
	}
	else if (pSize < 4)
	{
		size = 4;
	}
	else
	{
		size = pSize;
	}
	pArr = new Point * [size];
	for (int i = 0; i <= size; i++) pArr[i] = new Point[size];
}

Board::Board(const Board& board)
{
	size = board.size;
	pArr = new Point * [size];
	for (int i = 0; i <= size; i++) pArr[i] = new Point[size];
	for (int i = 0; i <= size; i++)
		for (int j = 0; j <= size; j++)
			pArr[i][j] = board.pArr[i][j];
}

Board::~Board()
{

	for (int i = 0; i <= size; i++) delete[] pArr[i];
	delete[] pArr;
}

void Board::SetXO(int i, int j, int value)
{
	if (size == 0) return; // Phai goi constructor truoc khi reset data
	pArr[i][j].setCheck(value);
}
int Board::GetXO(int x, int y)
{
	return pArr[x][y].getCheck();
}
// Player
string Player::GetName() { return name; }
void Player::SetName(string value) { name = value; }
void Player::Input()
{
	name = InputStringName(8);

	// nhap mot ten moi thi dat so tran thang, thua, hoa ve bang 0
	win = 0;
	lose = 0;
	draw = 0;
}

void Player::SetWin(int value) { win = value; }
void Player::SetLose(int value) { lose = value; }
void Player::SetDraw(int value) { draw = value; }
int Player::GetWin() { return win; }
int Player::GetLose() { return lose; }
int Player::GetDraw() { return draw; }
void Player::IncreWin() { win++; }
void Player::IncreLose() { lose++; }
void Player::IncreDraw() { draw++; }

// Game
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
User& Game::GetUser() { return user;}
void Game::SetUser(User value)
{
	user = value;
}
// User
User::User()
{
	online = false;
}
User::User(int id, string username, string password, int win, int lose , int draw, bool online)
{
	this->id = id;
	this->username = username;
	this->password = password;
	this->win = win;
	this->lose = lose;
	this->draw = draw;
	this->online = online;
}
int User::GetId()
{
	return id;
}
void User::SetId(int id)
{
	this->id = id;
}
string User::GetUserName()
{
	return username;
}
void User::SetUserName(string username)
{
	this->username = username;
}
string User::GetPassWord()
{
	return password;
}
void User::SetPassWord(string password)
{
	this->password = password;
}
int User::GetWin()
{
	return win;
}
void User::SetWin(int win)
{
	this->win = win;
}
int User::GetLose()
{
	return lose;
}
void User::SetLose(int lose)
{
	this->lose = lose;
}
int User::GetDraw()
{
	return draw;
}
void User::SetDraw(int draw)
{
	this->draw = draw;
}
bool User::isOnline() { return online; }
void User::SetStatusOnline(bool value)
{
	online = value;
}

// Match
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
