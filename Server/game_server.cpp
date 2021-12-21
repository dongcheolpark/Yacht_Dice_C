#include "game_server.hpp"
#include "game_server_parse.hpp"
#include <string>
send_struct * game_server::parseString(const char * buffer) {
	std::vector<std::string> token;
	std::string tmp;
	game_server_parse * parse = NULL;
	for(int i = 0;i<strlen(buffer);i++) {
		if(buffer[i] == ' ') {
			token.push_back(std::string(tmp));
			tmp.clear();
		}
		else tmp.push_back(buffer[i]);
	}//문자열을 스페이스바를 기준으로 토큰화 한다.
	token.push_back(tmp);
	//토큰을 분석해준다.
	if(token[0] == "0") {
		//유저 리스트에 추가
		if(token[0] == "0") {
			user * _user = new user(std::stoi(token[2]),token[3].c_str());
			userList.push_back(_user);
			parse = new game_server_send_userList(this);
		}
	}
	else if(token[0] == "1") {
		if(token[1] == "0") {
			parse = new game_server_send_chatList(this);
		}
		else if(token[1] == "1") {
			if(chatList.size() >= 5) {
				chatList.pop_front();
			}
			char buff[1024];
			int id = std::stoi(token[2]);
			user * _user = NULL;
			for(auto item : userList) {
				if(id == item->getuserId()) {
					_user = item;
					break;
				}
			}
			sprintf(buff,"%s %s",_user->getuserName(),token[3].c_str());
			//puts(buff);
			chatList.push_back(buff);
			parse = new game_server_send_chatList(this);
		}
	}
	auto * data = parse->doParse();//전송 데이터를 가져온다.
	delete parse;
	//printf("%s\n",data->str->c_str());
	return data;
}

send_struct * game_server::processing(int index) {//바뀐 정보를 바로바로 전송할 때 사용한다.
	game_server_parse * parse = NULL;
	if(index == 1) {
		parse = new game_server_send_userList(this);
	}
	auto data = parse->doParse();
	delete parse;
	return data;
}

void game_server::remove_user(int id) {
	userList.remove_if([id](user * value) {
		return value->getuserId() == id;
	});
}