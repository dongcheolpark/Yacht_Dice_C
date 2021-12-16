#pragma once
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#define PORT 8080

class network {
private : 
	int sock = 0, valread;
	struct sockaddr_in serv_addr;
	char buffer[1024] = {0};
public :
	network(); 
	void join(); 
};
