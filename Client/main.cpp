#include "network.hpp"
#include <iostream>
#include <thread>
using std::thread;

using namespace std;

void func1(network * net) {
	puts("start thread");
	while(1)
	{
		printf("%s\n",net->GetStringToServer());
	}
}

int main(int argc, char const *argv[])
{
	network * net = new network();
	while(!net->join()) {
		char a;
		cout<<"서버와 다시 연결 하시겠습니까? Y/N"<<endl;
		cin>>a;
		if(a == 'N'||a == 'n') {
			cout<<"종료합니다."<<endl;
			return 0;
		}
	}
	thread t1(func1,net);
	thread t2([](network *net){
		while(1) {
			char * buffer = new char[1024];
			scanf("%s",buffer);
			net->SendStringToServer(buffer);
		}
	},net);
	t1.join();
	t2.join();
	return 0;
}