#include "game_server.hpp"

void game_server::parseString(char * buffer) {
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
		userList.push_back(new user(std::stoi(token[1]),token[2].c_str()));
	}
}

void game_server::remove_user(int id) {
	userList.remove_if([id](user * value) {
		return value->getuserId() == id;
	});
}