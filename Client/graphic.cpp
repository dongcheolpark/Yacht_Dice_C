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
		printf("|%-15s|",item->getuserName());
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



void gamegraphic::score() {
	auto _room = _game->getRoom();
	std::list<user*> & userList = _room->getUserList();
	std::list<scoreboard> tableList;
	for(auto item : userList) {
		tableList.push_back(dynamic_cast<gameuser *>(item)->getScoreBoard());
	}
	for(auto item : tableList) {
		std::cout<<"|Aces       |"<<std::setw(2)<<item.getUp(1)<<" |";
	}
	std::cout<<"\n";
	for(auto item : tableList) {
		std::cout<<"|Deuces     |"<<std::setw(2)<<item.getUp(2)<<" |";
	}
	std::cout<<"\n";
	for(auto item : tableList) {
		std::cout<<"|Threes     |"<<std::setw(2)<<item.getUp(3)<<" |";
	}
	std::cout<<"\n";
	for(auto item : tableList) {
		std::cout<<"|Fours      |"<<std::setw(2)<<item.getUp(4)<<" |";
	}
	std::cout<<"\n";
	for(auto item : tableList) {
		std::cout<<"|Fives      |"<<std::setw(2)<<item.getUp(5)<<" |";
	}
	std::cout<<"\n";
	for(auto item : tableList) {
		std::cout<<"|Sixes      |"<<std::setw(2)<<item.getUp(6)<<" |";
	}
	std::cout<<"\n";
	for(auto item : tableList) {
		std::cout<<"|+35 Bonus  |"<<std::setw(2)<<item.getBonus()<<" |";
	}
	std::cout<<"\n";
	for(auto item : tableList) {
		std::cout<<"|Choice     |"<<std::setw(2)<<item.getDown(1)<<" |";
	}
	std::cout<<"\n";
	for(auto item : tableList) {
		std::cout<<"|4 of a Kind|"<<std::setw(2)<<item.getDown(2)<<" |";
	}
	std::cout<<"\n";
	for(auto item : tableList) {
		std::cout<<"|Full House |"<<std::setw(2)<<item.getDown(3)<<" |";
	}
	std::cout<<"\n";
	for(auto item : tableList) {
		std::cout<<"|S. Straight|"<<std::setw(2)<<item.getDown(4)<<" |";
	}
	std::cout<<"\n";
	for(auto item : tableList) {
		std::cout<<"|L. Straight|"<<std::setw(2)<<item.getDown(5)<<" |";
	}
	std::cout<<"\n";
	for(auto item : tableList) {
		std::cout<<"|Yacht      |"<<std::setw(2)<<item.getDown(6)<<" |";
	}
	std::cout<<"\n";
	for(auto item : tableList) {
		std::cout<<"|Total      |"<<std::setw(2)<<item.getscore()<<" |";
	}
	std::cout<<"\n";
}

void gamegraphic::help() {
	std::cout<<"주사위를 굴리려면 r을 눌러주세요."<<'\n';
}

void gamegraphic::run() {
	showPeople();
	score();
	showchatLists();
	dice();
	help();
	if(_game->getChatStatus()) {
		showChatString();
	}
}