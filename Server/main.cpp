#include "server.hpp"

int main(int argc, char const *argv[])
{
	server ser;
	ser.start();//네트워크 서버 시작
	return 0;
}