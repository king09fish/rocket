#include"iocp/connection.h"
using namespace rocket::network;

Connection::Connection()
{

}
void Connection::InitConnectSocket(SOCKET s, std::string remote_ip, unsigned short remote_port)
{

	m_socket = s;
	m_remote_ip = remote_ip;
	m_remote_port = remote_port;
	//_nLinkStatus = LS_WAITLINK;
	return;
}
Connection::~Connection()
{

}