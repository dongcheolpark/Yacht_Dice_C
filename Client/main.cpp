#include "network.hpp"
#include "game.hpp"
#include <iostream>
#include <string>
#include <termios.h>
#include <thread>
using std::thread;

using namespace std;

int id = 0;

int getch(void)
{
	int ch;
	struct termios old;
	struct termios new_;
	tcgetattr(0, &old);
	new_ = old;
	new_.c_lflag &= ~(ICANON | ECHO);
	new_.c_cc[VMIN] = 1;
	new_.c_cc[VTIME] = 0;
	tcsetattr(0, TCSAFLUSH, &new_);
	ch = getchar();
	tcsetattr(0, TCSAFLUSH, &old);
	return ch;
}

void recive_from_server(network * net,game * _game) {//서버에서 들어오는 문자열을 쓰레드로 관리한다.
	while(1)
	{
		char * buffer = net->GetStringToServer();
		std::list<std::string> str;
		std::string tmp;
		for(int i = 0;i<strlen(buffer);i++) {
			if(strncmp(buffer+i,"<end>",5) == 0) {
				str.push_back(tmp);
				tmp.clear();
				i+=4;
			}
			else tmp.push_back(buffer[i]);
		}
		if(!tmp.empty())	str.push_back(tmp);
		for(auto item : str) {
			_game->parseString(item.c_str());//문자열 분석부
		}
		delete buffer;
	}
}

void input(network * net,game * _game) {//사용자가 입력하는 정보들을 쓰레드로 받는다.
	while(1) {
		int x = getch();
		if(x == 10) {
			const std::u16string& chat_str = _game->get_chatString();
			if(chat_str.empty()) continue;
			if(chat_str == u"ready") {
				char buffer[1024];
				sprintf(buffer,"2 0 %d",id);
				net->SendStringToServer(buffer);
			}
			else {
				char buf[1024];
				int i = 0;
				for (const auto& c: chat_str) {
					if(c==' ') buf[i++] = '_';//채팅 문자열의 공백을 언더바로 바꾼다
					else buf[i++] = c;
				}
				buf[i] = '\0';
				char buffer[1024]; 
				sprintf(buffer,"1 1 %d %s",id,buf)다
				net->SendStringToServer(buffer);
			}
		}
		_game->set_chatString(x);
	}
}

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
	thread t1(recive_from_server,net,_game);
	char name[20];
	//cout<<getch();
	cout<<"사용할 닉네임을 정해주세요. (20자 제한)\n";
	cin>>name;
	char buffer[1024]; 
	//유저 정보 전송
	sprintf(buffer,"0 0 %d %s",id,name);
	net->SendStringToServer(buffer);
	//채팅 리스트 받아오기
	sprintf(buffer,"1 0");
	net->SendStringToServer(buffer);
	thread t2(input,net,_game);
	_game->start(net);
	t1.join();
	t2.join();
	return 0;
}