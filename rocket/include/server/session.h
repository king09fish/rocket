#include "iocp/connection.h"
using namespace rocket::network;

class session
{
public:
	session();

	~session();

	ConnectioinPtr connection_ptr;

	unsigned int m_session_id = 0;

	bool bindSocketPrt(const ConnectioinPtr &sockptr, unsigned int session_id);
private:

};
typedef  std::shared_ptr<session> Session_Ptr;

