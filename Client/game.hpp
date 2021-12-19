#pragma once

#include <list>
#include "network.hpp"
#include <vector>
#include <string>
#include "../common/user.hpp"
class game {
private :
	void graphic();
	std::list<user *> userList;
public :
	void parseString(char * buffer);
	void start(network * net);
};