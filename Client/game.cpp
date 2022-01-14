#include "game.hpp"
#include <iostream>
#include <thread>
#include <stdlib.h>
#include <termios.h>

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
			_game->parseString(item);//문자열 분석부
		}
	}
}

void input(network * net,game * _game) {//사용자가 입력하는 정보들을 쓰레드로 받는다.
	while(1) {
		int x = getch();
		if(x == 10) {
			const std::u16string& chat_str = _game->get_chatString();
			if(chat_str.empty()) continue;
			//문자열에 따라 채팅 구별(나중에 함수로 빼야함)
			if(chat_str == u"ready") {
				char buffer[1024];
				sprintf(buffer,"3 2 %d %d",_game->get_roomId(),_game->get_userId());
				net->SendStringToServer(buffer);
			}
			else {
				char buf[1008];
				int i = 0;
				for (const auto& c: chat_str) {
					if(c==' ') buf[i++] = '_';//채팅 문자열의 공백을 언더바로 바꾼다
					else buf[i++] = c;
				}
				buf[i] = '\0';
				char buffer[1024]; 
				sprintf(buffer,"1 1 %d %d %s",_game->get_roomId(),_game->get_userId(),buf);
				net->SendStringToServer(buffer);
			}
		}
		_game->set_chatString(x);
	}
}

void game::start(network * net) {
	std::thread t1(recive_from_server,net,this);
	t1.detach();
	char name[20];
	std::cout<<"사용할 닉네임을 정해주세요. (20자 제한)\n";
	std::cin>>name;
	char buffer[1024]; 
	//유저 정보 전송
	sprintf(buffer,"0 0 %d %s",id,name); 
	net->SendStringToServer(buffer);
	do {
		std::cout<<"게임 입장\n";
		std::cout<<"1. 방 생성  2. 방 입장  3. 게임 종료\n";
		int choice = 0;
		std::cin>>choice;
		bool check_while = false;
		if(choice == 1) {
			std::cout<<"방 제목을 입력해주세요.\n";
			char buff[1008];
			std::cin>>buff;
			int max_num = 8;
			do {
				std::cout<<"방 최대 인원을 입력해 주세요. (2명 이상 4명 이하)\n";
				std::cin>>max_num;
				if(max_num < 2 || max_num > 4) {
					std::cout<<"다시 입력해 주세요.\n";
				}
				break;
			}while(1);
			sprintf(buffer,"3 0 %d %s %d",id,buff,max_num);
			net->SendStringToServer(buffer);
			while(1) {
				if(_room != NULL) break;
			}
			sprintf(buffer,"3 1 %d %d",_room->getRoomId(),id);
			net->SendStringToServer(buffer);
		}
		else if(choice == 2) {
			char buff[1008];
			sprintf(buffer,"3 3 %d",id);
			net->SendStringToServer(buffer);
			while(1) {
				if(!roomList.empty()) break;
			}
			do {
				std::cout<<"숫자 : 참가할 방 , q : 뒤로가기"<<std::endl;
				int i = 1;
				for(auto item : roomList) {
					std::cout<<i<<" | "<<item->getRoomName()<<" | "<<item->getRoomMaxPeople()<<std::endl;
					i++;
				}
				char a;
				std::cin>>a;
				if(a == 'q' || a == 'Q') {
					check_while = true;
					break;
				}
				a -= '0';
				i = 0;
				std::list<room *>::iterator itor;
				for(itor = roomList.begin();i<a-1;i++,itor++);
				sprintf(buffer,"3 1 %d %d",(*itor)->getRoomId(),id);
				net->SendStringToServer(buffer);
				break;
			}while(1);
		}
		else if (choice == 3) {
			exit(1);
		}
		else {
			std::cout<<"잘못 입력하셨습니다. 다시 입력 해 주세요.\n";
			continue;
		}
		if(check_while) continue;
		break;
	}while(1);
	while(1) {
		if(_room != NULL) break;
	}

	sprintf(buffer,"1 0 %d",_room->getRoomId());
	net->SendStringToServer(buffer);
	sprintf(buffer,"0 1 %d",_room->getRoomId());
	net->SendStringToServer(buffer);
	std::thread t2(input,net,this);
	t2.join();
	graphic();
}

void game::set_chatString(int x) {//채팅 문자열 관리
	if(x == 127) {
		if(!(chat_str.empty())) {
			chat_str.pop_back();
		}
	}
	else if(x == 10) {
		chat_str.clear();
	}
	else {
		chat_str.push_back(x);
	}
	graphic();
}

void game::graphic() {//콘솔에 정보들을 띄워준다
	system("clear");
	auto userList = _room->getUserList();
	auto chatList = _room->getChatList();
	printf("| %s | %ld/%d\n",_room->getRoomName(),userList.size(),_room->getRoomMaxPeople());
	for(auto item : userList) {
		printf("%20s ",item->getuserName());
	}
	std::cout<<std::endl;
	for(auto item : userList) {
		printf("%20s ",item->getUserReady() ? "Ready" : " ");
	}
	std::cout<<std::endl;
	for(auto item : chatList) {
		std::cout<<item<<std::endl;
	}
	for (const auto& c: chat_str)
	    std::cout << static_cast<char>(c);
	
	std::cout<<std::endl;
}

void game::parseString(std::string buffer) {
	//서버에서 들어온 문자열을 분석한다.
	//std::cout<<buffer<<std::endl;
	std::vector<std::string> token;
	std::string tmp;
	for(int i = 0;i<buffer.size();i++) {
		if(buffer[i] == ' ') {
			token.push_back(std::string(tmp));
			tmp.clear();
		}
		else tmp.push_back(buffer[i]);
	}
	token.push_back(tmp);
	if(token[0] == "0") {
		if(token[1] == "0") {
			_room = new room(std::stoi(token[2]),token[3].c_str(),std::stoi(token[4]));
			return;
		}
		else if(token[1] == "1") {
			int n = std::stoi(token[2]);
			int j = 3;
			roomList.clear();
			for(int i = 3;i<3+n;i++) {
				roomList.push_back(new room(std::stoi(token[j]),token[j+1].c_str(),std::stoi(token[j+2])));
				j+=3;
			}
			return;
		}
	}
	else if(token[0] == "1") {
		if(token[1] == "0") {
			int n = std::stoi(token[2]);
			int j = 3;
			std::list<user*>& userList = _room->getUserList();
			userList.clear();
			for(int i = 3;i<3+n;i++) {
				userList.push_back(new user(std::stoi(token[j]),token[j+1].c_str(),std::stoi(token[j+2])));
				j+=3;
			}
		}
		if(token[1] == "1") {
			std::list<std::string>& chatList = _room->getChatList();
			chatList.clear();
			int n = std::stoi(token[2]);
			int j = 3;
			for(int i = 3;i<3+n;i++) {
				char buff[1024];
				sprintf(buff,"%s : %s",token[j].c_str(),token[j+1].c_str());
				chatList.push_back(buff);
				j+=2;
			}
		}
		if(token[1] == "-1") {
			
		}
	}
	//분석 후에 새로 들어온 데이터를 화면에 반영해준다.
	graphic();
}