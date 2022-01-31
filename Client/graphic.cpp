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



void gamegraphic::score() {
	auto _room = _game->getRoom();
	std::list<user*> & userList = _room->getUserList();
	std::list<scoreboard> tableList;
	for(auto item : userList) {
		tableList.push_back(dynamic_cast<gameuser *>(item)->getScoreBoard());
	}
	std::vector<std::string> scoreList1({"|Aces       |", "|Deuces     |", "|Threes     |",
										 "|Fours      |", "|Fives      |", "|Sixes      |"});
	std::vector<std::string> scoreList2({"|Choice     |", "|4 of a Kind|", "|Full House |",
										 "|S. Straight|", "|L. Straight|", "|Yacht      |"});
	for(int i = 0; i < 6; i++){
		for(auto item : tableList) {
			std::cout<<scoreList1[i]<<std::setw(2)<<item.getUp(i)<<" |";
		}
		std::cout<<"\n";
	}
	for(auto item : tableList) {
		std::cout<<"|+35 Bonus  |"<<std::setw(2)<<item.getBonus()<<" |";
	}
	std::cout<<"\n";
	for(int i = 0; i < 6; i++){
		for(auto item : tableList) {
			std::cout<<scoreList2[i]<<std::setw(2)<<item.getDown(i)<<" |";
		}
		std::cout<<"\n";
	}
	for(auto item : tableList) {
		std::cout<<"|Total      |"<<std::setw(2)<<item.getscore()<<" |";
	}
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