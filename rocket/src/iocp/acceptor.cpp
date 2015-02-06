
#include"iocp/acceptor.h"
using namespace rocket::network;

Acceptor::Acceptor(IO_SERVER *io):io_server(io)
{

}

bool Acceptor::Listen(const char* ip_addr, unsigned short port)
{
	if (!io_server || m_server_socket != INVALID_SOCKET)
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
		//LCF("server bind err, ERRCODE=" << WSAGetLastError() << "   ip=" << ip << ", port=" << port);
		printf("bind function ErrorCode %d", WSAGetLastError());
		closesocket(m_server_socket);
		m_server_socket = INVALID_SOCKET;
		return false;
	}

	if (listen(m_server_socket, SOMAXCONN) == SOCKET_ERROR)
	{
	//	LCF("server listen err, ERRCODE=" << WSAGetLastError() << "   ip=" << ip << ", port=" << port);
		printf("listen function ErrorCode %d", WSAGetLastError());
		closesocket(m_server_socket);
		m_server_socket = INVALID_SOCKET;
		return false;
	}

	if (CreateIoCompletionPort((HANDLE)m_server_socket, io_server->m_io, (ULONG_PTR)this, 1) == NULL)
	{
		printf("create io after listen ErrorCode %d", WSAGetLastError());
		closesocket(m_server_socket);
		m_server_socket = INVALID_SOCKET;
		return false;
	}
	//_nLinkStatus = LS_ESTABLISHED;
	return true;
}

Acceptor::~Acceptor()
{

}