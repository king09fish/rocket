#include "common.h"
#include "iocp/acceptor.h"
using namespace rocket::network;

class Server
{
public:
	Server(const std::string, unsigned short);

	~Server();

public:
	Acceptor *m_acceptor = nullptr;

	std::string m_local_ip;

	unsigned short m_listen_port;

};

