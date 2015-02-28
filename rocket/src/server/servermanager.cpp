#include "server/servermanager.h"
using namespace rocket::network;

ServerManager::ServerManager(std::string ip, unsigned short port) :m_local_ip(ip), m_listen_port(port), m_cur_session_count(0)
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
	bool ret = m_acceptor->Accept(newConnection, std::bind(&ServerManager::HandleAccept, this, std::placeholders::_1, std::placeholders::_2, m_acceptor));
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
void ServerManager::HandleAccept(ErrorCode ec, const ConnectioinPtr &con, const Acceptor_ptr &accepter)
{
	if (ec)
	{
		//accept fail
		ConnectioinPtr newConnection(new Connection());
		bool ret = m_acceptor->Accept(newConnection, std::bind(&ServerManager::HandleAccept, this, std::placeholders::_1, std::placeholders::_2, accepter));
		if (!ret)
		{
			printf("error accept in handleAccept");
		}
		return;
	}

	//accept true

	//check sessions count
	if (m_cur_session_count >= m_max_session_count)
	{

	}
	else 
	{
		m_cur_session_count++;

		m_last_session_id = nextSessionId(m_last_session_id);
		/*
		CTcpSessionPtr session(new TcpSession());
		s->initialize(_summer);
		if (session->bindTcpSocketPrt(s, aID, _lastSessionID, iter->second.first))
		{
			_mapTcpSessionPtr[_lastSessionID] = session;
			post(std::bind(&MessageDispatcher::dispatchOnSessionEstablished, &MessageDispatcher::getRef(), _lastSessionID));
		}*/
	}

}

ServerManager::~ServerManager()
{
}