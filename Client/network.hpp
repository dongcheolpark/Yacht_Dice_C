#pragma once
#include <iostream>
#ifdef _WIN32
#include <WinSock2.h>
#else 
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif
#include <string>

#define PORT 8080

class networkinterface {
public :
	virtual int join() { return 0; }
	virtual std::string* GetStringToServer() { return NULL; }
	virtual void SendStringToServer(std::string&) { return; }
#ifdef NDEBUG
	const char * ip_adress = "132.226.235.184";
#else
	const char * ip_adress = "127.0.0.1";
#endif
};

#ifdef _WIN32
class networkWin : public networkinterface {
private :
	WORD		wVersionRequested;
	WSADATA		wsaData;
	SOCKADDR_IN target; //Socket address information
	SOCKET      s;
	int			err;
	int			bytesSent;
	char        buf[1024];

public :
	networkWin(); 
	int join();
	std::string* GetStringToServer();
	void SendStringToServer(std::string&);
};
#else
class networkLinux : public networkinterface {
private : 
	int sock = 0;
	int valread;
	const int buff_size = 1024;
	struct sockaddr_in serv_addr;
public :
	networkLinux(); 
	int join(); 
	std::string * GetStringToServer();
	void SendStringToServer(std::string &);
};
#endif
