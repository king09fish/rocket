#include "server/session.h"

session::session()
{
}

session::~session()
{

}

void session::clear()
{

	m_session_id = 0;
	connection_ptr.reset();
	m_reve_buff.buff_len = 0;
}

bool session::bindSocketPrt(const ConnectioinPtr &sockptr, unsigned int session_id)
{

	//cleanSession(true, traits.rc4TcpEncryption);
	connection_ptr = sockptr;
	m_session_id = session_id;
	/*
	_acceptID = aID;
	_protoType = traits.protoType;
	_pulseInterval = traits.pulseInterval;
	_bOpenFlashPolicy = traits.openFlashPolicy;
	
	if (!doRecv())
	{
	//	LCW("bindTcpSocketPrt Failed.");
		return false;
	}
	/*
	if (traits.pulseInterval > 0)
	{
		_pulseTimerID = TcpSessionManager::getRef().createTimer(traits.pulseInterval, std::bind(&TcpSession::onPulseTimer, shared_from_this()));
	}*/
	return true;
}

bool session::doRecv()
{
	return connection_ptr->doRecv(m_reve_buff.buff + m_reve_buff.buff_len, MSG_BUFF_SIZE - m_reve_buff.buff_len, std::bind(&session::onRecv, shared_from_this(), std::placeholders::_1, std::placeholders::_2));
}

void session::onRecv(rocket::network::ErrorCode ec, int nRecvedLen)
{


}

