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
	while (true)
	{
		 dwTranceCount = 0;
		 uComKey = NULL;
		 pOverlapped = NULL;
		if (!GetQueuedCompletionStatus(m_io, &dwTranceCount, &uComKey, &pOverlapped, is_immediately ? 0 : 0))
		{
			if (GetLastError() == WAIT_TIMEOUT)
			{
				//printf("time nout");
				continue;

			}
			//printf("GetQueuedCompletionStatus failed with error %d\n", GetLastError());
		}
		if (!pOverlapped)
		{
			printf("poverlapped error %d", GetLastError());
			continue;
		}
		printf("enter accept now \n");
		RequestHandle &request = (ConvertOverlaped(pOverlapped));
		switch (request._type)
		{
		case RequestHandle::HANDLE_ACCEPT:
			if (request._tcpAccept)
				request._tcpAccept->OnMsg();
			printf("accept ");
			break;
		default:
			break;
		}

	}
	/*if (!bRet && !pOverlapped)
	{
		//TIMEOUT
		return;
	}*/
	
	/*
	//! user post
	if (uComKey == PCK_USER_DATA)
	{
		_OnPostHandler * func = (_OnPostHandler*) pOverlapped;
		try
		{
			(*func)();
		}
		catch (std::runtime_error e)
		{
			LCW("OnPostHandler have runtime_error exception. err=" << e.what());
		}
		catch (...)
		{
			LCW("OnPostHandler have unknown exception.");
		}
		delete func;
		return;
	}*/
	
	//! network data
	/*
	tagReqHandle & req = *(HandlerFromOverlaped(pOverlapped));
	switch (req._type)
	{
	case tagReqHandle::HANDLE_ACCEPT:
		{
			if (req._tcpAccept)
			{
				req._tcpAccept->onIOCPMessage(bRet);
			}
		}
		break;
	case tagReqHandle::HANDLE_RECV:
	case tagReqHandle::HANDLE_SEND:
	case tagReqHandle::HANDLE_CONNECT:
		{
			if (req._tcpSocket)
			{
				req._tcpSocket->onIOCPMessage(bRet, dwTranceCount, req._type);
			}
		}
		break;
	case tagReqHandle::HANDLE_SENDTO:
	case tagReqHandle::HANDLE_RECVFROM:
		{
			if (req._udpSocket)
			{
				req._udpSocket->onIOCPMessage(bRet, dwTranceCount, req._type);
			}
		}
		break;
	default:
		LCE("ZSummer::runOnce[this0x" << this << "]GetQueuedCompletionStatus undefined type=" << req._type << zsummerSection());
	}
	*/
}

