#include "network.hpp"
#include <cstdlib>

#ifdef _WIN32
networkWin::networkWin() {
	wVersionRequested = MAKEWORD(1, 1);
	err = WSAStartup(wVersionRequested, &wsaData);

	if (err != 0) {
		printf("WSAStartup error %ld", WSAGetLastError());
		WSACleanup();
		return;
	}

	target.sin_family = AF_INET; // address family Internet
	target.sin_port = htons(PORT); //Port to connect on
	target.sin_addr.s_addr = inet_addr(ip_adress); //Target IP


	s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //Create socket
	if (s == INVALID_SOCKET)
	{
		std::cout << "socket() error : " << WSAGetLastError() << std::endl;
		WSACleanup();
		return; //Couldn't create the socket
	}
}

int networkWin::join() {
	if (connect(s, reinterpret_cast<SOCKADDR*>(&target), sizeof(target)) == SOCKET_ERROR)
	{
		std::cout << "connect() error : " << WSAGetLastError() << std::endl;
		std::cout << "���� ���� �������ּ���." << std::endl;
		WSACleanup();
		return 0; //Couldn't connect	
	}
	recv(s,buf,1024,0);
	return atoi(buf);
}

std::string* networkWin::GetStringToServer() {
	recv(s,buf,1024,0);
	return new std::string(buf);
}

void networkWin::SendStringToServer(std::string& str) {
	str.append("<end>");
	send(s, str.c_str(), str.size(), 0);
}
#else 
networkLinux::networkLinux() {
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("\n Socket creation error \n");
		return;
	}
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	
	// Convert IPv4 and IPv6 addresses from text to binary form

}

int networkLinux::join() {
	if(inet_pton(AF_INET, this->ip_adress , &serv_addr.sin_addr)<=0)
	{
		printf("\nInvalid address/ Address not supported \n");
		return 0;
	}
	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		printf("\nConnection Failed \n");
		return 0;
	}
	char buffer[10];
	read(sock,buffer,buff_size);
	return atoi(buffer);
}
std::string * networkLinux::GetStringToServer() {
	char * buffer = new char[buff_size];
	if((valread = read(sock ,buffer, buff_size)) != 0) {
		return new std::string(buffer);
	}
	return NULL;
}
void networkLinux::SendStringToServer(std::string& str) {
	str.append("<end>");
	//puts(str);
	send(sock,str.c_str(),str.size(),0);
}
#endif // k
