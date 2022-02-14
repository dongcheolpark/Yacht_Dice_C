#include "Room.hpp"
#include <string.h>

room::room(int id, const char * name,int maxpeople) {
	level = 0;
	this->roomId = id;
	this->roomName = new char[strlen(name)];
	strcpy(this->roomName,name);
	this->roomMaxPeople = maxpeople;
}
room::room(gameroom * _room) {
	level = 0;
	this->roomId = _room->getRoomId();
	this->roomName = _room->getRoomName();
	this->roomMaxPeople = _room->getRoomMaxPeople();
	for(auto item : _room->getUserList()) {
		this->userList.push_back(new lobbyuser(item));
	}
	this->chatList = _room->getChatList();
}
gameroom::gameroom(room * _room) : room(_room->getRoomId(),_room->getRoomName(),_room->getRoomMaxPeople()), rollCount(3) {
	level = 1;
	order = 0;
	for(auto item : _room->getUserList()) {
		this->userList.push_back(new gameuser(item));
		delete item;
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
	rollCount = 3;
	if(order == size){
		order = 0;
		change_turn();
	}
	else order++;
	data.set_lockinitial(); //순서 바뀔 때, 주사위 락 초기화
}

void gameroom::change_turn() {
	turn++;
}

int gameroom::get_rollCount() {
   return rollCount;
}

void gameroom::set_rollCount() {
   if(rollCount!=0){
       rollCount--;
   }
}