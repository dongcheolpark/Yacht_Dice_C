#include "game.hpp"
#include <iostream>

void game::start(network * net) {
	graphic();
}

void game::set_chatString(int x) {
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

void game::graphic() {
	system("clear");
	for(auto item : userList) {
		std::cout<<item->getuserName()<<' ';
	}
	std::cout<<std::endl;
	for(auto item : chatList) {
		std::cout<<item<<std::endl;
	}
	for (const auto& c: chat_str)
	    std::cout << static_cast<char>(c);
	
	std::cout<<std::endl;
}

void game::parseString(const char * buffer) {
	//std::cout<<buffer<<std::endl;
	std::vector<std::string> token;
	std::string tmp;
	for(int i = 0;i<strlen(buffer);i++) {
		if(buffer[i] == ' ') {
			token.push_back(std::string(tmp));
			tmp.clear();
		}
		else tmp.push_back(buffer[i]);
	}
	token.push_back(tmp);
	if(token[0] == "0") {
		if(token[1] == "0") {
			int n = std::stoi(token[2]);
			int j = 3;
			userList.clear();
			for(int i = 3;i<3+n;i++) {
				userList.push_back(new user(std::stoi(token[j]),token[j+1].c_str()));
				j+=2;
			}
		}
		if(token[1] == "-1") {
			
		}
	}
	else if(token[0] == "1") {
		if(token[1] == "0") {
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
	}
	graphic();
}