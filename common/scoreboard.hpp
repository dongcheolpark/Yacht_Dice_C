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
	int scoreinfo;
public:
	scoreboard();
	void setUp(int,int);
	void setDown(int,int);
	void setBonus();
	int getUp(int);
	int getDown(int);
	int getBonus();
	int getscore();
	void set_scoreinfo(int);
	void get_scoreinfo(int);
	std::string tostring(); 

};