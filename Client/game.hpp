#pragma once

#include <list>
#include "network.hpp"
#include <vector>
#include <string>
#include "../common/user.hpp"
class game {
private :
	void graphic();
	std::u16string chat_str;
	std::list<user *> userList;
	std::list<std::string> chatList;
public :
	void parseString(const char * buffer);
	void start(network * net);
	void set_chatString(int x);
	const std::u16string& get_chatString() {return chat_str;}
};