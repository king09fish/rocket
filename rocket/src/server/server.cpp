#include "server/server.h"


Server::Server(std::string ip, unsigned short port):m_local_ip(ip), m_listen_port(port)
{
	p_io_server = new IO_SERVER();
	m_acceptor = new Acceptor(p_io_server);
}

bool Server::StartAccept()
{
	if (m_acceptor == nullptr || p_io_server == nullptr)
	{
		printf("acceptor_ptr io_servi init fail");
		return false;
	}
	return true;
}


Server::~Server()
{
}