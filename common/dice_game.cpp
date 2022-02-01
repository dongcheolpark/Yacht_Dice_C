#include "dice_game.hpp"

dice_game::dice_game() {
	dices.resize(5);
	for(int i = 0;i<5;i++) {
		dices[i] = 1;
	}
	lockinfo=0;
}

dice_game::dice_game(std::vector<int> v1) {
	dices.resize(5);
	try
	{
		for(int i = 0;i<5;i++) {
			dices[i] = v1[i];
		}
	}
	catch(const std::exception& e)
	{
		for(int i = 0;i<5;i++) {
			dices[i] = 1;
		}
	}
}

void dice_game::set_dice(int index,int value) {
	if( value < 1 || value > 6) return;
	this->dices[index] = value;
}

void dice_game::set_dice(std::vector<int> & val) {
	for(int i = 0;i<5;i++) {
		if(val[i] <1 || val[i] > 6) continue;
		this->dices[i] = val[i];
	}
}

std::vector<int> dice_game::get_dices() {
	return dices;
}

int dice_game::get_dices(int index) {
	return dices[index];
}

void dice_game::set_lockinfo(int index) {
	lockinfo ^= 1<<(4-index);				//비트마스킹
}

bool dice_game::get_lockinfo(int index) {	//index = 0~4
	return (lockinfo>>(4-index))%2;			//비트마스킹
}

int dice_game::get_lockinfo() {
	return lockinfo;
}