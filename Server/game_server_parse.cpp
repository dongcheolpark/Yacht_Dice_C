#include "game_server_parse.hpp"
void game_server_parse::set_network_code(int first,int second)  {
	data->str->append(ydc::format_string("%d %d ",first, second));
}


send_struct * game_server_send_userList::doParse() {
	//유저 리스트 전송
	auto _room = server->getRoom(roomId);
	auto userList = _room->getUserList();
	data->str->append(ydc::format_string("%d ",userList.size()));
	for(auto item : userList) {
		data->list->push_back(item);
		data->str->append(ydc::format_string("%d %s %d ",item->getuserId(),item->getuserName(),((lobbyuser *)item)->getUserReady()));
	}
	return data;
}
send_struct * game_server_send_chatList::doParse() {
	//채팅 리스트 전송
	auto _room = server->getRoom(roomId);
	auto chatList = _room->getChatList();
	auto userList = _room->getUserList();
	for(auto item : userList) {
		data->list->push_back(item);
	}
	data->str->append(ydc::format_string("%d ",chatList.size()));
	for(auto item : chatList) {
		data->str->append(ydc::format_string("%s ",item.c_str()));
	}
	return data;
}

send_struct * game_server_send_roomInfo::doParse() {
	auto _room = server->getRoom(roomId);
	data->list->push_back(_user);
	data->str->append(ydc::format_string("%d %s %d",_room->getRoomId(),_room->getRoomName(),_room->getRoomMaxPeople()));
	return data;
}

send_struct * game_server_send_roomList::doParse() {
	data->list->push_back(_user);
	std::string res;
	int n = 0;
	for(auto item : server->getRoomList()) {
		if(typeid(*item) != typeid(gameroom)) {
			n++;
			res.append(ydc::format_string("%d %s %d ",item->getRoomId(),item->getRoomName(),item->getRoomMaxPeople()));
		}
	}	
	data->str->append(ydc::format_string("%d ",n));
	data->str->append(ydc::format_string("%s ",res.c_str()));
	return data;
}
send_struct * game_server_change_gameroom::doParse() {
	auto _room = server->getRoom(roomId);
	auto userList = _room->getUserList();
	for(auto item : userList) {
		data->list->push_back(item);
	}
	return data;
}

send_struct * game_server_send_dices::doParse() {
	auto _room = dynamic_cast<gameroom *>(server->getRoom(roomId));
	auto userList = _room->getUserList();
	for(auto item : userList) {
		data->list->push_back(item);
	}
	for(int i = 0;i<5;i++) {
		data->str->append(ydc::format_string("%d ",_room->getdata().get_dices(i)));
	}
	return data;
}

send_struct * game_server_send_lockinfo::doParse() {
	auto _room = dynamic_cast<gameroom *>(server->getRoom(roomId));
	auto userList = _room->getUserList();
	for(auto item : userList) {
		data->list->push_back(item);
	}
	data->str->append(ydc::format_string("%d",_room->getdata().get_lockinfo()));
	return data;
}
send_struct * game_server_send_hello::doParse() {
	data->str->append("hello");
	data->list->push_back(_user);
	return data;
}