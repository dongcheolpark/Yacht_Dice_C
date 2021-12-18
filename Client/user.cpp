#include "user.hpp"
#include "string.h"

user::user(int id,char * name) {
	this->userId = id;
	this->userName = new char[strlen(name)];
	strcpy(this->userName,name);
}