#pragma once
#include "scoreboard.hpp"
class user {
protected:
	int userId;
	char * userName;
public:
	user(int,const char *);
	int getuserId();
	char * getuserName();
	virtual void test() {}
};

class lobbyuser : public user {
private:
	bool isReady;
public:
	lobbyuser(int id ,const char* name) :user(id,name) {
		isReady = false;
	}
	lobbyuser(int id ,const char* name, int isReady) :user(id,name),isReady(isReady) {}
	bool getUserReady() { return isReady;}
	void switchUserReady() {isReady = !isReady;}
};

class gameuser : public user {
private:
	scoreboard table;
public:
	gameuser(int id,const char* name) : user(id,name) {}
	gameuser(lobbyuser &);
};