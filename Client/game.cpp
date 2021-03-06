#include "game.hpp"
#include <iostream>
#include <thread>
#include <stdlib.h>
#include <regex>
#ifdef _WIN32
#define ENTER_KEY 13
#else
#define ENTER_KEY 10
#include <termios.h>
#endif

game::game(int id,networkinterface * net) : id(id) , net(net) {
	_graphic = new lobbygraphic(this);
	dice_cursor = 0;
}


#ifdef _WIN32
#else
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
#endif

void _recive_from_server(networkinterface * net,game * _game) {
	std::string * server_str = net->GetStringToServer();
	std::list<std::string> str;
	std::string tmp;
	for(int i = 0;i<server_str->size();i++) {
		if(server_str->compare(i,5,"<end>") == 0) {
			str.push_back(tmp);
			tmp.clear();
			i+=4;
		}
		else tmp.push_back((*server_str)[i]);
	}
	if(!tmp.empty())	str.push_back(tmp);
	delete server_str;
	for(auto item : str) {
		_game->parseString(item);//문자열 분석부
	}
}


void recive_from_server(networkinterface * net,game * _game) {//서버에서 들어오는 문자열을 쓰레드로 관리한다.
	while(1)
	{
		_recive_from_server(net,_game);
	}
}

void input(networkinterface * net,game * _game) {//사용자가 입력하는 정보들을 쓰레드로 받는다.
	while(1) {
		int x = getch();
		if(_game->getChatStatus()) {
			if(x == ENTER_KEY) {
				_game->sendChatString();
				_game->chatStatusSwitch();
			}
			_game->set_chatString(x);
		}
		else {
			if(x == ENTER_KEY) {
				_game->chatStatusSwitch();
			}
			if(_game->getRoom()->getlevel() == 0) {
				if(x == 'r' || x == 'R') {
					std::string buffer = ydc::format_string("3 2 %d %d",_game->get_roomId(),_game->get_userId());
					net->SendStringToServer(buffer);
				}
			}
			else if(_game->getRoom()->getlevel() == 1){
				if(x == 'z') {	
					auto _room = dynamic_cast<gameroom*>(_game->getRoom());
					if(_room->is_orderUser(_game->get_userId())){
						dice_game & _dice = dynamic_cast<gameroom*>(_game->getRoom())->getdata();
						_dice.set_lockinfo(_game->getDiceCursor());
						std::string buffer = ydc::format_string("4 3 %d %d",_game->get_roomId(),_dice.get_lockinfo());
						net->SendStringToServer(buffer);
					}
				}
				if(x == 'r' || x == 'R') {
					auto _room = dynamic_cast<gameroom*>(_game->getRoom());
					if(_room->is_orderUser(_game->get_userId())){
						if(_room->get_rollCount()!=0){
							std::string buffer = ydc::format_string("4 2 %d",_game->get_roomId());
							net->SendStringToServer(buffer);
						}
					}
				}
				if(x == 'x') {
					auto _room = dynamic_cast<gameroom*>(_game->getRoom());
					if(_room->is_orderUser(_game->get_userId())) {
						if(_room->get_rollCount() != 3) {
							std::string buffer = ydc::format_string("4 4 %d %d",_game->get_roomId(),_game->getScoreCursor());
							net->SendStringToServer(buffer);
						}
					}
				}
#ifdef _WIN32
                else if(x == 224) {
#else
                else if(x == 91) {
#endif
					x = getch();
#ifdef _WIN32
                    if(x == 72) {
#else
					if(x == 65) {
#endif
						_game->setScoreCursor(-1);
						//down
					}
#ifdef _WIN32
                    else if(x == 80) {
#else
					else if(x == 66) {
#endif
						_game->setScoreCursor(1);
						//up
					}
#ifdef _WIN32
                    else if(x == 77) {
#else
					else if(x == 67) {
#endif
						_game->setDiceCursor(1);
						//right
					}
#ifdef _WIN32
                    else if(x == 75) {
#else
					else if(x == 68) {
#endif
						_game->setDiceCursor(-1);
						//left
					}
					_game->graphics();
				}
			}
			else {
				_game->change_room(0);
				_game->graphics();
			}
		}
	}
}

void game::start() {
	char name[20];
	std::cout<<"사용할 닉네임을 정해주세요. (20자 제한)\n"; 
	std::cin >> name;
	//유저 정보 전송
	std::string buffer = ydc::format_string("0 0 %d %s",id,name); 
	net->SendStringToServer(buffer);
	do {
		std::cout<<"게임 입장\n";
		std::cout<<"1. 방 생성  2. 방 입장  3. 게임 종료\n";
		char choice;
		std::cin>>choice; 
		bool check_while = false;
		if(choice == '1') {
			std::cout<<"방 제목을 입력해주세요.\n";
			char buff[1008];
			std::cin>>buff;
			int max_num = 8;
			do {
				std::cout<<"방 최대 인원을 입력해 주세요. (2명 이상 5명 이하)\n";
				std::cin>>max_num;
				if(max_num < 2 || max_num > 5) {
					std::cout<<"다시 입력해 주세요.\n";
					continue;
				}
				break;
			}while(1);

			std::string buffer = ydc::format_string("3 0 %d %s %d",id,buff,max_num);
			net->SendStringToServer(buffer);
			//net->SendStringToServer("9 9 hello\n")
			_recive_from_server(net,this);
			buffer = ydc::format_string("3 1 %d %d",_room->getRoomId(),id);
			net->SendStringToServer(buffer);
		}
		else if(choice == '2') {
			std::string buffer = ydc::format_string("3 3 %d",id);
			net->SendStringToServer(buffer);
			_recive_from_server(net,this);
			if(roomList.empty()) {
				std::cout<<"생성된 방이 존재하지 않습니다. 초기화면으로 되돌아갑니다.\n";
				continue;
			}
			do {
				std::cout<<"숫자 : 참가할 방 , q : 뒤로가기\n";

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
				std::string buffer = ydc::format_string("3 1 %d %d",(*itor)->getRoomId(),id);
				net->SendStringToServer(buffer);
				_recive_from_server(net,this);		
				if(this->getRoom() == NULL){
					std::cout << (*itor)->getRoomId()+1 << "번 방은 가득차서 입장할 수 없습니다. 다시 선택해주세요\n";
					continue;
				}
				else break;
			}while(1);
		}
		else if (choice == '3') {
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

	buffer = ydc::format_string("1 0 %d",_room->getRoomId());
	net->SendStringToServer(buffer);
	buffer = ydc::format_string("0 1 %d",_room->getRoomId());
	net->SendStringToServer(buffer);
	std::thread t2(input,net,this);
	std::thread t1(recive_from_server,net,this);
	t1.detach();
	t2.join();
	graphics();
}

void game::graphics() {
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
	_graphic->run();
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
	graphics();
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
		if(token[1] == "2") {
			auto tmp = _room;
			_room = new gameroom(_room);
			delete tmp;
			auto tmp2 = _graphic;
			_graphic = new gamegraphic(this);
			delete tmp2;
		}
		else if(token[1] == "3"){
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
				if(_room->getlevel() == 0) {
					userList.push_back(new lobbyuser(std::stoi(token[j]),token[j+1].c_str(),std::stoi(token[j+2])));
				}
				else userList.push_back(new gameuser(std::stoi(token[j]),token[j+1].c_str()));
				j+=3;
			}
		}
		if(token[1] == "1") {
			std::list<std::string>& chatList = _room->getChatList();
			chatList.clear();
			int n = std::stoi(token[2]);
			int j = 3;
			for(int i = 3;i<3+n;i++) {
				std::string buff = ydc::format_string("%s : %s",token[j].c_str(),
					std::regex_replace(token[j+1].c_str(),std::regex("_")," ").c_str());
				chatList.push_back(buff);
				j+=2;
			}
		}
		if(token[1] == "-1") {
			
		}
	}
	else if(token[0] == "2") {
		if(token[1] == "1") {
			auto _gameroom =dynamic_cast<gameroom*>(_room);
			for(int i = 0;i<5;i++) {
				_gameroom->getdata().set_dice(i,std::stoi(token[2+i]));
			}
			_gameroom->set_rollCount();
		}
		else if(token[1] == "3") {
			dynamic_cast<gameroom*>(_room)->getdata().set_lockinfo2(std::stoi(token[2]));
		}
		else if(token[1] == "5") {
			auto _gameroom = dynamic_cast<gameroom*>(_room);
			auto& data = _gameroom->get_orderUser()->getScoreBoard();
			data.setValue(std::stoi(token[2]),std::stoi(token[3]));
			_gameroom->change_order();
			setScoreCursor();
			if(_gameroom->getTurn() == 12) {
				delete _graphic;
				_graphic = new scoregraphic(this);
				_gameroom->change_level();
			}
		}
	}
	else {
		return;
	}
	//분석 후에 새로 들어온 데이터를 화면에 반영해준다.
	graphics();
}

void game::sendChatString() {
	const std::u16string& chat_str = get_chatString();
	if(chat_str.empty()) return;
	else {
		char buf[1008];
		int i = 0;
		for (const auto& c: chat_str) {
			if(c==' ') buf[i++] = '_';//채팅 문자열의 공백을 언더바로 바꾼다
			else buf[i++] = c;
		}
		buf[i] = '\0';
		std::string buffer = ydc::format_string("1 1 %d %d %s",get_roomId(),get_userId(),buf);
		net->SendStringToServer(buffer);
		clearChatString();
	}
}

void game::change_room(int index) {
	if(index == 0) {
		auto tmp = _room;
		_room = new room(dynamic_cast<gameroom *>(_room));
		delete tmp;
		auto tmp2 = _graphic;
		_graphic = new lobbygraphic(this);
		delete tmp2;	
	}
}

void game::setScoreCursor(int a) {
	if(a < 0 && score_cursor == 0) return;
	if(a > 0 && score_cursor == 12) return;
	int scorelock = dynamic_cast<gameroom *>(getRoom())->
						get_orderUser()->getScoreBoard().isScoreLock();
	scorelock |= 1<<(12-7+1);
	if(a == -1) {//업
		scorelock>>=(12-score_cursor+1);
		int n = score_cursor;
		for(int i = 0;i<n;i++) {
			if(!(scorelock%2)) {
				score_cursor = n-i-1;
				break;
			}
			else scorelock>>=1;
		}
	}
	else if (a == 1) {//다운
		scorelock &= (1<<(12-score_cursor))-1;
		int start = score_cursor+1;
		for(int i = 12-start;i>=0;i--) {
			if(!(scorelock&(1<<i))) {
				score_cursor = 12-i;
				break;
			}
		}

	}
}
void game::setScoreCursor() {
	int scorelock = dynamic_cast<gameroom *>(getRoom())->
						get_orderUser()->getScoreBoard().isScoreLock();
	scorelock &= (1<<12)-1;
	scorelock |= 1<<(12-7+1);
	for(int i = 11;i>=0;i--) {
		if(!(scorelock&(1<<i))) {
			score_cursor = 12-i;
			break;
		}
	}
}