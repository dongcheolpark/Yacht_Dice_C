#pragma once

#include "../common/user.hpp"
#include "game_server.hpp"
#include "send_struct.hpp"
#include <list>

class game_server_parse { 
protected:
	send_struct * data;
	game_server * server;
	std::list<user *> & userList;
	void set_network_code(int first,int second); 
public :
	game_server_parse(game_server * server,int first,int second) : userList(server->getUserList()) {
		data = new send_struct();
		this->server = server;
		set_network_code(first,second);
	}	
	~game_server_parse() {
	}
	virtual send_struct * doParse() {
		return data;
	}
};

class game_server_send_userList : public game_server_parse {
public : 
	game_server_send_userList(game_server * server) : game_server_parse(server,0,0) {}
	send_struct * doParse();
};

class game_server_send_chatList : public game_server_parse {
public:
	game_server_send_chatList(game_server * server) : game_server_parse(server,1,0) {}
	send_struct * doParse();
};
