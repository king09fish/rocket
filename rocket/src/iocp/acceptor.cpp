
#include"iocp/acceptor.h"
using namespace rocket::network;

Acceptor::Acceptor(IO_SERVER *io) :p_io_server(io)
{
}

void Acceptor::Listen(const char* ip_addr, unsigned short port)
{

}

Acceptor::~Acceptor()
{

}