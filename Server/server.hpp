#pragma once
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <sys/time.h>
#include <string.h>
#include <pthread.h>
#include <string>

class server {
private :
	int server_fd,clnt_sock,valread;
	struct sockaddr_in address;
	struct timeval timeout;
	int fd_max, str_len, fd_num;
	const int buffer_size = 1024;
	int opt = 1;
	int addrlen = sizeof(address);
	char buffer[1024] = {0};
	fd_set reads, cpy_reads;
	const int port = 8080;
public :
	server(); 
	void start(); 
	void send_string(char * str);
};

