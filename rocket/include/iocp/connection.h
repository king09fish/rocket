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

			void InitConnectSocket(SOCKET s, std::string remote_ip, unsigned short remote_port);

			SOCKET m_socket = INVALID_SOCKET;

			std::string m_remote_ip;

			unsigned short m_remote_port;

			int m_status;

			Server_Ptr m_server_ptr;

			Recv_Handler m_recv_handle;
			RequestHandleTag m_recv_handle_tag;
			WSABUF	m_recv_WSABuf;

			bool InitServer(const Server_Ptr &server);

			bool doRecv(char *buf, unsigned int len, Recv_Handler &&handler);

			bool doClose();
		private:

		};
		typedef std::shared_ptr<Connection> ConnectioinPtr;


	}
}

#endif