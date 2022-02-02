#pragma once
#include <vector>
#include <string>
#include "dice_game.hpp"
#include "function.hpp"

class scoreboard {
protected:
	std::vector<int> up; // 위쪽 데이터
	bool bonus; // 보너스 처리
	std::vector<int> down; // 아래쪽 데이터
	int score; // 점수 총합
	void setscore();
	std::vector<int> calculate(dice_game); // 다이스 값을 바탕으로 데이터 처리
public:
	scoreboard(); //기본적인 생성자
	//<setter>
	void setUp(int,int);
	void setDown(int,int);
	void setBonus();
	//</setter>
	//<getter>
	int getUp(int);
	int getDown(int);
	int getBonus();
	int getscore();
	//</getter>
	std::vector<int> display(dice_game); //화면에 띄워질 때 어떤 값을 보여줄지를 처리해줌
	std::string tostring(); //서버로 데이터를 보내기 용이하도록 string으로 데이터를 바꿔줌
};