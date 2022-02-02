#pragma once
#include "user.hpp"
#include <string>
#include <list>
#include "dice_game.hpp"

class room { //방 클래스의 최상위 부모, 로비룸으로도 쓰인다.
protected:
	int level; // 자식 클래스인지 부모 클래스인지 여부 체크
	int roomId; // 방 id
	char * roomName; //방 이름
	int roomMaxPeople; // 방의 최대 인원
	std::list<user *> userList; // 방 유저 리스트
	std::list<std::string> chatList; // 방 채팅 리스트
	virtual void test() {};
public:	
	room(int,const char *,int); //방 id, 이름, 최대 인원을 받는 생성자
	//<getter>
	int getRoomId(){return roomId;}
	char * getRoomName() {return roomName;}
	int getRoomMaxPeople() {return roomMaxPeople;}
	int getlevel() {return level;}
	user * getUser(int);
	std::list<user *>& getUserList() {return userList;}
	std::list<std::string>& getChatList() {return chatList;}
	//</getter>
};

class gameroom : public room {
private:
	dice_game data; // 주사위 정보
	int order; // 어떤 유저가 순서인지 알려준다.
	int turn; // 몇번의 사이클이 돌았는지 알려준다.
	void change_turn();
public:
	gameroom(int ID , char *name, int MaxPeople): room(ID, name, MaxPeople), order(0) {}// 기본적인 생성자
	gameroom(room *); // 기본적인 생성자

	//<getter>
	dice_game& getdata() {return data;}
	int get_order() {return order;}
	int getTurn() {return turn;}
	bool is_orderUser(int id);
	gameuser * get_orderUser();
	//</getter>
	void change_order();
};