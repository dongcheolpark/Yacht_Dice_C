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
	std::list<user *> userList;
	std::list<std::string> chatList;
public: 
	send_struct * parseString(const char *);
	send_struct * processing(int index);
	void remove_user(int id);
	std::list<user *>& getUserList() { return userList; }
	std::list<std::string>& getChatList() {return chatList;}
};