#pragma once

#include <list>
#include "network.hpp"
#include "../common/strparse.hpp"
#include <vector>
#include <string>
#include "../common/user.hpp"
#include "../common/Room.hpp"
class game {
private :
	void graphic();
	std::u16string chat_str;
	int id = 0;
	room * _room = NULL;
public :
	std::list<room*> roomList;
	game(int id) : id(id) {}
	void parseString(std::string buffer);
	void start(network * net);
	void set_chatString(int x);
	void set_roomId(room * _room) {this->_room = _room;}
	int get_roomId() {return _room->getRoomId();}
	int get_userId() {return id;}
	const std::u16string& get_chatString() {return chat_str;}
};