#include "iocp/iocp.h"
#include "iocp/acceptor.h"

using namespace rocket::network;

int IO_SERVER::test()
{
	if (true)
	{
		return 9;
	}
	return 7;
}

void IO_SERVER::ThreaLoop(bool is_immediately)
{
	if (m_io == NULL)
	{
		return;
	}

	DWORD dwTranceCount = 0;
	ULONG_PTR uComKey = NULL;
	LPOVERLAPPED pOverlapped = NULL;

	//BOOL bRet = GetQueuedCompletionStatus(m_io, &dwTranceCount, &uComKey, &pOverlapped, is_immediately ? 0 : _timer.getNextExpireTime()/*INFINITE*/);

	//_timer.checkTimer();
	bool ret = false;
	while (true)
	{
		 dwTranceCount = 0;
		 uComKey = NULL;
		 pOverlapped = NULL;
		 ret = GetQueuedCompletionStatus(m_io, &dwTranceCount, &uComKey, &pOverlapped, is_immediately ? 0:0);

		 if(!ret && !pOverlapped)
		 { 
			continue; //time out
		 }
		
		RequestHandle &request = (ConvertOverlaped(pOverlapped));
		switch (request._type)
		{
		case RequestHandle::HANDLE_ACCEPT:
			if (request._tcpAccept)
				request._tcpAccept->AcceptClient(ret);
			break;
		default:
			printf("error handle type");
			break;
		}

	}
	
}

