
#ifndef RRCKET_ACCEPTOR_H_
#define RRCKET_ACCEPTOR_H_
#include "iocp/iocp.h"
#include "iocp/connection.h"
namespace rocket
{
	namespace network
	{
		class Acceptor:public std::enable_shared_from_this<Acceptor>
		{
			public:
				Acceptor(Server_Ptr io);

				~Acceptor();

				bool Listen(const char *ip_addr, unsigned short port);

				bool Accept(const ConnectioinPtr &ptr, Accept_Handler&& handler);

			public:
				Server_Ptr server;

				SOCKET m_server_socket = INVALID_SOCKET;

				SOCKET m_client_socket = INVALID_SOCKET;

				SOCKADDR_IN	socket_addr;

				Accept_Handler m_Accept_Handler;

				ConnectioinPtr m_connection;

				RequestHandleTag m_request_handle;


				char m_recv_Buf[200];
				DWORD m_recv_Len = 0;
				bool AcceptClient(bool is_suc);

		};

		typedef std::shared_ptr<Acceptor> Acceptor_ptr;


	}

}

#endif











