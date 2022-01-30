#pragma once
#include <list>
#include "user.hpp"
#include <string>
#include <list>
#include "dice_game.hpp"
class room {
protected:
	int level;
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
	int getlevel() {return level;}
	std::list<user *>& getUserList() { return userList; }
	std::list<std::string>& getChatList() {return chatList;}
};

class gameroom : public room {
private:
	dice_game data;
	int order;
protected:
public:
	gameroom(int ID , char *name, int MaxPeople): room(ID, name, MaxPeople), order(0) {}
	gameroom(room *);
	dice_game& getdata() {return data;}
};