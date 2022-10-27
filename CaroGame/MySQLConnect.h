#ifndef MYSQLCONNECT_H
#define MYSQLCONNECT_H
#include <stdlib.h>
#include <iostream>

#include "mysql_connection.h"
#include "Model.h"
using namespace Model;
using namespace std;
using namespace sql;

class MySQLConnect {
private:
	const string server = "tcp://127.0.0.1:3306";
	const string username = "root";
	const string password = "0123456789";
	const string schema = "caro_game";
	sql::Driver* driver;
	sql::Connection* con;

public:
	~MySQLConnect() {
		delete con;
	}
	void getConnection();
	void insertUser(User);
	void insertMatch(Match);
	void updateUser(User);
	void updateMatch(Match);
	void deleteUser(User);
	void deleteMatch(Match);
	list<User> findAllUser();
	list<Match> findAllMatch();
	User findUserByUserName(string);
	void getUserInfoByUserName(string);
	void findMatchByUserName(string);
	void findMatchByID(int);
	User findUserByUserNameAndPassWord(string, string);
};
#endif // MYSQLCONNECT_H
