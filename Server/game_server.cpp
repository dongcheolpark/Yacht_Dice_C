#include "game_server.hpp"
#include <string>
send_struct * game_server::parseString(char * buffer) {
	std::vector<std::string> token;
	std::string tmp;
	send_struct * data = new send_struct();
	for(int i = 0;i<strlen(buffer);i++) {
		if(buffer[i] == ' ') {
			token.push_back(std::string(tmp));
			tmp.clear();
		}
		else tmp.push_back(buffer[i]);
	}
	token.push_back(tmp);
	if(token[0] == "0") {
		//유저 리스트에 추가
		user * _user = new user(std::stoi(token[1]),token[2].c_str());
		userList.push_back(_user);
		//유저 리스트 전송
		data->str->append(data->format_string("1 0 %d ",userList.size()));
		for(auto item : userList) {
			data->list->push_back(item);
			data->str->append(data->format_string("%d %s ",item->getuserId(),item->getuserName()));
		}
	}
	return data;
}

void game_server::remove_user(int id) {
	userList.remove_if([id](user * value) {
		return value->getuserId() == id;
	});
}