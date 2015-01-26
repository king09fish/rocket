#include "server/server.h"


Server::Server(std::string ip, unsigned short port):m_local_ip(ip), m_listen_port(port)
{
	//m_acceptor = new Acceptor();
}




Server::~Server()
{
}