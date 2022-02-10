#pragma once
#include "scoreboard.hpp"
class user { //유저 클래스 최상위 부모 클래스
protected:
	int userId;
	char * userName;
public:
	user(int,const char *);
	int getuserId();
	char * getuserName();
	virtual void test() {}
	bool operator== (user& user2) {
		if(user2.getuserId() == this->userId) return true;
		return false;
	}
};

class lobbyuser : public user { //로비에 속해있는 유저 표현
private:
	bool isReady; // 레디 여부
public:
	lobbyuser(int id ,const char* name) :user(id,name) { //가장 기본적인 생성자
		isReady = false;
	}
	lobbyuser(int id ,const char* name, int isReady) :user(id,name),isReady(isReady) {} //준비 여부를 받는 생성자
	lobbyuser(user *);
	//<getter>
	bool getUserReady() { return isReady;}
	//</getter>
	//<setter>
	void switchUserReady() {isReady = !isReady;}
	//</setter>
};

class gameuser : public user { //게임에 속해있는 유저 표현
private:
	scoreboard table; // 점수판 저장
public:
	//<constructor>
	gameuser(int id,const char* name) : user(id,name) {}
	gameuser(lobbyuser *);
	gameuser(user *);
	//</constructor>
	scoreboard& getScoreBoard() {return table;} // 점수판을 가져온다.
};