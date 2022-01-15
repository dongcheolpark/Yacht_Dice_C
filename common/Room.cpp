#include "Room.hpp"
#include <string.h>

room::room(int id, const char * name,int maxpeople) {
	this->roomId = id;
	this->roomName = new char[strlen(name)];
	strcpy(this->roomName,name);
	this->roomMaxPeople = maxpeople;
}
gameroom::gameroom(room * _room) : room(_room->getRoomId(),_room->getRoomName(),_room->getRoomMaxPeople()) {
	for(auto item : _room->getUserList()) {
		this->userList.push_back(new gameuser(item));
	}
	this->chatList = _room->getChatList();
}