#include "iocp/connection.h"
using namespace rocket::network;

class session
{
public:
	session();

	~session();

	ConnectioinPtr connection_ptr;

	unsigned int m_session_id = 0;
private:

};
typedef  std::shared_ptr<session> Session_Ptr;

