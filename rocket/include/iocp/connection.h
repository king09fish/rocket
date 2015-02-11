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

		private:

		};

		typedef std::shared_ptr<Connection> ConnectioinPtr;

	}
}

#endif