#pragma once
#include <vector>

class dice_game {
private:
	std::vector<int> dices;
public:
	dice_game();
	void set_dice(int,int);
	void set_dice(std::vector<int>&);
	std::vector<int> get_dices();
	int get_dices(int);
};
