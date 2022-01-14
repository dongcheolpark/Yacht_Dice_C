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
		data->str->append(ydc::format_string("%d %s %d ",item->getuserId(),item->getuserName(),item->getUserReady()));
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
	data->str->append(ydc::format_string("%d ",server->getRoomList().size()));
	for(auto item : server->getRoomList()) {
		data->str->append(ydc::format_string("%d %s %d ",item->getRoomId(),item->getRoomName(),item->getRoomMaxPeople()));
	}	
	return data;
}
