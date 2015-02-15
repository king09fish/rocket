
#include"iocp/acceptor.h"
using namespace rocket::network;

Acceptor::Acceptor(Server_Ptr io) :server(io)
{
	memset(&m_request_handle._overlapped, 0, sizeof(m_request_handle._overlapped));
	memset(&socket_addr, 0, sizeof(socket_addr));
	m_request_handle._type = RequestHandle::HANDLE_ACCEPT;
	m_server_socket = INVALID_SOCKET;
	m_client_socket = INVALID_SOCKET;
}

bool Acceptor::Listen(const char* ip_addr, unsigned short port)
{
	if (!server || m_server_socket != INVALID_SOCKET)
	{
		return false;
	}

	m_server_socket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
	if (m_server_socket == INVALID_SOCKET)
	{
		printf("valid server socket");
		return false;
	}

	BOOL bReUseAddr = TRUE;
	if (setsockopt(m_server_socket, SOL_SOCKET, SO_REUSEADDR, (char*)&bReUseAddr, sizeof(BOOL)) == SOCKET_ERROR)
	{
		printf("set socketop reuseAddr  ErrorCode %d", WSAGetLastError());
	}
	//SOCKET_ERROR
	socket_addr.sin_family = AF_INET;
	socket_addr.sin_addr.s_addr = inet_addr(ip_addr);
	socket_addr.sin_port = htons(port);
	if (bind(m_server_socket, (sockaddr *)&socket_addr, sizeof(socket_addr)) == SOCKET_ERROR)
	{
		printf("bind function ErrorCode %d", WSAGetLastError());
		closesocket(m_server_socket);
		m_server_socket = INVALID_SOCKET;
		return false;
	}

	if (listen(m_server_socket, SOMAXCONN) == SOCKET_ERROR)
	{
		printf("listen function ErrorCode %d", WSAGetLastError());
		closesocket(m_server_socket);
		m_server_socket = INVALID_SOCKET;
		return false;
	}

	if (CreateIoCompletionPort((HANDLE)m_server_socket, server->m_io, (ULONG_PTR)this, 1) == NULL)
	{
		printf("create io after listen ErrorCode %d", WSAGetLastError());
		closesocket(m_server_socket);
		m_server_socket = INVALID_SOCKET;
		return false;
	}
	//_nLinkStatus = LS_ESTABLISHED;
	return true;
}

bool Acceptor::Accept(const ConnectioinPtr &con, Accept_Handler&& handler)
{
	if (m_Accept_Handler)
	{	
		printf("AcceptHandler Error");
		//LCF("doAccept err, aready doAccept  ip=" << _ip << ", port=" << _port);
		return false;
	}
	/*
	if (_nLinkStatus != LS_ESTABLISHED)
	{
		LCF("doAccept err, link is unestablished.  ip=" << _ip << ", port=" << _port);
		return false;
	}*/

	m_connection = con;
	m_client_socket = INVALID_SOCKET;
	memset(m_recv_Buf, 0, sizeof(m_recv_Buf));
	m_recv_Len = 0;
	m_client_socket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
	if (m_client_socket == INVALID_SOCKET)
	{
		printf("Create client socket Error %d", WSAGetLastError());
		//LCF("create client socket err! ERRCODE=" << WSAGetLastError() << " ip=" << _ip << ", port=" << _port);
		return false;
	}

	if (!AcceptEx(m_server_socket, m_client_socket, m_recv_Buf, 0, sizeof(SOCKADDR_IN) + 16, sizeof(SOCKADDR_IN) + 16, &m_recv_Len, &m_request_handle._overlapped))
	{
		if (WSAGetLastError() != ERROR_IO_PENDING)
		{
			printf("AcceptEx ErrorCode %d", WSAGetLastError());
			//LCE("do AcceptEx err, ERRCODE=" << WSAGetLastError() << " ip=" << _ip << ", port=" << _port);
			closesocket(m_client_socket);
			m_client_socket = INVALID_SOCKET;
			return false;
		}
	}
	printf("AcceptEx Succ");
	m_Accept_Handler = std::move(handler);
	m_request_handle._tcpAccept = shared_from_this();
	return true;
}

bool Acceptor::OnMsg()
{
	std::shared_ptr<Acceptor> acceptor_ptr = std::move(m_request_handle._tcpAccept);
	Accept_Handler AcceptConnection = std::move(m_Accept_Handler);
	if (setsockopt(m_client_socket, SOL_SOCKET, SO_UPDATE_ACCEPT_CONTEXT, (char*)&m_server_socket, sizeof(m_server_socket)) != 0)
	{
		printf("set socket update accept contest fail ErrorCode %d", WSAGetLastError());
	}
	BOOL bTrue = TRUE;
	if (setsockopt(m_client_socket, IPPROTO_TCP, TCP_NODELAY, (char*)&bTrue, sizeof(bTrue)) != 0)
	{
		printf("set socket tcp_nodelay faile ErrorCode %d", WSAGetLastError());
	}

	sockaddr *paddr_local = NULL;
	sockaddr *paddr_remote = NULL;
	int len1 = 0;
	int len2 = 0;
	GetAcceptExSockaddrs(m_recv_Buf, m_recv_Len, sizeof(SOCKADDR_IN) + 16, sizeof(SOCKADDR_IN) + 16, &paddr_local, &len1, &paddr_remote, &len2);
	printf("the ip is %s \n", inet_ntoa(((sockaddr_in*)paddr_remote)->sin_addr));
	printf("the port is %u \n", ntohs(((sockaddr_in*)paddr_remote)->sin_port));
	m_connection->InitConnectSocket(m_client_socket, inet_ntoa(((sockaddr_in*)paddr_remote)->sin_addr), ntohs(((sockaddr_in*)paddr_remote)->sin_port));
	AcceptConnection(m_connection);
	
	return true;
}
Acceptor::~Acceptor()
{

}