#include "server.hpp"

int main(int argc, char const *argv[])
{
	server ser;
	ser.start();
	char str[100] = "hello,world!";
	ser.send_string(str);
	return 0;
}