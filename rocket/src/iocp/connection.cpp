#include"iocp/connection.h"
using namespace rocket::network;

Connection::Connection()
{
	memset(&m_recv_handle_tag._overlapped, 0, sizeof(m_recv_handle_tag._overlapped));
	m_recv_handle_tag._type = RequestHandleTag::HANDLE_RECV;
	m_recv_WSABuf.buf = NULL;
	m_recv_WSABuf.len = 0;
}
void Connection::InitConnectSocket(SOCKET s, std::string remote_ip, unsigned short remote_port)
{

	m_socket = s;
	m_remote_ip = remote_ip;
	m_remote_port = remote_port;
	m_status = LS_WAITLINK;
	return;
}
Connection::~Connection()
{

}

//new socket to connect, or accept established socket
bool Connection::InitServer(const Server_Ptr& server_ptr)
{
	m_server_ptr = server_ptr;

	if (m_status != LS_UNINITIALIZE)
	{
		m_status = LS_ESTABLISHED;
	}
	else
	{
	/*
		_nLinkStatus = LS_WAITLINK;
		_socket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
		if (_socket == INVALID_SOCKET)
		{
			LCE("TcpSocket::doConnect[" << this << "] socket create error! ERRCODE=" << WSAGetLastError() << getTcpSocketStatus());
			return false;
		}

		SOCKADDR_IN localAddr;
		memset(&localAddr, 0, sizeof(SOCKADDR_IN));
		localAddr.sin_family = AF_INET;
		if (bind(_socket, (sockaddr *)&localAddr, sizeof(SOCKADDR_IN)) != 0)
		{
			LCE("TcpSocket::doConnect[" << this << "] bind local addr error! ERRCODE=" << WSAGetLastError() << getTcpSocketStatus());
			closesocket(_socket);
			_socket = INVALID_SOCKET;
			return false;
		}*/
	}
	
	if (CreateIoCompletionPort((HANDLE)m_socket, m_server_ptr->m_io, (ULONG_PTR)this, 0) == NULL)
	{
		closesocket(m_socket);
		m_socket = INVALID_SOCKET;
		return false;
	}
	return true;
}

bool Connection::doRecv(char *buf, unsigned int len, Recv_Handler &&handler)
{
	
	if (m_status != LS_ESTABLISHED)
	{
		//LCT("TcpSocket::doRecv[" << this << "] socket status != LS_ESTABLISHED. " << getTcpSocketStatus());
		return false;
	}
	if (!m_server_ptr)
	{
		//LCF("TcpSocket::doRecv[" << this << "] _summer pointer uninitialize." << getTcpSocketStatus());
		return false;
	}
	if (m_recv_handle)
	{
		//LCF("TcpSocket::doRecv[" << this << "] socket is recving. " << getTcpSocketStatus());
		return false;
	}
	if (len == 0)
	{
		//LCF("TcpSocket::doRecv[" << this << "] length is 0." << getTcpSocketStatus());
		return false;
	}


	m_recv_WSABuf.buf = buf;
	m_recv_WSABuf.len = len;

	DWORD dwRecv = 0;
	DWORD dwFlag = 0;
	if (WSARecv(m_socket, &m_recv_WSABuf, 1, &dwRecv, &dwFlag, &m_recv_handle_tag._overlapped, NULL) != 0)
	{
		if (WSAGetLastError() != WSA_IO_PENDING)
		{
			//LCT("TcpSocket::doRecv[" << this << "] doRecv failed and ERRCODE!=ERROR_IO_PENDING, ERRCODE=" << WSAGetLastError() << getTcpSocketStatus());
			m_recv_WSABuf.buf = nullptr;
			m_recv_WSABuf.len = 0;
			doClose();
			return false;
		}
	}
	m_recv_handle = std::move(handler);
	m_recv_handle_tag._connection = shared_from_this();
	return true;
}

bool Connection::doClose()
{
	if (m_status == LS_ESTABLISHED || m_status == LS_WAITLINK)
	{
		m_status = LS_CLOSED;
		closesocket(m_socket);
		return true;
	}
	return true;
}
