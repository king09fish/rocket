#include<iostream>
#include<server/server.h>

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

	printf("hello word \n");
	//Server *server = new Server(g_local_ip, g_listen_Port);
	std::shared_ptr<people> pInt2(new people());
	printf("the count %d", pInt2.use_count());
	pInt2.reset();

	while (true)
	{

	}
	return 0;

}