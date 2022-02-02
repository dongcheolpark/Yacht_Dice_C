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
	order = 0;
	for(auto item : _room->getUserList()) {
		this->userList.push_back(new gameuser(item));
	}
	this->chatList = _room->getChatList();
}

gameuser * gameroom::get_orderUser() {
	auto res = userList.begin();
	for(int i = 0;i<order;i++,res++);
	return dynamic_cast<gameuser*>(*res); 
}

user * room::getUser(int id) {
	for(auto item : userList) {
		if(item->getuserId() == id) return item;
	}
	return NULL;
}

bool gameroom::is_orderUser(int id) {
	return (getUser(id) == get_orderUser());
}

void gameroom::change_order() {
	int size = userList.size()-1;
	if(order == size){
		order = 0;
		change_turn();
	}
	else order++;
}

void gameroom::change_turn() {
	turn++;
}