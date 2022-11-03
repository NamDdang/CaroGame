#include "../../Header Files/Controller/MySQLConnect.h"
#include <iomanip>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>
void MySQLConnect::getConnection()
{
	try
	{
		driver = get_driver_instance();
		con = driver->connect(server, username, password);
	}
	catch (sql::SQLException e)
	{
		cout << "Could not connect to server. Error message: " << e.what() << endl;
		system("pause");
		exit(1);
	}
	//please create database "caro_game" ahead of time
	con->setSchema(schema);
}
void MySQLConnect::insertUser(User user)
{
	string sqlString = "Insert into `user`(`username`, `password`, `win`, `lose`, `draw`, `online`) values(?, ?, ?, ?, ?, ?)";
	try {
		PreparedStatement* preparedStmt = con->prepareStatement(sqlString);
		preparedStmt->setString(1, user.GetUserName());
		preparedStmt->setString(2, user.GetPassWord());
		preparedStmt->setInt(3, user.GetWin());
		preparedStmt->setInt(4, user.GetLose());
		preparedStmt->setInt(5, user.GetDraw());
		preparedStmt->setBoolean(6, user.isOnline());
		preparedStmt->executeUpdate();
		cout << "Successful!" << endl;
		delete preparedStmt;
		system("pause");
	}
	catch (SQLException& ex) {
		cout << "Insert user failure!" << endl;
		cout << "# ERR: " << ex.what();
		cout << " (MySQL error code: " << ex.getErrorCode();
		cout << ", SQLState: " << ex.getSQLState() << " )" << endl;
		system("pause");
	}
}
void MySQLConnect::insertMatch(Match match)
{
	string sqlString = "Insert into `match`(`player1`, `player2`, `playerwin`) values(?, ?, ?)";
	try {
		PreparedStatement* preparedStmt = con->prepareStatement(sqlString);
		preparedStmt->setString(1, match.GetPlayer1());
		preparedStmt->setString(2, match.GetPlayer2());
		preparedStmt->setString(3, match.GetPlayerWin());
		preparedStmt->executeUpdate();
		delete preparedStmt;
	}
	catch (SQLException& ex) {
		cout << "Insert match failure!" << endl;
		cout << "# ERR: " << ex.what();
		cout << " (MySQL error code: " << ex.getErrorCode();
		cout << ", SQLState: " << ex.getSQLState() << " )" << endl;
		system("pause");
	}
}
void MySQLConnect::updateUser(User user)
{
	string sqlString = "Update `user` set `username` = ?, `password` = ?, `win` = ?, `lose` = ?, `draw` = ?, `online` = ? where `id` = ?";
	try {
		PreparedStatement* preparedStmt = con->prepareStatement(sqlString);
		preparedStmt->setString(1, user.GetUserName());
		preparedStmt->setString(2, user.GetPassWord());
		preparedStmt->setInt(3, user.GetWin());
		preparedStmt->setInt(4, user.GetLose());
		preparedStmt->setInt(5, user.GetDraw());
		preparedStmt->setInt(6, user.isOnline());
		preparedStmt->setInt(7, user.GetId());
		preparedStmt->executeUpdate();
		delete preparedStmt;
	}
	catch (SQLException& ex) {
		cout << "Update user failure!" << endl;
		cout << "# ERR: " << ex.what();
		cout << " (MySQL error code: " << ex.getErrorCode();
		cout << ", SQLState: " << ex.getSQLState() << " )" << endl;
		system("pause");
	}
}
void MySQLConnect::updateMatch(Match match)
{
	string sqlString = "Update `match` set `player1` = ?, `player2` = ?, `playerwin` = ? where `matchId` = ?";
	try {
		PreparedStatement* preparedStmt = con->prepareStatement(sqlString);
		preparedStmt->setString(1, match.GetPlayer1());
		preparedStmt->setString(2, match.GetPlayer2());
		preparedStmt->setString(3, match.GetPlayerWin());
		preparedStmt->setInt(4, match.GetMatchId());
		preparedStmt->executeUpdate();
		delete preparedStmt;
	}
	catch (SQLException& ex) {
		cout << "Update match failure!" << endl;
		cout << "# ERR: " << ex.what();
		cout << " (MySQL error code: " << ex.getErrorCode();
		cout << ", SQLState: " << ex.getSQLState() << " )" << endl;
		system("pause");
	}
}
void MySQLConnect::deleteUser(User user)
{
	string sqlString = "Delete from `user` where `id` = ?";
	try {
		PreparedStatement* preparedStmt = con->prepareStatement(sqlString);
		preparedStmt->setInt(1, user.GetId());
		preparedStmt->executeUpdate();
		delete preparedStmt;
	}
	catch (SQLException& ex) {
		cout << "Delete user failure!" << endl;
		cout << "# ERR: " << ex.what();
		cout << " (MySQL error code: " << ex.getErrorCode();
		cout << ", SQLState: " << ex.getSQLState() << " )" << endl;
		system("pause");
	}
}
void MySQLConnect::deleteMatch(Match match)
{
	string sqlString = "Delete from `match` where `matchId` = ?";
	try {
		PreparedStatement* preparedStmt = con->prepareStatement(sqlString);
		preparedStmt->setInt(1, match.GetMatchId());
		preparedStmt->executeUpdate();
		delete preparedStmt;
	}
	catch (SQLException& ex) {
		cout << "Delete match failure!" << endl;
		cout << "# ERR: " << ex.what();
		cout << " (MySQL error code: " << ex.getErrorCode();
		cout << ", SQLState: " << ex.getSQLState() << " )" << endl;
		system("pause");
	}
}

