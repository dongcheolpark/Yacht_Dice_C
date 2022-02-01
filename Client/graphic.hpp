#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include "../common/scoreboard.hpp"
#include "game.hpp"

class game;

class graphic {
protected:
	game * _game = NULL;	
	void showchatLists();
	void showPeople();
	void showChatString();
public:
	graphic(game * _game) {
		this->_game = _game;
	}
	virtual void run() {}
};

class lobbygraphic : public graphic {
private:
	void help();
public:
	lobbygraphic(game * _game) : graphic(_game) {}
	void run();
};

class gamegraphic : public graphic {
private:
	void dice();
	void score();
	void help();
	void order();
public:
	gamegraphic(game * _game) : graphic(_game) {}
	void run();
};