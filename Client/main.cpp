#include "network.hpp"
#include <iostream>
#include <string>
#include <thread>
using std::thread;

using namespace std;

void func1(network * net) {
	while(1)
	{
		printf("%s\n",net->GetStringToServer());
	}
}

int main(int argc, char const *argv[])
{
	network * net = new network();
	int id = 0;
	while((id = net->join()) == 0) {
		char a;
		cout<<"서버와 다시 연결 하시겠습니까? Y/N"<<endl;
		cin>>a;
		if(a == 'N'||a == 'n') {
			cout<<"종료합니다."<<endl;
			return 0;
		}
	}
	thread t1(func1,net);
	char name[20];
	cout<<"사용할 닉네임을 정해주세요. (20자 제한)";
	cin>>name;
	char buffer[1024]; 
	sprintf(buffer,"0 %d %s",id,name);
	net->SendStringToServer(buffer);
	t1.join();
	return 0;
}