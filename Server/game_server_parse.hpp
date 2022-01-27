#pragma once

#include "../common/user.hpp"
#include "../common/Room.hpp"
#include "../common/function.hpp"
#include "game_server.hpp"
#include "send_struct.hpp"
#include <list>

class game_server_parse { 
protected:
	int roomId = 0;
	send_struct * data;
	game_server * server;
	void set_network_code(int first,int second); 
public :
	game_server_parse(game_server * server,int first,int second,int roomId) {
		this->roomId = roomId;
		data = new send_struct();
		this->server = server;
		set_network_code(first,second);
	}	
	game_server_parse(game_server * server,int first,int second) {
		data = new send_struct();
		this->server = server;
		set_network_code(first,second);
	}	
	game_server_parse(int first,int second) {
		data = new send_struct();
		set_network_code(first,second);
	}	
	~game_server_parse() {
	}
	virtual send_struct * doParse() {
		return NULL;
	}
};
class game_server_send_userList : public game_server_parse {
public : 
	game_server_send_userList(game_server * server,int roomId) : game_server_parse(server,1,0,roomId) {}
	send_struct * doParse();
};

class game_server_send_chatList : public game_server_parse {
public:
	game_server_send_chatList(game_server * server,int roomId) : game_server_parse(server,1,1,roomId) {}
	send_struct * doParse();
};

class game_server_send_roomList : public game_server_parse {
private:
	user * _user;
public:
	game_server_send_roomList(game_server * server,user *_user) : game_server_parse(server,0,1) , _user(_user) {}
	send_struct * doParse();
};

class game_server_send_roomInfo : public game_server_parse {
private : 
	user * _user;
public:
	game_server_send_roomInfo(game_server * server,int roomId,user * _user) : game_server_parse(server,0,0,roomId), _user(_user) {}
	send_struct * doParse();
};

class game_server_change_gameroom : public game_server_parse {
private : 
public:
	game_server_change_gameroom(game_server * server,int roomId) : game_server_parse(server,0,2,roomId) {}
	send_struct * doParse();
};

class game_server_send_dices : public game_server_parse {
private : 
public:
	game_server_send_dices(game_server * server,int roomId) : game_server_parse(server,2,1,roomId) {}
	send_struct * doParse();
};
