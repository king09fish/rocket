#include "common/paltform.h"
#include "session.h"
using namespace rocket::network;
class ServerManager
{
public:
	ServerManager(const std::string, unsigned short);

	bool StartAccept();

	~ServerManager();

public:
	Acceptor_ptr m_acceptor = nullptr;

	std::string m_local_ip;

	unsigned short m_listen_port;

	Server_Ptr server = nullptr;

	void HandleAccept(ErrorCode ec, const ConnectioinPtr& s, const Acceptor_ptr &accepter);

	void run();

	int m_status;

	unsigned int m_cur_session_count;

	static unsigned int m_max_session_count;

	unsigned int m_last_session_id = 0;
};

unsigned int ServerManager::m_max_session_count = 100;