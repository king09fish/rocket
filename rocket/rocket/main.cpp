#include<iostream>
#include<server/serverManager.h>

std::string g_local_ip = "0.0.0.0";
unsigned short g_listen_Port = 8081;
class people :public std::enable_shared_from_this<people>
{
public:
	people(){ printf("new people"); };
	~people(){
		printf("people delete is now");
	};

};



int main(int argc, char *argv[])
{
	ServerManager *p_server = new ServerManager(g_local_ip, g_listen_Port);

	if (p_server->StartAccept())
		p_server->run();
	
	return 0;
}