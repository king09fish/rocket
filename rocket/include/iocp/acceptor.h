
#ifndef RRCKET_ACCEPTOR_H_
#define RRCKET_ACCEPTOR_H_
#include "iocp/iocp.h"

namespace rocket
{
	namespace network
	{
		class Acceptor
		{
			public:
				Acceptor(IO_SERVER *io);

				~Acceptor();

				void Listen(const char *ip_addr, unsigned short port);

			public:
			IO_SERVER *p_io_server;

			SOCKET m_server = INVALID_SOCKET;


		};

		

	}

}

#endif











