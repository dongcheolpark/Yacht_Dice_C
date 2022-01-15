#pragma once
#include <list>
#include "user.hpp"
#include <string>
#include <list>
#include "dice_game.hpp"
class room {
protected:
	int roomId;
	char * roomName;
	int roomMaxPeople;
	std::list<user *> userList;
	std::list<std::string> chatList;
	virtual void test() {};
public:	
	room(int,const char *,int); 
	int getRoomId(){return roomId;}
	char * getRoomName() {return roomName;}
	int getRoomMaxPeople() {return roomMaxPeople;}
	std::list<user *>& getUserList() { return userList; }
	std::list<std::string>& getChatList() {return chatList;}
};

class gameroom : public room {
private:
	dice_game data;
protected:
public:
	gameroom(int ID , char *name, int MaxPeople): room(ID, name, MaxPeople) {}
	gameroom(room *);
};