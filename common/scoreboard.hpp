#pragma once
#include <vector>
#include <string>
#include "function.hpp"

class scoreboard {
private:
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
	std::string tostring(); 
};