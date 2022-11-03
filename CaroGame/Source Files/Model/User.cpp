#include "../../Header Files/Model/User.h"

User::User()
{
	online = false;
}
User::User(int id, string username, string password, int win, int lose, int draw, bool online)
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
