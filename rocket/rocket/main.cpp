#include<iostream>
#include<server/server.h>

std::string g_local_ip = "0.0.0.0";
unsigned short g_listen_Port = 8081;
class people
{
public:
	people(){ printf("new people"); };
	~people(){};

};



int main(int argc, char *argv[])
{

	printf("hello word \n");
	Server *server = new Server(g_local_ip, g_listen_Port);
	
	return 0;

}