#pragma once

#include <list>
#include "network.hpp"
#include "../common/function.hpp"
#include <vector>
#include <string>
#include "../common/user.hpp"
#include "../common/Room.hpp"
#include "graphic.hpp"
class graphic;

class game {
private :
	std::u16string chat_str;
	int id = 0;
	room * _room = NULL;
	bool chatStatus = false;
	void graphics();
	graphic * _graphic;
public :
	std::list<room*> roomList;
	game(int id); 
	void parseString(std::string buffer);
	void start(network * net);
	void set_chatString(int x);
	void set_roomId(room * _room) {this->_room = _room;}
	void chatStatusSwitch() { chatStatus = !chatStatus;}
	int get_roomId() {return _room->getRoomId();}
	int get_userId() {return id;}
	room* getRoom() {return _room;}
	bool getChatStatus() {return chatStatus; }
	const std::u16string& get_chatString() {return chat_str;}
};