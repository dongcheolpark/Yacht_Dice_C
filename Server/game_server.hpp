#pragma once
#include "../common/Room.hpp"
#include "../common/user.hpp"
#include "send_struct.hpp"
#include <cstring>
#include <string>
#include <vector>
#include <list>

class game_server {
private:
	std::list<room *> roomList;
	std::list<user *> serverUserList;
public: 
	send_struct * parseString(const char *);
	send_struct * processing(int index,int roomId);
	send_struct * remove_user(int id);
	room * getRoom(int roomId);
	std::list<room*> & getRoomList() {return roomList;}
};