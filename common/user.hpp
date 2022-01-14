#pragma once
class user {
protected:
	int userId;
	char * userName;
public:
	user(int,const char *);
	int getuserId();
	char * getuserName();
};

class lobbyuser : public user {
protected:
	bool isReady;
public:
	lobbyuser(int id ,const char* name) :user(id,name) {
		isReady = false;
	}
	lobbyuser(int id ,const char* name, int isReady) :user(id,name),isReady(isReady) {}
	bool getUserReady() { return isReady;}
	void switchUserReady() {isReady = !isReady;}
};