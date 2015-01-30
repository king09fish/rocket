

#ifndef _ROCKET_IOCP_H
#define _ROCKET_IOCP_H
#include "common.h"


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
			}

			~IO_SERVER(){}

			void test();

		public:
			HANDLE m_io = nullptr;



		};

	}

}
#endif