#pragma once
#include "../common/Room.hpp"
#include "../common/user.hpp"
#include <string>
#include <vector>
#include <list>

class game_server {
private:
	std::list<room *> roomList;
	std::list<user *> userList;
public: 
	void parseString(char *);
	void remove_user(int id);
};