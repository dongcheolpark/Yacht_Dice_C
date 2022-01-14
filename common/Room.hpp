#pragma once
#include <list>
#include "user.hpp"
#include <string>
#include <list>
class room {
private:
	int roomId;
	char * roomName;
	int roomMaxPeople;
	std::list<user *> userList;
	std::list<std::string> chatList;
public:	
	room(int,const char *,int); 
	int getRoomId(){return roomId;}
	char * getRoomName() {return roomName;}
	int getRoomMaxPeople() {return roomMaxPeople;}
	std::list<user *>& getUserList() { return userList; }
	std::list<std::string>& getChatList() {return chatList;}
};
