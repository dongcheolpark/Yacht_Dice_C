#include "gtest/gtest.h"
#include "../Server/game_server.hpp"

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
	testserver.parseString("0 0 4 hello");
	testserver.parseString("3 0 4 hello 3");
	testserver.parseString("3 1 0 4");
	testserver.parseString("1 1 0 4 testchat");
	auto a = testserver.parseString("1 0 0");
	auto res = std::string("1 1 1 hello testchat ");
	EXPECT_EQ(*(a->str),res);
}