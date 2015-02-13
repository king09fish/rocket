

#ifndef _ROCKET_IOCP_SERVER_H
#define _ROCKET_IOCP_SERVER_H

#include "common/common.h"
namespace rocket
{
	namespace network
	{
		class IO_SERVER
		{
		public:
			IO_SERVER()
			{
				if (m_io != nullptr)
				{
					printf("the io is not null!");
				}
				m_io = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, 0);

				if (m_io == NULL)
				{
					printf("init io is error");
				}

			}

			~IO_SERVER(){}

			int test();

			void ThreaLoop(bool is_immediately);

		public:
			HANDLE m_io = nullptr;


		};
		typedef std::shared_ptr<IO_SERVER> Server_Ptr;
	}

}
#endif