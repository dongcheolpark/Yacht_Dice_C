#include "Room.hpp"
#include <string.h>

room::room(int id, const char * name,int maxpeople) {
	this->roomId = id;
	this->roomName = new char[strlen(name)];
	strcpy(this->roomName,name);
	this->roomMaxPeople = maxpeople;
}