#pragma once
#include <iostream>
#include <iomanip>
#include "../common/scoreboard.hpp"
#include "game.hpp"

class game;

class graphic {
protected:
	game * _game = NULL;	
	void showchatLists();
	void showPeople();
public:
	graphic(game * _game) {
		this->_game = _game;
	}
	virtual void run() {}
};

class lobbygraphic : public graphic {
public:
	lobbygraphic(game * _game) : graphic(_game) {}
	virtual void run();
};

class gamegraphic : public graphic {
public:
	gamegraphic(game * _game) : graphic(_game) {}
	void dice();
	void score();
	virtual void run();
};