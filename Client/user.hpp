#pragma once
class user {
private:
	int userId;
	char * userName;
public:
	user(int,const char *);
	int getuserId();
	char * getuserName();
};