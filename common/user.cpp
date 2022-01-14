#include "user.hpp"
#include "string.h"

user::user(int id,const char * name) {
	this->userId = id;
	this->userName = new char[strlen(name)];
	strcpy(this->userName,name);
}

int user::getuserId() {
	return this->userId;
}
char * user::getuserName() {
	return this->userName;
}