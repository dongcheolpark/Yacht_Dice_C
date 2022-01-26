#include <typeinfo>
#include "../game.hpp"

int testfile(int argc, char ** argv) {
	game * a;
	if(typeid(a) == typeid(game)) return 0;
	return 1;
}