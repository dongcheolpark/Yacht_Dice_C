#include "game.hpp"
#include <iostream>

void game::start(network * net) {
	graphic();
}

void game::graphic() {
	for(auto item : userList) {
		std::cout<<item->getuserName()<<' ';
	}
	std::cout<<std::endl;
}

void game::parseString(char * buffer) {
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
	if(token[0] == "1") {
		if(token[1] == "0") {
			int n = std::stoi(token[2]);
			int j = 3;
			for(int i = 3;i<3+n;i++) {
				userList.push_back(new user(std::stoi(token[j]),token[j+1].c_str()));
				j+=2;
			}
		}
		if(token[1] == "-1") {
			
		}
	}
	graphic();
}