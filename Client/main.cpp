#include "network.hpp"
#include "game.hpp"
#include <iostream>
#include <string>
#include <thread>

int main(int argc, char const *argv[])
{
#ifdef _WIN32
    system("chcp 65001");
	networkWin * net = new networkWin();
#else
	networkLinux * net = new networkLinux();
#endif
	int id;
	while((id = net->join()) == 0) {
		char a;
		std::cout<<"서버와 다시 연결 하시겠습니까? Y/N"<<std::endl;
		std::cin>>a;
		if(a == 'N'||a == 'n') {
			std::cout<<"종료합니다."<<std::endl;
			return 0;
		}
	}//서버와 연결을 시도한다.
	game * _game = new game(id,net);
	_game->start();
	return 0;
}