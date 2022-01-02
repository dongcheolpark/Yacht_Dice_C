#include "network.hpp"
#include "game.hpp"
#include <iostream>
#include <string>
#include <termios.h>
#include <thread>
using std::thread;

using namespace std;

int id = 0;


int main(int argc, char const *argv[])
{
	network * net = new network();
	while((id = net->join()) == 0) {
		char a;
		cout<<"서버와 다시 연결 하시겠습니까? Y/N"<<endl;
		cin>>a;
		if(a == 'N'||a == 'n') {
			cout<<"종료합니다."<<endl;
			return 0;
		}
	}//서버와 연결을 시도한다.
	game * _game = new game();
	_game->start(net);
	return 0;
}