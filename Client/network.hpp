#pragma once
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#define PORT 8080

class network {
private : 
	int sock = 0;
	int valread;
	const int buff_size = 1024;
	struct sockaddr_in serv_addr;
public :
	network(); 
	bool join(); 
	char * GetStringToServer();
	void SendStringToServer(char *);
};
