#pragma once
#include <vector>
#include <string>
#include "dice_game.hpp"
#include "function.hpp"

class scoreboard {
protected:
	std::vector<int> up;
	//up
	bool bonus;
	//bonus
	std::vector<int> down;
	int score;
	void setscore();
	//down
public:
	scoreboard();
	void setUp(int,int);
	void setDown(int,int);
	void setBonus();
	int getUp(int);
	int getDown(int);
	int getBonus();
	int getscore();
	std::vector<int> display(dice_game);
	std::string tostring();
};