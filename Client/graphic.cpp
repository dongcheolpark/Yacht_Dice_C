#include "graphic.hpp"
void graphic::showchatLists() {
	auto _room = _game->getRoom();
	auto chatList = _room->getChatList();
	std::cout<<std::endl;
	for(auto item : chatList) {
		std::cout<<item<<std::endl;
	}
}

void graphic::showPeople() {
	auto _room = _game->getRoom();
	std::list<user*> & userList = _room->getUserList();

	printf("| %s | %ld/%d|\n",_room->getRoomName(),userList.size(),_room->getRoomMaxPeople());
	for(auto item : userList) {
		printf("|%-16s|",item->getuserName());
	}
	std::cout<<std::endl;
}

void graphic::showChatString() {
	std::cout<<"채팅 : ";
	for (const auto& c: _game->get_chatString())
	    std::cout << static_cast<char>(c);
	
	std::cout<<std::endl;
}

void lobbygraphic::help() {
	std::cout<<"레디하시려면 r 키를 눌러주세요."<<'\n';
}

void lobbygraphic::run() {
	auto _room = _game->getRoom();
	auto userList = _room->getUserList();
	auto chatList = _room->getChatList();
	showPeople();
	for(auto item : userList) {
		printf("%16s ",((lobbyuser *)item)->getUserReady() ? "Ready" : " ");
	}
	std::cout<<"\n";
	showchatLists();
	help();
	if(_game->getChatStatus()) {
		showChatString();
	}
}

void gamegraphic::dice() {
	auto data = dynamic_cast<gameroom *>(_game->getRoom())->getdata();
	std::cout<<"\n\n   ";
	for(int i = 0;i<5;i++) {
		if(data.get_lockinfo(i)) {
			std::cout<<"-";
		}
		else std::cout<<" ";
		std::cout<<" ";
	}
	std::cout<<"\n   ";
	for(int i = 0;i<5;i++) {
		std::cout<<data.get_dices(i)<<" ";
	}
	std::cout<<"\n   ";
	for(int i = 0;i<5;i++) {
		if(i == _game->getDiceCursor()) {
			std::cout<<"-";
		}
		else std::cout<<" ";
		std::cout<<" ";
	}
	std::cout<<"\n";
}

void gamegraphic::scoreShell(int index,std::string name, std::list<std::vector<int>> & tableList) {
	auto _room = dynamic_cast<gameroom *>(_game->getRoom());
	auto order = _room->get_order();
	int i = 0;
	for(auto item : tableList) {
		std::cout<<name<<std::setw(3)<<item[index];
		if(index == _game->getScoreCursor() && i == order && _room->is_orderUser(_game->get_userId())) {std::cout<<"||";}
		else std::cout<<" |";
		i++;
	}
	std::cout<<"\n";
}


void gamegraphic::score() {
	auto _room = _game->getRoom();
	std::list<user*> & userList = _room->getUserList();
	std::list<std::vector<int>> tableList;
	dice_game & dice = dynamic_cast<gameroom *>(_room)->getdata();
	for(auto item : userList) {
		tableList.push_back(dynamic_cast<gameuser *>(item)->getScoreBoard().display(dice));
	}
	std::vector<std::string> scoreList1({"|Aces       |", "|Deuces     |", "|Threes     |",
										 "|Fours      |", "|Fives      |", "|Sixes      |"});
	std::vector<std::string> scoreList2({"|Choice     |", "|4 of a Kind|", "|Full House |",
										 "|S. Straight|", "|L. Straight|", "|Yacht      |"});
	int index = 0;
	for(int i = 0; i < 6; i++){
		scoreShell(index,scoreList1[i],tableList);
		index++;
	}
	scoreShell(index,"|+35 Bonus  |",tableList);
	index++;
	for(int i = 0; i < 6; i++){
		scoreShell(index,scoreList2[i],tableList);
		index++;
	}
	scoreShell(index,"|Total      |",tableList);
}

void gamegraphic::help() {
	std::cout<<"주사위를 굴리려면 r을 눌러주세요."<<'\n';
}

void gamegraphic::order() { 
	auto _user = dynamic_cast<gameroom *>(_game->getRoom())->get_orderUser();
	std::cout<<_user->getuserName()<<"님의 차례입니다."<<'\n';
}

void gamegraphic::run() {
	showPeople();
	score();
	showchatLists();
	dice();
	order();
	help();
	if(_game->getChatStatus()) {
		showChatString();
	}
}

void scoregraphic::run() {
	showPeople();
	total_score();
	if(_game->getChatStatus()) {
		showChatString();
	}
}

void scoregraphic::total_score() {
	auto _room = dynamic_cast<gameroom *>(_game->getRoom());
	std::list<user*> & userList = _room->getUserList();
	for(auto item : userList) {
		printf("|%-16s|",item->getuserName());
	}
	for(auto item : userList) {
		auto scoreboard = dynamic_cast<gameuser*>(item)->getScoreBoard();
		printf("|%-16d|",scoreboard.getscore());
	}
}