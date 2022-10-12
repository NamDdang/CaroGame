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
	/*getline(cin, name);
	fflush(stdin);*/
	cin >> name;
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
    user1.SetLose(0);
    user1.SetWin(0);
    user1.SetDraw(0);
    user2.SetLose(0);
    user2.SetWin(0);
    user2.SetDraw(0);
}

Game::~Game() { delete board; }

void Game::Init(int pSize)
{
	board = new Board(pSize);
	exit = false;
	turn = true;
	wongame = false;
	playerwon = 0;
	user1.SetLose(0);
	user1.SetWin(0);
	user1.SetDraw(0);
	user2.SetLose(0);
	user2.SetWin(0);
	user2.SetDraw(0);
}

Player& Game::GetUser1() { return user1; }
Player& Game::GetUser2() { return user2; }
void Game::SetUser1(Player value)
{
	user1 = value;
}
void Game::SetUser2(Player value)
{
	user2 = value;
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
