#include "common/paltform.h"
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

	void HandleAccept(rocket::network::ErrorCode ec, const ConnectioinPtr& s, const Acceptor_ptr &accepter);

	void run();

	int m_status;
};

