#include<iostream>
#include<server/server.h>

std::string g_local_ip = "0.0.0.0";
unsigned short g_listen_Port = 8081;
class people
{
public:
	people(){};
	~people(){};

public:
	int a;
};



int main(int argc, char *argv[])
{

	printf("hello worl3d \n");
	Server *server = new Server(g_local_ip, g_listen_Port);
	
	
	return 0;

}