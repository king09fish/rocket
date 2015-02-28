#include "server/session.h"

session::session()
{
}

session::~session()
{

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