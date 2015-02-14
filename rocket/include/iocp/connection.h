#ifndef ROCKET_CONNECTION_H
#define ROCKET_CONNECTION_H

#include "common/common.h"
#include "iocp.h"
namespace rocket
{
	namespace network
	{
		class Connection:public std::enable_shared_from_this<Connection>
		{
		public:
			Connection();

			~Connection();

			void SetSocketInfo(SOCKET s, std::string remote_ip, unsigned short remote_port));
		private:

		};
		SOCKET		m_socket = INVALID_SOCKET;
		std::string m_remote_ip;
		unsigned short m_remote_port = 0;
		typedef std::shared_ptr<Connection> ConnectioinPtr;

	}
}

#endif