#include "iocp/connection.h"
using namespace rocket::network;


struct MsgBuff
{
	char buff[MSG_BUFF_SIZE];
	unsigned int buff_len = 0;
};

class session : public std::enable_shared_from_this<session>
{
public:
	session();

	~session();

	ConnectioinPtr connection_ptr;

	unsigned int m_session_id = 0;

	bool bindSocketPrt(const ConnectioinPtr &sockptr, unsigned int session_id);

	bool doRecv();

	void onRecv(rocket::network::ErrorCode ec, int nRecvedLen);

	void clear();

	MsgBuff m_reve_buff;
private:

};
typedef  std::shared_ptr<session> Session_Ptr;

