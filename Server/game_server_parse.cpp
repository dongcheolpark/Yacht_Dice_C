#include "game_server_parse.hpp"
void game_server_parse::set_network_code(int first,int second)  {
	data->str->append(data->format_string("%d %d ",first, second));
}

send_struct * game_server_send_userList::doParse() {
	//유저 리스트 전송
	data->str->append(data->format_string("%d ",userList.size()));
	for(auto item : userList) {
		data->list->push_back(item);
		data->str->append(data->format_string("%d %s ",item->getuserId(),item->getuserName()));
	}
	return data;
}
send_struct * game_server_send_chatList::doParse() {
	auto chatList = server->getChatList();
	for(auto item : userList) {
		data->list->push_back(item);
	}
	data->str->append(data->format_string("%d ",chatList.size()));
	for(auto item : chatList) {
		data->str->append(data->format_string("%s ",item.c_str()));
	}
	return data;
}