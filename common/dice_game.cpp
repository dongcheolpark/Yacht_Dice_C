#include "dice_game.hpp"

dice_game::dice_game() {

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