
#ifndef RRCKET_ACCEPTOR_H_
#define RRCKET_ACCEPTOR_H_
#include "iocp/iocp.h"
#include "iocp/connection.h"
namespace rocket
{
	namespace network
	{
		class Acceptor
		{
			public:
				Acceptor(IO_SERVER *io);

				~Acceptor();

				bool Listen(const char *ip_addr, unsigned short port);

				bool Accept(const ConnectioinPtr &ptr);

			public:
			IO_SERVER *io_server;

			SOCKET m_server_socket = INVALID_SOCKET;

			SOCKET m_client_socket = INVALID_SOCKET;

			SOCKADDR_IN	socket_addr;

			_AcceptHandler m_Accept_Handler;

			ConnectioinPtr m_connection;

			char m_recv_Buf[200];
			DWORD m_recv_Len = 0;

		};

		

	}

}

#endif











