#include "graphic.hpp"

void lobbygraphic::run() {
	auto _room = _game->getRoom();
	auto userList = _room->getUserList();
	auto chatList = _room->getChatList();
	printf("| %s | %ld/%d\n",_room->getRoomName(),userList.size(),_room->getRoomMaxPeople());
	for(auto item : userList) {
		printf("%20s ",item->getuserName());
	}
	std::cout<<std::endl;
	for(auto item : userList) {
		printf("%20s ",((lobbyuser *)item)->getUserReady() ? "Ready" : " ");
	}
	std::cout<<std::endl;
	for(auto item : chatList) {
		std::cout<<item<<std::endl;
	}
	for (const auto& c: _game->get_chatString())
	    std::cout << static_cast<char>(c);
	
	std::cout<<std::endl;

}