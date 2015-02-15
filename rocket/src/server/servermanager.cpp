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
	bool ret = m_acceptor->Accept(newConnection, std::bind(&ServerManager::HandleAccept, this, std::placeholders::_1, m_acceptor));
	if (ret)
	m_status = ServerStatus::Start_Suc;

	return ret;
}

void ServerManager::run()
{
	if(m_status)
	{
		server->ThreaLoop(true);
	}
}
void ServerManager::HandleAccept(const ConnectioinPtr &con, const Acceptor_ptr &accepter)
{

}

ServerManager::~ServerManager()
{
}