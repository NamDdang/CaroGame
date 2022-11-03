#ifndef USER_H
#define USER_H
#include <string>
using namespace std;
class User
{
private:
	int id;
	string username;
	string password;
	int win;
	int lose;
	int draw;
	bool online;
public:
	User();
	User(int, string, string, int, int, int, bool);
	int GetId();
	void SetId(int);
	string GetUserName();
	void SetUserName(string);
	string GetPassWord();
	void SetPassWord(string);
	int GetWin();
	void SetWin(int);
	int GetLose();
	void SetLose(int);
	int GetDraw();
	void SetDraw(int);
	bool isOnline();
	void SetStatusOnline(bool);
};
#endif // USER_H
