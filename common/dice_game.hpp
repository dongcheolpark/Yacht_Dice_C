#pragma once
#include <vector>

class dice_game {
private:
	std::vector<int> dices;
	int lockinfo;
public:
	dice_game();
	dice_game(std::vector<int>);
	void set_dice(int,int);
	void set_dice(std::vector<int>&);
	std::vector<int> get_dices();
	int get_dices(int);
	void set_lockinfo(int);
	void set_lockinfo2(int tmp) {lockinfo=tmp;}
	bool get_lockinfo(int);
	int get_lockinfo();
};
