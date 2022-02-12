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
		if(token[1] == "0") {
			user * _user = new lobbyuser(std::stoi(token[2]),token[3].c_str(),false);
			serverUserList.push_back(_user);
		}
		if(token[1] == "1") {
			parse = new game_server_send_userList(this,stoi(token[2]));
		}
	}
	else if(token[0] == "1") {
		if(token[1] == "0") {
			parse = new game_server_send_chatList(this,stoi(token[2]));
		}
		else if(token[1] == "1") {
			room * _room = getRoom(stoi(token[2]));
			auto userList = _room->getUserList();
			std::list<std::string>& chatList = _room->getChatList();
			if(chatList.size() >= 5) {
				chatList.pop_front();
			}
			int id = std::stoi(token[3]);
			user * _user = NULL;
			for(auto item : userList) {
				if(id == item->getuserId()) {
					_user = item;
					break;
				}
			}
			std::string buff = ydc::format_string("%s %s",_user->getuserName(),token[4].c_str());
			chatList.push_back(buff);
			printf("%ld\n",chatList.size());
			parse = new game_server_send_chatList(this,_room->getRoomId());
		}
	}
	else if(token[0] == "2") {

	}
	else if(token[0] == "3") {
		if(token[1] == "0") {
			int roomId =  roomList.empty() ? 0 : roomList.back()->getRoomId()+1;
			roomList.push_back(new room(roomId,token[3].c_str(),std::stoi(token[4])));
			user * _user;
			for(auto item : serverUserList) {
				if(item->getuserId() == std::stoi(token[2])) {
					_user = item;
				}
			}
			parse = new game_server_send_roomInfo(this,roomId,_user);
		}
		else if(token[1] == "1") {
			room * _room = getRoom(std::stoi(token[2]));
			user * _user;
			for(auto item : serverUserList) {
				if(item->getuserId() == std::stoi(token[3])) {
					_user = item;
				}
			}
			if(_room->getRoomMaxPeople()<=_room->getRoomCurrentPeople()){
				parse = new game_server_send_blockentry(this,_room->getRoomId(),_user);
			}
			else{
				_room->getUserList().push_back(_user);
				parse = new game_server_send_roomInfo(this,_room->getRoomId(),_user);
			}
		}
		else if(token[1] == "2") {
			room * _room = getRoom(std::stoi(token[2]));
			auto userList = _room->getUserList();
			bool check = true;
			for(auto item : userList) {
				lobbyuser* _lobbyuser;
				if(item->getuserId() == std::stoi(token[3])) {
					if((_lobbyuser = dynamic_cast<lobbyuser *>(item)) != NULL) {
						_lobbyuser->switchUserReady();
					}
				} 
				if((_lobbyuser = dynamic_cast<lobbyuser *>(item)) != NULL) {
					if(_lobbyuser->getUserReady() != true) check = false;
				}
				else check = false;
			}
			if(check) {
				gameroom * _gameroom = new gameroom(_room);
				roomList.push_back(_gameroom);
				roomList.remove(_room);
				delete _room;
				std::cout<<_gameroom->getUserList().front()->getuserId()<<'\n';
				parse = new game_server_change_gameroom(this,_gameroom->getRoomId());
			}
			else parse = new game_server_send_userList(this,_room->getRoomId());
		}
		else if(token[1] == "3") {
			user * _user;
			for(auto item : serverUserList) {
				if(item->getuserId() == std::stoi(token[2])) {
					_user = item;
				}
			}
			parse = new game_server_send_roomList(this,_user);
		}
	}
	else if(token[0] == "4") {
		if(token[1] == "1") {

		}
		else if(token[1] == "2") {
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<int> dis(1, 6);
			int roomid = std::stoi(token[2]);
			gameroom * _room = dynamic_cast<gameroom *>(getRoom(roomid));
			dice_game& dices = _room->getdata();
			for(int i = 0;i<5;i++) {
				if(!(dices.get_lockinfo(i))){
					dices.set_dice(i,dis(gen));
				}
			}
			parse = new game_server_send_dices(this,roomid);
		}
		else if(token[1] == "3") {
			int roomid = std::stoi(token[2]);
			gameroom * _room = dynamic_cast<gameroom *>(getRoom(roomid));
			dice_game& dices = _room->getdata();
			dices.set_lockinfo2(std::stoi(token[3]));
			parse = new game_server_send_lockinfo(this,roomid);
		}
		else if(token[1] == "4") {
			int roomid = std::stoi(token[2]);
			gameroom * _room = dynamic_cast<gameroom *>(getRoom(roomid));
			int scorecursor = std::stoi(token[3]);
			auto& scoreboard = _room->get_orderUser()->getScoreBoard();
			int value = scoreboard.display(_room->getdata())[scorecursor];
			scoreboard.setValue(scorecursor,value);
			_room->change_order();
			if(dynamic_cast<gameroom*>(_room)->getTurn() == 14) {
				roomList.push_back(new room(dynamic_cast<gameroom *>(_room)));
				roomList.remove(_room);
			}
			parse = new game_server_change_order(this,roomid,scorecursor,value);
		}
	}
	if(parse == NULL) return NULL;
	auto * data = parse->doParse();//전송 데이터를 가져온다.
	delete parse;
	//printf("%s\n",data->str->c_str());
	return data;
}

send_struct * game_server::processing(int index,int roomId) {//바뀐 정보를 바로바로 전송할 때 사용한다.
	game_server_parse * parse = NULL;
	if(index == 1) {
		parse = new game_server_send_userList(this,roomId);
	}
	auto data = parse->doParse();
	delete parse;
	return data;
}

send_struct * game_server::remove_user(int id) {
	serverUserList.remove_if([id](user * value) {
		return value->getuserId() == id;
	});
	for(auto item : roomList) {
		for(auto item2 : item->getUserList()) {
			if(item2->getuserId() == id) {
				item->getUserList().remove(item2);	
				if(item->getUserList().empty()) {
					roomList.remove(item);
					return NULL;
				}
				return processing(1,item->getRoomId());
			}
		}
	}
	return NULL;
}

room * game_server::getRoom(int roomId) {
	for(auto item : roomList) {
		if(item->getRoomId() == roomId) {
			return item;
		}
	}
	return NULL;
}