list<User> MySQLConnect::findAllUser()
{
	list<User> userList;
	string sqlString = "Select * from `user`";
	try {
		Statement* stmt = con->createStatement();
		ResultSet* rs = stmt->executeQuery(sqlString);
		while (rs->next()) {
			User user = User(rs->getInt("id"), rs->getString("username"), rs->getString("password"), rs->getInt("win"),
				rs->getInt("lose"), rs->getInt("draw"), rs->getBoolean("online"));
			userList.push_back(user);
		}
		delete rs;
		delete stmt;
	}
	catch (SQLException& ex) {
		cout << "# ERR: " << ex.what();
		cout << " (MySQL error code: " << ex.getErrorCode();
		cout << ", SQLState: " << ex.getSQLState() << " )" << endl;
		system("pause");
	}
	return userList;
}
list<Match> MySQLConnect::findAllMatch()
{
	list<Match> matchList;
	string sqlString = "Select * from `match`";
	try {
		Statement* stmt = con->createStatement();
		ResultSet* rs = stmt->executeQuery(sqlString);
		while (rs->next()) {
			Match match = Match(rs->getInt("matchId"), rs->getString("player1"), rs->getString("player2"), rs->getString("playerwin"));
			matchList.push_back(match);
		}
		delete rs;
		delete stmt;
	}
	catch (SQLException& ex) {
		cout << "# ERR: " << ex.what();
		cout << " (MySQL error code: " << ex.getErrorCode();
		cout << ", SQLState: " << ex.getSQLState() << " )" << endl;
		system("pause");
	}
	return matchList;
}
User MySQLConnect::findUserByUserName(string username)
{
	User user;
	string sqlString = "Select * from `user` where `username` = '" + username + "'";
	try {
		Statement* stmt = con->createStatement();
		ResultSet* rs = stmt->executeQuery(sqlString);
		while (rs->next()) {
			user = User(rs->getInt("id"), rs->getString("username"), rs->getString("password"), rs->getInt("win"),
				rs->getInt("lose"), rs->getInt("draw"), rs->getBoolean("online"));
		}
		delete rs;
		delete stmt;
	}
	catch (SQLException& ex) {
		cout << "# ERR: " << ex.what();
		cout << " (MySQL error code: " << ex.getErrorCode();
		cout << ", SQLState: " << ex.getSQLState() << " )" << endl;
		system("pause");
	}
	return user;
}
void MySQLConnect::getUserInfoByUserName(string username)
{
	string sqlString = "select * from `user` where `username` = '" + username + "'";
	try {
		Statement* stmt = con->createStatement();
		ResultSet* rs = stmt->executeQuery(sqlString);
		while (rs->next()) {
			cout << "User name: " << rs->getString("username") << endl;
			cout << "Number of Wins: " << rs->getInt("win") << endl;
			cout << "Number of Losses: " << rs->getInt("lose") << endl;
			cout << "Number of Draws: " << rs->getInt("draw") << endl;
		}
		delete rs;
		delete stmt;
	}
	catch (SQLException ex) {
		cout << "# ERR: " << ex.what();
		cout << " (MySQL error code: " << ex.getErrorCode();
		cout << ", SQLState: " << ex.getSQLState() << " )" << endl;
		system("pause");
	}
}
void MySQLConnect::findMatchByUserName(string username)
{
	string sqlString = "select * from `match` where `player1` = '" + username + "'" + " or `player2` = '" + username + "'";
	try {
		Statement* stmt = con->createStatement();
		ResultSet* rs = stmt->executeQuery(sqlString);
		int order = 1;
		cout << setw(16) << "Player 1" << setw(12) << "Player 2" << setw(12) << "Winner" << endl;
		while (rs->next()) {
			cout << setw(4) << order;
			cout << setw(12) << rs->getString("player1");
			cout << setw(12) << rs->getString("player2");
			cout << setw(12) << rs->getString("playerwin") << endl;
			order++;
		}
		delete rs;
		delete stmt;
	}
	catch (SQLException ex) {
		cout << "# ERR: " << ex.what();
		cout << " (MySQL error code: " << ex.getErrorCode();
		cout << ", SQLState: " << ex.getSQLState() << " )" << endl;
		system("pause");
	}
}

User MySQLConnect::findUserByUserNameAndPassWord(string username, string password)
{
	User user;
	try {
		Statement* stmt = con->createStatement();
		string sqlString = "select * from `user` where `username` = '" + username + "'and `password` ='" + password + "'";
		ResultSet* rs = stmt->executeQuery(sqlString);
		if (rs->next()) {
			user = User(rs->getInt("id"), rs->getString("username"), rs->getString("password"), rs->getInt("win"),
				rs->getInt("lose"), rs->getInt("draw"), rs->getBoolean("online"));
		}
		else {
			cout << "Wrong username or password." << endl;
			system("pause");
		}
		delete rs;
		delete stmt;
	}
	catch (SQLException ex) {
		cout << "# ERR: " << ex.what();
		cout << " (MySQL error code: " << ex.getErrorCode();
		cout << ", SQLState: " << ex.getSQLState() << " )" << endl;
		system("pause");
	}
	return user;
}