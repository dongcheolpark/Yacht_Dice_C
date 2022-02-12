#pragma once

#ifdef _WIN32
#include <conio.h>
#endif // _Win32


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
	networkinterface * net;
	graphic * _graphic;
	int dice_cursor;
	int score_cursor;
public :
	std::list<room*> roomList;
	game(int id,networkinterface * net); 
	void parseString(std::string buffer);
	void start();
	void set_chatString(int x);
	void sendChatString();
	void set_roomId(room * _room) {this->_room = _room;}
	void setDiceCursor(int a) {
		if(a < 0 && dice_cursor == 0) return; 
		if(a > 0 && dice_cursor == 4) return;
		dice_cursor += a;
	}
	void setScoreCursor(int a); 
	void setScoreCursor(); 
	void graphics();
	void chatStatusSwitch() { chatStatus = !chatStatus; graphics();}
	int get_roomId() {return _room->getRoomId();}
	int get_userId() {return id;}
	room* getRoom() {return _room;}
	bool getChatStatus() {return chatStatus;}
	int getDiceCursor() {return dice_cursor;}
	int getScoreCursor() {return score_cursor;}
	void change_room(int);
	void clearChatString() { chat_str.clear();}
	const std::u16string& get_chatString() {return chat_str;}
};