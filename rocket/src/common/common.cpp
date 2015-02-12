


#include "common/common.h"

#ifdef WIN32
#pragma comment(lib, "ws2_32")
#pragma comment(lib, "Mswsock")

#endif




rocket::network::Env::Env()
{
	std::cout << "Env Construct" << std::endl;
}

rocket::network::Env::~Env()
{
	#ifdef WIN32
		WSACleanup();
	#endif
}

void rocket::network::Env::InitEnv()
{
	#ifdef WIN32
		WORD version = MAKEWORD(2, 2);
		WSADATA d;
		if (WSAStartup(version, &d) != 0)
		{
			assert(0);
		}
	#endif
}

namespace rocket
{
	namespace network
	{
		Env env;
	}
}