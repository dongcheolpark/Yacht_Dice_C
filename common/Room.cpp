#include "Room.hpp"
#include <string.h>

room::room(int id, const char * name,int maxpeople) {
	level = 0;
	this->roomId = id;
	this->roomName = new char[strlen(name)];
	strcpy(this->roomName,name);
	this->roomMaxPeople = maxpeople;
}
gameroom::gameroom(room * _room) : room(_room->getRoomId(),_room->getRoomName(),_room->getRoomMaxPeople()) {
	level = 1;
	for(auto item : _room->getUserList()) {
		this->userList.push_back(new gameuser(item));
	}
	this->chatList = _room->getChatList();
}