#pragma once
#include <vector>
#include <string>
#include "dice_game.hpp"
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
	std::vector<int> display(dice_game);
	std::string tostring(); 

};