#include "scoreboard.hpp"
scoreboard::scoreboard() {
	up.resize(6);
	down.resize(6);
}

void scoreboard::setscore() {
	for(auto item : up) {
		score += item;
	}
	for(auto item: down) {
		score += item;
	}
	score += 35*(int)bonus;
}

void scoreboard::setUp(int i,int val) {
	if(val > i*6 || val < 0) return;
	up[i-1] = val;
}
void scoreboard::setDown(int i,int val) {
	switch (i)
	{
	case 1:
		down[i-1] = val;
		break;
	case 2:
		down[i-1] = val;
		break;
	case 3:
		down[i-1] = val;
		break;
	case 4:
		down[i-1] = 15;
		break;
	case 5:
		down[i-1] = 30;
		break;
	case 6:
		down[i-1] = 50;
		break;
	
	default:
		break;
	}
}

std::string scoreboard::tostring()  {
	std::string res;
	for(auto item : up) {
		res.append(ydc::format_string("%d ",item));
	}
	res.append(ydc::format_string("%d ", bonus ? 0 : 35));
	for(auto item : down) {
		res.append(ydc::format_string("%d ",item));
	}
	return res;
}

int scoreboard::getUp(int n) {
	return up[n];
}

int scoreboard::getDown(int n) {
	return down[n];
}

int scoreboard::getBonus() {
	return bonus*(int)35;
}

int scoreboard::getscore() {
	setscore();
	return score;
}