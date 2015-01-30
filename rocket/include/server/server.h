#include "paltform.h"

using namespace rocket::network;

class Server
{
public:
	Server(const std::string, unsigned short);

	bool StartAccept();

	~Server();

public:
	Acceptor *m_acceptor = nullptr;

	std::string m_local_ip;

	unsigned short m_listen_port;

	IO_SERVER *p_io_server = nullptr;


};

