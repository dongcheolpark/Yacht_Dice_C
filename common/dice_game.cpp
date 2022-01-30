#include "dice_game.hpp"

dice_game::dice_game() {
	dices.resize(5);
	for(int i = 0;i<5;i++) {
		dices[i] = 1;
	}
	lockinfo=0;
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
	int tmp = 1<<(4-index);
	lockinfo ^= tmp;
}

bool dice_game::get_lockinfo(int index) {	//index = 0~4
	int tmp = 1<<(4-index);
	//10110 3 00100

	bool _lockinfo;
	return 	_lockinfo;
}

int dice_game::get_lockinfo() {
	return lockinfo;
}