#include "user.hpp"
#include "string.h"

user::user(int id,const char * name) {
	this->userId = id;
	this->userName = new char[strlen(name)];
	strcpy(this->userName,name);
}

lobbyuser::lobbyuser(user * _user) : user(_user->getuserId(),_user->getuserName())  {
	isReady = false;
}

int user::getuserId() {
	return this->userId;
}
char * user::getuserName() {
	return this->userName;
}

gameuser::gameuser(lobbyuser * _lobbyuser) : user(_lobbyuser->getuserId(),_lobbyuser->getuserName()) {
}
gameuser::gameuser(user * _user) : user(_user->getuserId(),_user->getuserName()) {
}