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
		printf("|%15s|",item->getuserName());
	}
	std::cout<<std::endl;
}

void lobbygraphic::run() {
	auto _room = _game->getRoom();
	auto userList = _room->getUserList();
	auto chatList = _room->getChatList();
	showPeople();
	for(auto item : userList) {
		printf("%16s ",((lobbyuser *)item)->getUserReady() ? "Ready" : " ");
	}
	showchatLists();
	for (const auto& c: _game->get_chatString())
	    std::cout << static_cast<char>(c);
	
	std::cout<<std::endl;

}

void gamegraphic::dice() {

}

void gamegraphic::score() {
	auto _room = _game->getRoom();
	std::list<user*> & userList = _room->getUserList();
	std::list<scoreboard> tableList;
	for(auto item : userList) {
		tableList.push_back(dynamic_cast<gameuser *>(item)->getScoreBoard());
	}
	for(auto item : tableList) {
		std::cout<<"|   ACES   | "<<std::setw(2)<<item.getUp(1)<<" |";
	}
	std::cout<<"\n";
	for(auto item : tableList) {
		std::cout<<"|  Deuces  | "<<std::setw(2)<<item.getUp(2)<<" |";
	}
	std::cout<<"\n";
	for(auto item : tableList) {
		std::cout<<"|  Threes  | "<<std::setw(2)<<item.getUp(3)<<" |";
	}
	std::cout<<"\n";
	for(auto item : tableList) {
		std::cout<<"|  Small   | "<<"  "<<" |";
	}
	std::cout<<"\n";
	for(auto item : tableList) {
		std::cout<<"|          | "<<std::setw(2)<<item.getUp(1)<<" |";
	}
	std::cout<<"\n";
	for(auto item : tableList) {
		std::cout<<"| Straight | "<<"  "<<" |";
	}
	std::cout<<"\n";
}

void gamegraphic::run() {
	showPeople();
	score();
}