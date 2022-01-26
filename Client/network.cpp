#include "network.hpp"
#include <cstdlib>

network::network() {
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("\n Socket creation error \n");
		return;
	}
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	
	// Convert IPv4 and IPv6 addresses from text to binary form

}

int network::join() {
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
std::string * network::GetStringToServer() {
	char * buffer = new char[buff_size];
	if((valread = read(sock ,buffer, buff_size)) != 0) {
		return new std::string(buffer);
	}
	return NULL;
}
void network::SendStringToServer(std::string& str) {
	str.append("<end>");
	//puts(str);
	send(sock,str.c_str(),str.size(),0);
}