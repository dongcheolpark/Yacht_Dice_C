#include "gtest/gtest.h"
#include "../Server/game_server.hpp"

void enterRoom(game_server& testserver) { //3명 동시접속 MOCK
	testserver.parseString("0 0 0 test1");
	testserver.parseString("0 0 1 test2");
	testserver.parseString("0 0 2 test3");//3명 서버 접속

	testserver.parseString("3 0 4 hello 3");//방 생성

	testserver.parseString("3 1 0 0");
	testserver.parseString("3 1 0 1");
	testserver.parseString("3 1 0 2");//3명 방 접속
}

TEST(gameServerTest,parseStringTest1) { // 방 만들기
	game_server testserver;
	testserver.parseString("0 0 4 hello"); //id 접속
	auto a = testserver.parseString("3 0 4 hello 3"); //방정보 생성
	auto res = std::string("0 0 0 hello 3"); //방정보 리턴
	EXPECT_EQ(*(a->str),res);
}

TEST(gameServerTest,parseStringTest2) { // 방접속
	game_server testserver;
	testserver.parseString("0 0 4 hello");
	testserver.parseString("3 0 4 hello 3");
	auto a = testserver.parseString("3 1 0 4");
	auto res = std::string("0 0 0 hello 3");
	EXPECT_EQ(*(a->str),res);
}

TEST(gameServerTest,parseStringTest3) { // 방접속하고 채팅
	game_server testserver;
	enterRoom(testserver);
	testserver.parseString("1 1 0 0 testchat");
	auto a = testserver.parseString("1 0 0");
	auto res = std::string("1 1 1 test1 testchat ");
	EXPECT_EQ(*(a->str),res);
}

TEST(gameServerTest,ParseSTringTest4) { // 턴 넘기기
	game_server testserver;
	enterRoom(testserver);
	testserver.parseString("3 2 0 0");
	testserver.parseString("3 2 0 1");
	testserver.parseString("3 2 0 2");//레디

	auto a = testserver.parseString("4 4 0");
	auto res = std::string("2 5 ");
	EXPECT_EQ(*(a->str),res);
	a = testserver.parseString("4 4 0");
	res = std::string("2 5 ");
	EXPECT_EQ(*(a->str),res);
}