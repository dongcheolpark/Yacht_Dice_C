#include "network.hpp"
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
	network net;
	while(!net.join()) {
		char a;
		cout<<"서버와 다시 연결 하시겠습니까? Y/N"<<endl;
		cin>>a;
		if(a == 'N'||a == 'n') {
			cout<<"종료합니다."<<endl;
			return 0;
		}
	}
	char * str = net.GetStringToServer();
	if(str != NULL)	printf("%s",str);
	return 0;
}