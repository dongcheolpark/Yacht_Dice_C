#pragma once
#include <iostream>
#include "game.hpp"

class game;

class graphic {
protected:
	game * _game = NULL;	
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
};