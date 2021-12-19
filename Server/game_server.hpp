#pragma once
#include "../common/Room.hpp"
#include "../common/user.hpp"
#include "send_struct.hpp"
#include <string>
#include <vector>
#include <list>

class game_server {
private:
	std::list<room *> roomList;
	std::list<user *> userList;
public: 
	send_struct * parseString(char *);
	void remove_user(int id);
};