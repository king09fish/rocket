#include "server/servermanager.h"
using namespace rocket::network;

ServerManager::ServerManager(std::string ip, unsigned short port) :m_local_ip(ip), m_listen_port(port)
{
	env.InitEnv();
	server = std::make_shared<IO_SERVER>();
	m_acceptor = std::make_shared<Acceptor>(server);
	m_status = ServerStatus::Init_Suc;
}

bool ServerManager::StartAccept()
{
	if (m_acceptor == nullptr || server == nullptr)
	{
		printf("acceptor_ptr io_servi init fail");
		return false;
	}

	if (!m_acceptor->Listen(m_local_ip.c_str(), m_listen_port))
	{
		printf("acceptor listen Error");
		return false;
	}

	ConnectioinPtr newConnection(new Connection());
	m_status = m_acceptor->Accept(newConnection, std::bind(&ServerManager::HandleAccept, this, std::placeholders::_1, std::placeholders::_2, m_acceptor));
	return m_status;
}

void ServerManager::run()
{
	while (m_status)
	{
		server->runOnce();
	}
}
void ServerManager::HandleAccept(rocket::network::ErrorCode ec, const ConnectioinPtr& s, const Acceptor_ptr &accepter)
{

}

ServerManager::~ServerManager()
{
}