#pragma once

#include <list>
#include <memory>
#include <string>
#include "../common/user.hpp"
class send_struct {
public:
	std::string * str;
	std::list<user *> * list;
	send_struct() {
		this->str = new std::string;
		this->list = new std::list<user*>;
	}
	send_struct(std::string * str,std::list<user*>*list) {
		this->str = str;
		this->list = list;
	}
	~send_struct() {
		delete str;
		delete list;
	}
	void print_data() {
		for(auto item : *list) {
			printf("%d %s\n",item->getuserId(),item->getuserName());
		}
		printf("%s\n",str->c_str());
	}
};