#pragma once
class user {
private:
	int userId;
	char * userName;
	bool isReady = false;
public:
	user(int,const char *,int);
	int getuserId();
	char * getuserName();
	bool getUserReady() { return isReady;}
	void switchUserReady() {isReady = !isReady;}
};